//---------------------------------------------------------------------------------
// Bombs.h
//---------------------------------------------------------------------------------
#ifndef _BOMBS_H
#define _BOMBS_H

#include "..\stdafx.h"
#include "Bomb.h"

class CAxisBomb : public CBomb {
public:
	CAxisBomb(float detonationTime, int range);
	// Inherited via CBomb
	virtual std::unique_ptr<CBomb> GetCopy() override;
	virtual void Detonate() override;

private:
	int m_range = 1;
};

#endif