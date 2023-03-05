//---------------------------------------------------------------------------------
// BombDispenser.h
//---------------------------------------------------------------------------------
#ifndef _BOMBDISPENSER_H
#define _BOMBDISPENSER_H

#include "..\stdafx.h"
#include "Bomb.h"
#include <unordered_set>
#include <memory>

class CBombDispenser {
public:
	CBombDispenser(BombType bombType) : m_bombType(bombType) {}
	void SetBomb(BombType bombType) { m_bombType = bombType; }
	void Dispense(int row, int col);
	void Update(float dt);
	void Render();

private:
	std::unordered_set<std::shared_ptr<CBomb>> m_activeBombs;
	BombType m_bombType;
	float m_cooldownMultiplier = 1.0F;
	int m_maxActiveBombs = 1;
};

#endif