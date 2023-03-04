//---------------------------------------------------------------------------------
// GameLevel.cpp
//---------------------------------------------------------------------------------
#include "stdafx.h"
#include "GameLevel.h"
#include "Block.h"
#include <cmath>


//-----------------------------------------------------------------------------
// Singleton
//-----------------------------------------------------------------------------
CGameLevel& CGameLevel::GetInstance()
{
	static CGameLevel level;
	return level;
}

void CGameLevel::GenerateLevel(int difficultyLevel)
{
	for (int r = 0; r < numRows; r++) {
		for (int c = 0; c < numCols; c++) {
			// Put concrete blocks around edges
			if (r == 0 || c == 0 || r == numRows - 1 || c == numCols - 1) {
				m_cells[r][c].SetContainedObject(new CBlock(c * cellSize + (cellSize / 2), r * cellSize + (cellSize / 2), BlockType::CONCRETE_BLOCK));
			}
			// Put concrete blocks at odd rows and colums
			else if ((r + 1) % 2 == 1 && (c + 1) % 2 == 1) {
				m_cells[r][c].SetContainedObject(new CBlock(c * cellSize + (cellSize / 2), r * cellSize + (cellSize / 2), BlockType::CONCRETE_BLOCK));
			}
			else {
				//m_cells[r][c].SetContainedObject(new CBlock(c * cellSize + (cellSize / 2), r * cellSize, BlockType::BRICK_BLOCK));
			}
		}
	}
}

void CGameLevel::Render()
{
	for (int r = 0; r < numRows; r++) {
		for (int c = 0; c < numCols; c++) {
			m_cells[r][c].Render();
		}
	}
}

bool CGameLevel::IsBlocked(float x, float y)
{
	return VirtualCoordsToLevelCell(x, y)->BlocksCell();
}

CLevelCell* CGameLevel::VirtualCoordsToLevelCell(float x, float y)
{
	float cellSizeF = static_cast<float>(cellSize);
	int cellRow = static_cast<int>((APP_VIRTUAL_HEIGHT - y) / cellSizeF) - abs(numVirtualRows - numRows);
	int cellCol = static_cast<int>(x / cellSizeF);
	return &m_cells[cellRow][cellCol];
}

