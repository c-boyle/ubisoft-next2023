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


//-----------------------------------------------------------------------------
// Singleton
//-----------------------------------------------------------------------------
CGameLevel& CGameLevel::GetInstance()
{
	static CGameLevel level;
	return level;
}

bool removeCharactersNextFrame = false;
std::vector<std::weak_ptr<CCharacterController>> charactersToRemove;

void CGameLevel::GenerateLevel(int difficultyLevel)
{
	for (int r = 0; r < numRows; r++) {
		for (int c = 0; c < numCols; c++) {
			// Put concrete blocks around edges
			if (r == 0 || c == 0 || r == numRows - 1 || c == numCols - 1) {
				auto block = new CConcreteBlock();
				block->Init(r, c);
				m_cells[r][c].SetContainedObject(std::shared_ptr<CLevelObject>(block));
			}
			// Put concrete blocks at odd rows and colums
			else if ((r + 1) % 2 == 1 && (c + 1) % 2 == 1) {
				auto block = new CConcreteBlock();
				block->Init(r, c);
				m_cells[r][c].SetContainedObject(std::shared_ptr<CLevelObject>(block));
			}
			else {
				if (c > 4) {
					auto block = new CBrickBlock(1);
					block->Init(r, c);
					m_cells[r][c].SetContainedObject(std::shared_ptr<CLevelObject>(block));
				}
			}
		}
	}
	AddCharacter(std::make_shared<CPlayerController>(), playerSpawnRow, playerSpawnCol);
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
	if (removeCharactersNextFrame) {
		for (auto& character : charactersToRemove) {
			if (auto characterToRemove = character.lock()) {
				m_activeCharacters.erase(characterToRemove);
			}
		}
		charactersToRemove.clear();
		removeCharactersNextFrame = false;
	}
	for (auto& activeCharacter : m_activeCharacters) {
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
	m_activeCharacters.insert(character);
}

void CGameLevel::RemoveCharacter(std::shared_ptr<CCharacterController> character)
{
	removeCharactersNextFrame = true;
	charactersToRemove.push_back(character);
}

