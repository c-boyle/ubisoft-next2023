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
				auto block = new CBlock();
				block->Init(r, c);
				m_cells[r][c].SetContainedObject(block);
			}
			// Put concrete blocks at odd rows and colums
			else if ((r + 1) % 2 == 1 && (c + 1) % 2 == 1) {
				auto block = new CBlock();
				block->Init(r, c);
				m_cells[r][c].SetContainedObject(block);
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
	return VirtualCoordsToLevelCell(x, y)->Blocked();
}

void CGameLevel::CellToVirtualCoords(int row, int col, float& x, float& y)
{
	y = row * cellSize + (cellSize / 2);
	x = col * cellSize + (cellSize / 2);
}

void CGameLevel::VirtualCoordsToCell(float x, float y, int& row, int& column)
{
	float cellSizeF = static_cast<float>(cellSize);
	row = static_cast<int>((APP_VIRTUAL_HEIGHT - y) / cellSizeF) - abs(numVirtualRows - numRows);
	column = static_cast<int>(x / cellSizeF);
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

