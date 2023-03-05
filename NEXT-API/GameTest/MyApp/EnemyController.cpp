//---------------------------------------------------------------------------------
// EnemyController.cpp
//---------------------------------------------------------------------------------
#include "stdafx.h"
#include "EnemyController.h"

CEnemyController::CEnemyController(bool isBlocker, std::unique_ptr<CSimpleSprite> sprite, std::unique_ptr<CExplodeLogic> explodeLogic,
	std::unique_ptr<CAIInputLogic> aiInputLogic, std::unique_ptr<COnPlayerPickupLogic> onPlayerPickupLogic)
	: CCharacterController(isBlocker, std::move(sprite), std::move(explodeLogic), std::move(onPlayerPickupLogic)), m_inputLogic(std::move(aiInputLogic)) {};

void CEnemyController::HandleInput()
{
	m_inputLogic->HandleInput((*this));
}
