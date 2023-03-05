//---------------------------------------------------------------------------------
// GameLogic.h
//---------------------------------------------------------------------------------
#ifndef _GAMELOGIC_H
#define _GAMELOGIC_H

#include "..\stdafx.h"
#include <memory>

class CLevelObject;

class CDetonateLogic {
public:
	virtual void Detonate(CLevelObject& object) = 0;
};

class COnPlayerPickupLogic {
public:
	virtual void OnPlayerPickup() = 0;
};

class CExplodeLogic {
public:
	CExplodeLogic(std::unique_ptr<CDetonateLogic> detonateLogic = nullptr, std::shared_ptr<CLevelObject> dropOnDestruction = nullptr, int durability = 1);
	virtual ~CExplodeLogic();
	bool Explode(CLevelObject& detonatingObject);

private:
	std::unique_ptr<CDetonateLogic> m_detonateLogic;
	int m_durability;
	std::shared_ptr<CLevelObject> m_dropOnDestruction;

};

#endif