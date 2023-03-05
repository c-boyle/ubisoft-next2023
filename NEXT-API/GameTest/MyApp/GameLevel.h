//---------------------------------------------------------------------------------
// GameLevel.h
//---------------------------------------------------------------------------------
#ifndef _GAMELEVEL_H
#define _GAMELEVEL_H

#include "..\stdafx.h"
#include "LevelCell.h"
#include "../App/AppSettings.h"
#include <unordered_set>

constexpr int numRows = 13;
constexpr int numCols = 41;
constexpr int numVirtualRows = APP_VIRTUAL_HEIGHT / cellSize;
constexpr int numVirtualCols = APP_VIRTUAL_WIDTH / cellSize;
constexpr int levelWidth = numCols * cellSize;

constexpr int playerSpawnRow = numRows - 2;
constexpr int playerSpawnCol = 1;

class CGameLevel {
public:
	static CGameLevel& GetInstance();
	void GenerateLevel(int difficultyLevel);
	void Render();
	void Update(float deltaTime);
	void ShiftLevelHorizontally(float xShift);
	bool IsBlocked(float x, float y);
	void CellToVirtualCoords(int row, int col, float& x, float& y);
	void VirtualCoordsToCell(float x, float y, int& row, int& column);
	CLevelCell* GetLevelCell(int row, int column);
	CLevelCell* VirtualCoordsToLevelCell(float x, float y);
	float GetTotalShift() { return m_totalShift;  }
	void RemoveCharacter(std::shared_ptr<CCharacterController> character);
	int GetDifficulty() { return m_currentDifficulty; }

private:
	void AddCharacter(std::shared_ptr<CCharacterController> character, int row, int col);

private:
	std::unordered_set<std::shared_ptr<CCharacterController>> m_activeCharacters;
	CLevelCell m_cells[numRows][numCols];
	float m_totalShift;
	int m_currentDifficulty;

};

#endif