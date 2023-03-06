//---------------------------------------------------------------------------------
// GameLevel.cpp
//---------------------------------------------------------------------------------
#include "stdafx.h"
#include "GameLevel.h"
#include <cmath>
#include <functional>
#include <vector>
#include "../App/app.h"
#include "BombDispenser.h"
#include "GameLogicSubclasses.h"
#include "MyApp.h"

CLevelObject* GetConcreteBlock() {
	auto sp = App::CreateSprite(".\\MyData\\ConcreteBlock.bmp", 1, 1);
	return new CLevelObject(true, std::unique_ptr<CSimpleSprite>(sp), nullptr);
}

//-----------------------------------------------------------------------------
// Singleton
//-----------------------------------------------------------------------------
CGameLevel& CGameLevel::GetInstance()
{
	static CGameLevel level;
	return level;
}

bool generationFrame = false;

void CGameLevel::GenerateLevel(int difficultyLevel)
{
	m_timeLeft = 200.0F * 1000.0F;
	m_currentDifficulty = difficultyLevel;
	m_generator.Init();
	m_totalShift = 0.0F;
	generationFrame = true;
	m_activeCharacters.clear();
	for (int r = 0; r < numRows; r++) {
		for (int c = 0; c < numCols; c++) {
			// Put concrete blocks around edges
			if ((r == 0 || c == 0 || r == numRows - 1 || c == numCols - 1)) {
				auto block = GetConcreteBlock();
				block->Init(r, c);
				m_cells[r][c].SetContainedObject(std::shared_ptr<CLevelObject>(block));
			}
			// Put concrete blocks at odd rows and colums
			else if (((r + 1) % 2 == 1 && (c + 1) % 2 == 1)) {
				auto block = GetConcreteBlock();
				block->Init(r, c);
				m_cells[r][c].SetContainedObject(std::shared_ptr<CLevelObject>(block));
			}
			else {
				bool isSpawnReserved = (c == 1 && r == numRows - 2) || (c == 1 && r == numRows - 3) || (c == 2 && r == numRows - 2);
				if (!isSpawnReserved) {
					auto object = m_generator.GenerateRandomObject();
					if (object == nullptr) {
						m_cells[r][c].Clear(true, true);
					}
					else {
						CCharacterController* character = dynamic_cast<CCharacterController*>(object);
						if (character != nullptr) {
							AddCharacter(std::shared_ptr<CCharacterController>(character), r, c);
						}
						else {
							object->Init(r, c);
							m_cells[r][c].SetContainedObject(std::shared_ptr<CLevelObject>(object));
						}
					}
				}
			}
		}
	}

	RespawnPlayer();
}

void CGameLevel::Respawn()
{
	if (m_livesLeft == 0) {
		GenerateLevel(1);
		m_livesLeft = 0;
	}
	else {
		RespawnPlayer();
		--m_livesLeft;
	}
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
	m_scoreboard.Render(static_cast<int>(m_timeLeft / 1000.0F), m_score, m_livesLeft, m_currentDifficulty);
	for (int r = 0; r < numRows; r++) {
		for (int c = 0; c < numCols; c++) {
			m_cells[r][c].Render();
		}
	}
}

void CGameLevel::Update(float deltaTime)
{
	m_timeLeft -= deltaTime;
	if (m_timeLeft <= 0) {
		Respawn();
		return;
	}
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
	if (row >= 0 && row < numRows && column >= 0 && column < numCols) {
		return &m_cells[row][column];
	}
	return nullptr;
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

void CGameLevel::RespawnPlayer()
{
	auto explodeLogic = new CExplodeLogic();
	GetPlayer().SetExplodeLogic(std::unique_ptr<CExplodeLogic>(explodeLogic));
	AddCharacter(m_player, playerSpawnRow, playerSpawnCol);
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
		m_player->SetSpecialDispenser(BombType::DIRTY_BOMB);
	}
	return *m_player;
}

