//---------------------------------------------------------------------------------
// EnemyController.cpp
//---------------------------------------------------------------------------------
#include "stdafx.h"
#include "EnemyController.h"
#include "GameLevel.h"

CEnemyController::CEnemyController(bool isBlocker, std::unique_ptr<CSimpleSprite> sprite, std::unique_ptr<CExplodeLogic> explodeLogic,
	std::unique_ptr<CAIInputLogic> aiInputLogic, std::unique_ptr<COnPlayerPickupLogic> onPlayerPickupLogic, bool hurtsPlayer)
	: CCharacterController(isBlocker, std::move(sprite), std::move(explodeLogic), std::move(onPlayerPickupLogic)), m_inputLogic(std::move(aiInputLogic)), m_hurtsPlayer(hurtsPlayer) {};

void CEnemyController::DecideInput()
{
	m_inputLogic->DecideInput((*this));
}
