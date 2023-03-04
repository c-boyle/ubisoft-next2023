//---------------------------------------------------------------------------------
// AxisBomb.h
//---------------------------------------------------------------------------------
#ifndef _AXISBOMB_H
#define _AXISBOMB_H

#include "..\stdafx.h"
#include "Bomb.h"

class CAxisBomb : public CBomb {
public:
	CAxisBomb(float detonationTime, int range);
	// Inherited via CBomb
	virtual float GetCooldown() override;
	virtual void Detonate() override;

private:
	int m_range = 1;
};

#endif