//---------------------------------------------------------------------------------
// GameLogic.h
//---------------------------------------------------------------------------------
#ifndef _GAMELOGIC_H
#define _GAMELOGIC_H

#include "..\stdafx.h"
#include <memory>

class CLevelObject;
class CCharacterController;

class CDetonateLogic {
public:
	virtual void Detonate(CLevelObject& object) = 0;
	bool GetDetonated() { return m_detonated; }

protected:
	bool m_detonated = false;
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
	bool GetDetonated();

private:
	std::unique_ptr<CDetonateLogic> m_detonateLogic;
	int m_durability;
	std::shared_ptr<CLevelObject> m_dropOnDestruction;

};

class CAIInputLogic {
public:
	virtual void DecideInput(CCharacterController& character) = 0;

protected:
	virtual bool NeedNewInput(CCharacterController& character);
	int m_dirX = -1;
	int m_dirY = 0;
	

};

#endif