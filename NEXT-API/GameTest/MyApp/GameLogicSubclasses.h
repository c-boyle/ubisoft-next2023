//---------------------------------------------------------------------------------
// GameLogicSubclasses.h
//---------------------------------------------------------------------------------
#ifndef _GAMELOGICSUBCLASSES_H
#define _GAMELOGICSUBCLASSES_H

#include "..\stdafx.h"
#include "GameLogic.h"

#pragma region ExplodeLogics

#pragma endregion


#pragma region DetonateLogics

class CAxisDetonateLogic : public CDetonateLogic {
public:
	CAxisDetonateLogic(int range) : m_range(range) {}
	virtual void Detonate(CLevelObject& object) override;

private:
	int m_range = 1;

};

#pragma endregion


#endif