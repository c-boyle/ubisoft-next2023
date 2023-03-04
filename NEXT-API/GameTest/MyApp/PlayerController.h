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

	// Inherited via CLevelObject
	virtual void Render() override;

	// Inherited via CCharacterController
	virtual void HandleInput() override;
	virtual void Update(float deltaTime) override;

protected:
	virtual CSimpleSprite* GetSprite() override;
	std::unique_ptr<CBombDispenser> m_basicDispenser;
	std::unique_ptr<CBombDispenser> m_specialDispenser;

};

#endif