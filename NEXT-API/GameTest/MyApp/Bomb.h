//---------------------------------------------------------------------------------
// Bomb.h
//---------------------------------------------------------------------------------
#ifndef _BOMB_H
#define _BOMB_H

#include "..\stdafx.h"
#include "LevelObject.h"

enum BombType {
	BASIC_BOMB,
	SUPERBOMB,
	DIRTY_BOMB
	
};

class CBomb : public CLevelObject {
public:
	CBomb(BombType type);
	/// <returns>True iff bomb was detonated</returns>
	bool Update(float dt);
	virtual float GetDetonationTime() { return m_detonationTime; };

protected:
	float m_detonationTime; // Detonation time in ms.
	bool m_detonated = false;
};

#endif