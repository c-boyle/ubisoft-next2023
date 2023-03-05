//---------------------------------------------------------------------------------
// GameLevel.h
//---------------------------------------------------------------------------------
#ifndef _GAMELEVEL_H
#define _GAMELEVEL_H

#include "..\stdafx.h"
#include "LevelCell.h"
#include "../App/AppSettings.h"
#include <unordered_set>
#include "PlayerController.h"
#include "EnemyController.h"
#include "Scoreboard.h"

constexpr int numRows = 13;
constexpr int numCols = 35;
constexpr int numVirtualRows = APP_VIRTUAL_HEIGHT / cellSize;
constexpr int numVirtualCols = APP_VIRTUAL_WIDTH / cellSize;
constexpr int levelWidth = numCols * cellSize;

constexpr int playerSpawnRow = numRows - 2;
constexpr int playerSpawnCol = 1;

class CGameLevel {
public:
	static CGameLevel& GetInstance();
	void GenerateLevel(int difficultyLevel);
	void Respawn();
	bool IsCenterOfCell(float x, float y);
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
	CPlayerController& GetPlayer();
	void AddScore(int score) { m_score += score; }
	void AddLives(int lives) { m_livesLeft += lives; }
	void AddCharacter(std::shared_ptr<CCharacterController> character, int row, int col);
	CEnemyController* GetWandererEnemy();

private:
	void RespawnPlayer();

private:
	std::unordered_set<std::shared_ptr<CCharacterController>> m_activeCharacters;
	CLevelCell m_cells[numRows][numCols];
	float m_totalShift;
	int m_currentDifficulty;
	std::shared_ptr<CPlayerController> m_player;
	CScoreboard m_scoreboard = CScoreboard(cellSize, APP_VIRTUAL_HEIGHT - cellSize);
	int m_livesLeft = 0;
	float m_timeLeft = 200.0F * 1000.0F;
	int m_score = 0;


};

#endif