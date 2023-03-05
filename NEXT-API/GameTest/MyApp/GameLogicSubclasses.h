//---------------------------------------------------------------------------------
// GameLogicSubclasses.h
//---------------------------------------------------------------------------------
#ifndef _GAMELOGICSUBCLASSES_H
#define _GAMELOGICSUBCLASSES_H

#include "..\stdafx.h"
#include "GameLogic.h"

#pragma region OnPlayerPickupLogics

class CIncreaseLevelOnPlayerPickupLogic : public COnPlayerPickupLogic {
public:
	CIncreaseLevelOnPlayerPickupLogic(int levelIncrease = 1) : m_levelIncrease(levelIncrease) {};
	// Inherited via COnPlayerPickupLogic
	virtual void OnPlayerPickup() override;

private:
	int m_levelIncrease;

};

#pragma endregion


#pragma region DetonateLogics

class CAxisDetonateLogic : public CDetonateLogic {
public:
	CAxisDetonateLogic(int range) : m_range(range) {}
	virtual void Detonate(CLevelObject& object) override;

private:
	int m_range = 1;

};

#pragma endregion


#pragma region AIInputLogics

class CHugWallAIInput : public CAIInputLogic {
public:
	// Inherited via CAIInputLogic
	virtual void HandleInput(CCharacterController& character) override;

protected:
	void PrefferedNewDir(int& x, int& y);
	int m_dirX = -1;
	int m_dirY = 0;

};

#pragma endregion

#endif