//---------------------------------------------------------------------------------
// GameLogicSubclasses.cpp
//---------------------------------------------------------------------------------
#include "stdafx.h"
#include "GameLogicSubclasses.h"
#include "GameLevel.h"
#include "CharacterController.h"

#pragma region OnPlayerPickupLogics

void CIncreaseLevelOnPlayerPickupLogic::OnPlayerPickup()
{
	CGameLevel::GetInstance().GenerateLevel(CGameLevel::GetInstance().GetDifficulty() + m_levelIncrease);
}

#pragma endregion

#pragma region DetonateLogics

void CAxisDetonateLogic::Detonate(CLevelObject& object)
{
	m_detonated = true;
	bool leftBlocked = false;
	bool rightBlocked = false;
	bool upBlocked = false;
	bool downBlocked = false;

	int row, col;
	object.GetPosition(row, col);

	CGameLevel::GetInstance().GetLevelCell(row, col)->Explode();
	for (int i = 1; i <= m_range; i++) {
		if (!downBlocked) {
			downBlocked = !CGameLevel::GetInstance().GetLevelCell(row - i, col)->Explode();
		}
		if (!upBlocked) {
			upBlocked = !CGameLevel::GetInstance().GetLevelCell(row + i, col)->Explode();
		}
		if (!leftBlocked) {
			leftBlocked = !CGameLevel::GetInstance().GetLevelCell(row, col - i)->Explode();
		}
		if (!rightBlocked) {
			rightBlocked = !CGameLevel::GetInstance().GetLevelCell(row, col + i)->Explode();
		}
	}
}
#pragma endregion

#pragma region AIInputLogics

void CHugWallAIInput::HandleInput(CCharacterController& character)
{
	float oldX, oldY;
	character.GetPosition(oldX, oldY);
	int oldRow, oldCol;
	character.GetPosition(oldRow, oldCol);
	character.Move(static_cast<float>(m_dirX), static_cast<float>(m_dirY));
	float newX, newY;
	character.GetPosition(newX, newY);
	int newRow, newCol;
	character.GetPosition(newRow, newCol);
	bool notMoving = oldX == newX && oldY == newY;
	bool freshCell = !notMoving && !CGameLevel::GetInstance().IsCenterOfCell(oldX, oldY) && CGameLevel::GetInstance().IsCenterOfCell(newX, newY);
	if (notMoving || freshCell) {
		int newDirX, newDirY;
		PrefferedNewDir(newDirX, newDirY);
		if (!CGameLevel::GetInstance().GetLevelCell(newRow + newDirY, newCol + newDirX)->Blocked() || CGameLevel::GetInstance().GetLevelCell(newRow + m_dirY, newCol + m_dirX)->Blocked()) {
			m_dirX = newDirX;
			m_dirY = newDirY;
		}
	}
}

void CHugWallAIInput::PrefferedNewDir(int& x, int& y)
{
	if (m_dirX == -1 && m_dirY == 0) { // left
			// Go down
		x = 0;
		y = -1;
	}
	else if (m_dirX == 0 && m_dirY == -1) { // down
		// Go right
		x = 1;
		y = 0;
	}
	else if (m_dirX == 1 && m_dirY == 0) { // right
		// do up
		x = 0;
		y = 1;
	} 
	else { // up
		// Go left
		x = -1;
		y = 0;
	}
}

#pragma endregion


