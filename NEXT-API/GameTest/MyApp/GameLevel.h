//---------------------------------------------------------------------------------
// GameLevel.h
//---------------------------------------------------------------------------------
#ifndef _GAMELEVEL_H
#define _GAMELEVEL_H

#include "..\stdafx.h"
#include "LevelCell.h"

constexpr int numRows = 13;
constexpr int numCols = 41;

class CGameLevel {
public:
	static CGameLevel& GetInstance();
	void GenerateLevel(int difficultyLevel);
	void Render();

private:
	CLevelCell m_cells[numRows][numCols];

};

#endif