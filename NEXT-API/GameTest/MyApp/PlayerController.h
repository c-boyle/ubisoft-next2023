//---------------------------------------------------------------------------------
// PlayerController.h
//---------------------------------------------------------------------------------
#ifndef _PLAYERCONTROLLER_H
#define _PLAYERCONTROLLER_H

#include "..\stdafx.h"
#include "CharacterController.h"
#include "BombDispenser.h"

class CPlayerController : public CCharacterController {
	using CCharacterController::CCharacterController;
public:
	void SetDead(bool dead) { m_dead = dead; }
	void SetBasicDispenser(BombType bombType);
	void SetSpecialDispenser(BombType bombType);
	void SetBasicDispenserMaxBombs(int maxBombs) { m_basicDispenser->SetMaxActiveBombs(maxBombs); }

	// Inherited via CLevelObject
	virtual void ShiftHorizontally(float xChange) override {};

	// Inherited via CCharacterController
	virtual void DecideInput() override;
	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void Move(float moveX, float moveY) override;

protected:
	std::unique_ptr<CBombDispenser> m_basicDispenser;
	std::unique_ptr<CBombDispenser> m_specialDispenser;
	bool m_dead = false;

};

#endif