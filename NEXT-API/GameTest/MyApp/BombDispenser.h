//---------------------------------------------------------------------------------
// BombDispenser.h
//---------------------------------------------------------------------------------
#ifndef _BOMBDISPENSER_H
#define _BOMBDISPENSER_H

#include "..\stdafx.h"
#include "Bomb.h"
#include <set>
#include <memory>

class CBombDispenser {
public:
	CBombDispenser(std::unique_ptr<CBomb> bomb, int maxActiveBombs) : m_bomb(std::move(bomb)), m_maxActiveBombs(maxActiveBombs) {};
	void Dispense(float x, float y);
	void Update(float dt);
	void Render();

private:
	std::set<std::shared_ptr<CBomb>> m_activeBombs;
	std::unique_ptr<CBomb> m_bomb;
	float m_cooldownMultiplier = 1.0F;
	int m_maxActiveBombs = 1;
};

#endif