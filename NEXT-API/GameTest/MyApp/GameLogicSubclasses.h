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
	virtual void OnPlayerPickup(CLevelObject& object) override;

private:
	int m_levelIncrease;
};

class CAddLivesOnPlayerPickupLogic : public COnPlayerPickupLogic {
public:
	CAddLivesOnPlayerPickupLogic(int lives = 1) : m_lives(lives) {};
	// Inherited via COnPlayerPickupLogic
	virtual void OnPlayerPickup(CLevelObject& object) override;

private:
	int m_lives;
};

enum BombType;

class CEditBombDispenserPickupLogic : public COnPlayerPickupLogic {
public:
	CEditBombDispenserPickupLogic(bool editBasic, BombType bombType, int addMaxBombs = 0, float cooldownMultiplier = 1.0F)
		: m_editBasic(editBasic), m_cooldownMultiplier(cooldownMultiplier), m_addMaxBombs(addMaxBombs), m_bombType(bombType) {};
	// Inherited via COnPlayerPickupLogic
	virtual void OnPlayerPickup(CLevelObject& object) override;

private:
	bool m_editBasic;
	float m_cooldownMultiplier;
	int m_addMaxBombs;
	BombType m_bombType;
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

class CAttackDetonateLogic : public CDetonateLogic {
public:
	CAttackDetonateLogic(int radius) : m_radius(radius) {}
	virtual void Detonate(CLevelObject& object) override;

private:
	int m_radius = 1;
};

#pragma endregion


#pragma region AIInputLogics

class CHugWallAIInput : public CAIInputLogic {
public:
	// Inherited via CAIInputLogic
	virtual void DecideInput(CCharacterController& character) override;

protected:
	void PrefferedNewDir(int& x, int& y);
};

class CAStarAIInput : public CAIInputLogic {
public:
	CAStarAIInput(std::shared_ptr<CCharacterController> target, bool preferClose = true) : m_target(target), m_preferClose(preferClose) {};
	// Inherited via CAIInputLogic
	virtual void DecideInput(CCharacterController& character) override;

protected:
	bool m_preferClose;
	std::shared_ptr<CCharacterController> m_target;
};

#pragma endregion

#endif