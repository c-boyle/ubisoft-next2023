//---------------------------------------------------------------------------------
// Bomb.h
//---------------------------------------------------------------------------------
#ifndef _BOMB_H
#define _BOMB_H

#include "..\stdafx.h"
#include "LevelObject.h"

enum BombType {
	SUPERBOMB,
	DIRTY_BOMB,
	AXIS,
};

class CBomb : public CLevelObject {
public:
	CBomb(float detonationTime);
	void Update(float dt);
	virtual void Detonate() = 0;
	virtual float GetDetonationTime() { return m_detonationTime; };
	virtual std::unique_ptr<CBomb> GetCopy() = 0;

	// Inherited via CLevelObject
	virtual bool Explode() override;
	virtual bool BlocksCell() override;
	
protected:
	virtual CSimpleSprite* GetSprite() override;

protected:
	float m_detonationTime; // Detonation time in ms.
};

#endif