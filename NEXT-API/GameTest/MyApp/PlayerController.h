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
	// Inherited via CCharacterController
	virtual void HandleInput() override;

protected:
	virtual CSimpleSprite* GetSprite() override;
	std::unique_ptr<CBombDispenser> m_basicDispenser;
	std::unique_ptr<CBombDispenser> m_specialDispenser;

};

#endif