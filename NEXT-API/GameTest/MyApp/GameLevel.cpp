//---------------------------------------------------------------------------------
// GameLevel.cpp
//---------------------------------------------------------------------------------
#include "stdafx.h"
#include "GameLevel.h"
#include "Block.h"
#include "Blocks.h"
#include "PlayerController.h"
#include <cmath>
#include <functional>
#include <vector>
#include <ctime>


//-----------------------------------------------------------------------------
// Singleton
//-----------------------------------------------------------------------------
CGameLevel& CGameLevel::GetInstance()
{
	static CGameLevel level;
	return level;
}

std::shared_ptr<CPlayerController> player = nullptr;
bool generatedBefore = false;
bool generationFrame = false;

void CGameLevel::GenerateLevel(int difficultyLevel)
{
	srand((unsigned int)time(NULL));
	m_totalShift = 0.0F;
	generationFrame = true;
	m_activeCharacters.clear();
	for (int r = 0; r < numRows; r++) {
		for (int c = 0; c < numCols; c++) {
			// Put concrete blocks around edges
			if (!generatedBefore && (r == 0 || c == 0 || r == numRows - 1 || c == numCols - 1)) {
				auto block = new CConcreteBlock();
				block->Init(r, c);
				m_cells[r][c].SetContainedObject(std::shared_ptr<CLevelObject>(block));
			}
			// Put concrete blocks at odd rows and colums
			else if (!generatedBefore && ((r + 1) % 2 == 1 && (c + 1) % 2 == 1)) {
				auto block = new CConcreteBlock();
				block->Init(r, c);
				m_cells[r][c].SetContainedObject(std::shared_ptr<CLevelObject>(block));
			}
			else {
				if (c > 4 && (rand() % 100) < 30) {
					auto block = new CBrickBlock(1);
					block->Init(r, c);
					m_cells[r][c].SetContainedObject(std::shared_ptr<CLevelObject>(block));
				}
				else {
					m_cells[r][c].Clear(true);
				}
			}
		}
	}
	if (player == nullptr) {
		player = std::make_shared<CPlayerController>();	
	}
	AddCharacter(player, playerSpawnRow, playerSpawnCol);
}

void CGameLevel::Render()
{
	for (int r = 0; r < numRows; r++) {
		for (int c = 0; c < numCols; c++) {
			m_cells[r][c].Render();
		}
	}
}

void CGameLevel::Update(float deltaTime)
{
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
	y = row * cellSize + (cellSize / 2);
	x = (col * cellSize + (cellSize / 2) - m_totalShift);
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
	m_cells[row][col].SetContainedCharacter(character);
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

