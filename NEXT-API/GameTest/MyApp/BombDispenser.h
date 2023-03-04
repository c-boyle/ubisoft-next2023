//---------------------------------------------------------------------------------
// BombDispenser.h
//---------------------------------------------------------------------------------
#ifndef _BOMBDISPENSER_H
#define _BOMBDISPENSER_H

#include "..\stdafx.h"
#include "Bomb.h"
#include <vector>
#include <memory>

class CBombDispenser {
public:
	CBombDispenser(BombType bombType) : m_bombType(bombType) {};
	void Dispense(float x, float y);
	void Update(float dt);
private:
	std::vector<std::unique_ptr<CBomb>> m_activeBombs;
	std::vector<float> m_activeBombCooldowns;
	BombType m_bombType;
	float m_cooldownMultiplier = 1.0F;
	int m_maxActiveBombs = 1;
};

#endif