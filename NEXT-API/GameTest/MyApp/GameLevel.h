//---------------------------------------------------------------------------------
// GameLevel.h
//---------------------------------------------------------------------------------
#ifndef _GAMELEVEL_H
#define _GAMELEVEL_H

#include "..\stdafx.h"
#include "LevelCell.h"
#include "../App/AppSettings.h"

constexpr int numRows = 13;
constexpr int numCols = 41;
constexpr int numVirtualRows = APP_VIRTUAL_HEIGHT / cellSize;
constexpr int numVirtualCols = APP_VIRTUAL_WIDTH / cellSize;

class CGameLevel {
public:
	static CGameLevel& GetInstance();
	void GenerateLevel(int difficultyLevel);
	void Render();
	bool IsBlocked(float x, float y);

private:
	CLevelCell* VirtualCoordsToLevelCell(float x, float y);
	CLevelCell m_cells[numRows][numCols];

};

#endif