//---------------------------------------------------------------------------------
// GameLevel.cpp
//---------------------------------------------------------------------------------
#include "stdafx.h"
#include "GameLevel.h"
#include <cmath>
#include <functional>
#include <vector>
#include <ctime>
#include "EnemyController.h"
#include "../App/app.h"
#include "BombDispenser.h";
#include "GameLogicSubclasses.h"

CLevelObject* GetConcreteBlock() {
	auto sp = App::CreateSprite(".\\MyData\\ConcreteBlock.bmp", 1, 1);
	return new CLevelObject(true, std::unique_ptr<CSimpleSprite>(sp), nullptr);
}

CLevelObject* GetBrickBlock() {
	auto sp = App::CreateSprite(".\\MyData\\BrickBlock.bmp", 1, 1);
	auto explodeLogic = new CExplodeLogic(nullptr, nullptr, 1);
	return new CLevelObject(true, std::unique_ptr<CSimpleSprite>(sp), std::unique_ptr<CExplodeLogic>(explodeLogic));
}

CLevelObject* GetDoorItem() {
	auto sp = App::CreateSprite(".\\MyData\\DoorItem.bmp", 1, 1);
	auto increaseLevel = new CAddLivesOnPlayerPickupLogic();
	return new CLevelObject(false, std::unique_ptr<CSimpleSprite>(sp), nullptr, std::unique_ptr<COnPlayerPickupLogic>(increaseLevel));
}

CLevelObject* GetDoorBlock() {
	auto sp = App::CreateSprite(".\\MyData\\BrickBlock.bmp", 1, 1);
	auto explodeLogic = new CExplodeLogic(nullptr, std::shared_ptr<CLevelObject>(GetDoorItem()), 1, 100);
	return new CLevelObject(true, std::unique_ptr<CSimpleSprite>(sp), std::unique_ptr<CExplodeLogic>(explodeLogic));
}

CEnemyController* GetWandererEnemy() {
	auto sp = App::CreateSprite(".\\MyData\\BaseCharacter.bmp", 2, 2);
	sp->SetColor(40.0F / 255.0F, 23.0F / 255.0F, 173.0F / 255.0F);
	auto explodeLogic = new CExplodeLogic();
	auto inputLogic = new CHugWallAIInput();
	return new CEnemyController(false, std::unique_ptr<CSimpleSprite>(sp), std::unique_ptr<CExplodeLogic>(explodeLogic), std::unique_ptr<CHugWallAIInput>(inputLogic));
}


//-----------------------------------------------------------------------------
// Singleton
//-----------------------------------------------------------------------------
CGameLevel& CGameLevel::GetInstance()
{
	static CGameLevel level;
	return level;
}

bool generatedBefore = false;
bool generationFrame = false;

void CGameLevel::GenerateLevel(int difficultyLevel)
{
	m_currentDifficulty = difficultyLevel;
	srand((unsigned int)time(NULL));
	m_totalShift = 0.0F;
	generationFrame = true;
	m_activeCharacters.clear();
	for (int r = 0; r < numRows; r++) {
		for (int c = 0; c < numCols; c++) {
			// Put concrete blocks around edges
			if ((r == 0 || c == 0 || r == numRows - 1 || c == numCols - 1)) {
				if (!generatedBefore) {
					auto block = GetConcreteBlock();
					block->Init(r, c);
					m_cells[r][c].SetContainedObject(std::shared_ptr<CLevelObject>(block));
				}
			}
			// Put concrete blocks at odd rows and colums
			else if (((r + 1) % 2 == 1 && (c + 1) % 2 == 1)) {
				if (!generatedBefore) {
					auto block = GetConcreteBlock();
					block->Init(r, c);
					m_cells[r][c].SetContainedObject(std::shared_ptr<CLevelObject>(block));
				}
			}
			else {
				if (c > 4 && (rand() % 100) < 30) {
					auto block = GetDoorBlock();
					block->Init(r, c);
					m_cells[r][c].SetContainedObject(std::shared_ptr<CLevelObject>(block));
				}
				else {
					m_cells[r][c].Clear(true, true);
				}
			}
		}
	}

	
	auto explodeLogic = new CExplodeLogic();
	GetPlayer().SetExplodeLogic(std::unique_ptr<CExplodeLogic>(explodeLogic));
	AddCharacter(m_player, playerSpawnRow, playerSpawnCol);
	
	auto wandererEnemy = GetWandererEnemy();
	AddCharacter(std::shared_ptr<CEnemyController>(wandererEnemy), 1, playerSpawnCol);

	generatedBefore = true;
}

bool CGameLevel::IsCenterOfCell(float x, float y)
{
	int decimalX = abs(static_cast<int>(((x + m_totalShift) / cellSize) * 10)) % 10;
	int decimalY = abs(static_cast<int>((y / cellSize) * 10)) % 10;
	bool atCenterOfCellX = decimalX == 5;
	bool atCenterOfCellY = decimalY == 5;
	return atCenterOfCellX && atCenterOfCellY;
}

void CGameLevel::Render()
{
	m_scoreboard.Render(static_cast<int>(m_timeLeft / 1000.0F), m_score, m_livesLeft, m_currentDifficulty + 1);
	for (int r = 0; r < numRows; r++) {
		for (int c = 0; c < numCols; c++) {
			m_cells[r][c].Render();
		}
	}
}

void CGameLevel::Update(float deltaTime)
{
	m_timeLeft -= deltaTime;
	for (auto& activeCharacter : m_activeCharacters) {
		if (generationFrame) {
			generationFrame = false;
			return;
		}
		activeCharacter->Update(deltaTime);
	}
}

void CGameLevel::ShiftLevelHorizontally(float xShift)
{
	for (int r = 0; r < numRows; r++) {
		for (int c = 0; c < numCols; c++) {
			m_cells[r][c].ShiftHorizontally(xShift);
		}
	}
	m_totalShift += xShift;
}

bool CGameLevel::IsBlocked(float x, float y)
{
	return VirtualCoordsToLevelCell(x, y)->Blocked();
}

void CGameLevel::CellToVirtualCoords(int row, int col, float& x, float& y)
{
	y = static_cast<float>(row * cellSize + (cellSize / 2));
	x = static_cast<float>((col * cellSize + (cellSize / 2)) - m_totalShift);
}

void CGameLevel::VirtualCoordsToCell(float x, float y, int& row, int& column)
{
	float cellSizeF = static_cast<float>(cellSize);
	row = static_cast<int>(y / cellSizeF);
	column = static_cast<int>((x + m_totalShift) / cellSizeF);
}

CLevelCell* CGameLevel::GetLevelCell(int row, int column)
{
	return &m_cells[row][column];
}

CLevelCell* CGameLevel::VirtualCoordsToLevelCell(float x, float y)
{
	int row, column;
	VirtualCoordsToCell(x, y, row, column);
	return GetLevelCell(row, column);
}

void CGameLevel::AddCharacter(std::shared_ptr<CCharacterController> character, int row, int col)
{
	character->Init(row, col);
	m_cells[row][col].AddContainedCharacter(character);
	m_activeCharacters.emplace(character);
}

void CGameLevel::RemoveCharacter(std::shared_ptr<CCharacterController> character)
{
	std::shared_ptr<CPlayerController> player = std::dynamic_pointer_cast<CPlayerController>(character);
	if (player == nullptr)
	{
		m_activeCharacters.erase(character);
	}
	else {
		player->SetDead(true);
	}
}

CPlayerController& CGameLevel::GetPlayer()
{
	if (m_player == nullptr) {
		auto sp = App::CreateSprite(".\\MyData\\BaseCharacter.bmp", 2, 2);
		sp->SetColor(0.0F, 1.0F, 0.0F);

		m_player = std::shared_ptr<CPlayerController>(new CPlayerController(false, std::unique_ptr<CSimpleSprite>(sp), nullptr));
		m_player->SetBasicDispenser(BombType::BASIC_BOMB);
		m_player->SetSpecialDispenser(BombType::SUPERBOMB);
		m_player->SetBasicDispenserMaxBombs(3);
	}
	return *m_player;
}

