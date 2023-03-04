//---------------------------------------------------------------------------------
// PlayerController.h
//---------------------------------------------------------------------------------
#ifndef _PLAYERCONTROLLER_H
#define _PLAYERCONTROLLER_H

#include "..\stdafx.h"
#include "CharacterController.h"
#include "BombDispenser.h"

class CPlayerController : public CCharacterController {
public:
	CPlayerController();

	void GetPosition(float& x, float& y) { m_sprite->GetPosition(x, y); }
	void SetDead(bool dead) { m_dead = dead; }

	// Inherited via CLevelObject
	virtual void Render() override;

	// Inherited via CCharacterController
	virtual void HandleInput() override;
	virtual void Update(float deltaTime) override;

protected:
	virtual void Move(float moveX, float moveY) override;
	virtual CSimpleSprite* GetSprite() override;
	std::unique_ptr<CBombDispenser> m_basicDispenser;
	std::unique_ptr<CBombDispenser> m_specialDispenser;
	bool m_dead = false;

};

#endif