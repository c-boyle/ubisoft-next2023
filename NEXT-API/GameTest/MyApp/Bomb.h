//---------------------------------------------------------------------------------
// Bomb.h
//---------------------------------------------------------------------------------
#ifndef _BOMB_H
#define _BOMB_H

#include "..\stdafx.h"
#include "LevelObject.h"

class CBomb : public CLevelObject {
	using CLevelObject::CLevelObject;
public:
	/// <returns>True iff bomb was detonated</returns>
	bool Update(float dt);
	virtual void Detonate() = 0;
	virtual float GetDetonationTime() { return m_detonationTime; };
	virtual std::unique_ptr<CBomb> GetCopy() = 0;

protected:
	float m_detonationTime; // Detonation time in ms.
	bool m_detonated = false;
};

#endif