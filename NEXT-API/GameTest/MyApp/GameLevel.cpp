//---------------------------------------------------------------------------------
// GameLevel.cpp
//---------------------------------------------------------------------------------
#include "stdafx.h"
#include "GameLevel.h"
#include "Block.h"


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
				m_cells[r][c].SetContainedObject(new CBlock(c * 32, r * 32, CONCRETE_BLOCK));
			}
			// Put concrete blocks at odd rows and colums
			else if (r + 1 % 2 == 1 && c + 1 % 2 == 1) {
				m_cells[r][c].SetContainedObject(new CBlock(c * 32, r * 32, CONCRETE_BLOCK));
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

