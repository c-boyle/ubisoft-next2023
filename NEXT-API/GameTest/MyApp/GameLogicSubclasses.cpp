//---------------------------------------------------------------------------------
// GameLogicSubclasses.cpp
//---------------------------------------------------------------------------------
#include "stdafx.h"
#include "GameLogicSubclasses.h"
#include "GameLevel.h"
#include "CharacterController.h"
#include "Bomb.h"
#include "AStar.h"

#pragma region OnPlayerPickupLogics

void CIncreaseLevelOnPlayerPickupLogic::OnPlayerPickup(CLevelObject& object)
{
	CGameLevel::GetInstance().GenerateLevel(CGameLevel::GetInstance().GetDifficulty() + m_levelIncrease);
	COnPlayerPickupLogic::OnPlayerPickup(object);
}

void CAddLivesOnPlayerPickupLogic::OnPlayerPickup(CLevelObject& object)
{
	CGameLevel::GetInstance().AddLives(m_lives);
	COnPlayerPickupLogic::OnPlayerPickup(object);
}

void CEditBombDispenserPickupLogic::OnPlayerPickup(CLevelObject& object)
{
	auto& dispenser = m_editBasic ? CGameLevel::GetInstance().GetPlayer().GetBasicDispenser() : CGameLevel::GetInstance().GetPlayer().GetSpecialDispenser();
	dispenser.MultiplyCooldownMultiplier(m_cooldownMultiplier);
	dispenser.SetMaxActiveBombs(dispenser.GetMaxActiveBombs() + m_addMaxBombs);
	if (m_bombType != BombType::NONE) {
		dispenser.SetBomb(m_bombType);
	}
	COnPlayerPickupLogic::OnPlayerPickup(object);
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
	CLevelCell* cell;
	for (int i = 1; i <= m_range; i++) {
		if (!downBlocked) {
			cell = CGameLevel::GetInstance().GetLevelCell(row - i, col);
			if (cell != nullptr) {
				downBlocked = !cell->Explode();
			}
		}
		if (!upBlocked) {
			cell = CGameLevel::GetInstance().GetLevelCell(row + i, col);
			if (cell != nullptr) {
				upBlocked = !cell->Explode();
			}
		}
		if (!leftBlocked) {
			cell = CGameLevel::GetInstance().GetLevelCell(row, col - i);
			if (cell != nullptr) {
				leftBlocked = !cell->Explode();
			}
		}
		if (!rightBlocked) {
			cell = CGameLevel::GetInstance().GetLevelCell(row, col + i);
			if (cell != nullptr) {
				rightBlocked = !cell->Explode();
			}
		}
	}
}

void CAttackDetonateLogic::Detonate(CLevelObject& object)
{
	m_detonated = true;

	int row, col;
	object.GetPosition(row, col);

	CLevelCell* cell;
	for (int i = -m_radius; i < m_radius; i++) {
		for (int j = -m_radius; j < m_radius; j++) {
			cell = CGameLevel::GetInstance().GetLevelCell(row + i, col + j);
			if (cell != nullptr) {
				cell->Explode(true);
			}
		}
	}
}

#pragma endregion

#pragma region AIInputLogics

void CHugWallAIInput::DecideInput(CCharacterController& character)
{
	if (NeedNewInput(character)) {
		int newDirX, newDirY;
		PrefferedNewDir(newDirX, newDirY);
		int row, col;
		character.GetPosition(row, col);
		if (!CGameLevel::GetInstance().GetLevelCell(row + newDirY, col + newDirX)->Blocked() || CGameLevel::GetInstance().GetLevelCell(row + m_dirY, col + m_dirX)->Blocked()) {
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

void CAStarAIInput::DecideInput(CCharacterController& character)
{
	if (NeedNewInput(character)) {
		int row, col;
		character.GetPosition(row, col);
		int targetRow, targetCol;
		CGameLevel::GetInstance().GetPlayer().GetPosition(targetRow, targetCol);
		CAstar::GetMove(row, col, targetRow, targetCol, m_dirX, m_dirY);
	}
}

#pragma endregion
