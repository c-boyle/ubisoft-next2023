//---------------------------------------------------------------------------------
// EnemyController.h
//---------------------------------------------------------------------------------
#ifndef _ENEMYCONTROLLER_H
#define _ENEMYCONTROLLER_H

#include "..\stdafx.h"
#include "CharacterController.h"

class CEnemyController : public CCharacterController {
public:
	CEnemyController(bool isBlocker, std::unique_ptr<CSimpleSprite> sprite, std::unique_ptr<CExplodeLogic> explodeLogic,
		std::unique_ptr<CAIInputLogic> aiInputLogic, std::unique_ptr<COnPlayerPickupLogic> onPlayerPickupLogic = nullptr, bool hurtsPlayer = true);
	bool HurtsPlayer() { return m_hurtsPlayer;  }
	// Inherited via CCharacterController
	virtual void DecideInput() override;

protected:
	std::unique_ptr<CAIInputLogic> m_inputLogic;
	bool m_hurtsPlayer;

};

#endif