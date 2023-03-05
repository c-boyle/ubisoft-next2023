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
	void GetPosition(float& x, float& y) { m_sprite->GetPosition(x, y); }
	void SetDead(bool dead) { m_dead = dead; }
	void SetBasicDispenser(BombType bombType);
	void SetSpecialDispenser(BombType bombType);

	// Inherited via CLevelObject
	virtual void ShiftHorizontally(float xChange) override {};

	// Inherited via CCharacterController
	virtual void HandleInput() override;
	virtual void Update(float deltaTime) override;
	virtual void Render() override;

protected:
	virtual void Move(float moveX, float moveY) override;
	std::unique_ptr<CBombDispenser> m_basicDispenser;
	std::unique_ptr<CBombDispenser> m_specialDispenser;
	bool m_dead = false;

};

#endif