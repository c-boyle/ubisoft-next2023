//---------------------------------------------------------------------------------
// EnemyController.h
//---------------------------------------------------------------------------------
#ifndef _ENEMYCONTROLLER_H
#define _ENEMYCONTROLLER_H

#include "..\stdafx.h"
#include "CharacterController.h"

class CEnemyController : public CCharacterController {
	using CCharacterController::CCharacterController;
public:
	// Inherited via CCharacterController
	virtual void HandleInput() override;

};

#endif