//---------------------------------------------------------------------------------
// BombDispenser.cpp
//---------------------------------------------------------------------------------
#include "stdafx.h"
#include "BombDispenser.h"
#include "GameLevel.h"
#include "AxisBomb.h"
#include <memory>

void CBombDispenser::Dispense(float x, float y)
{
	if (m_activeBombs.size() < m_maxActiveBombs) {
		int row, col;
		CGameLevel::GetInstance().VirtualCoordsToCell(x, y, row, col);
		auto cell = CGameLevel::GetInstance().GetLevelCell(row, col);
		if (cell->Blocked()) {
			return;
		}
		std::unique_ptr<CBomb> bomb = nullptr;
		switch (m_bombType) {
		case BombType::AXIS:
			bomb = std::make_unique<CAxisBomb>(3000.0F, 1);
			bomb->Init(row, col);
			break;
		case BombType::DIRTY_BOMB:
			break;
		case BombType::SUPERBOMB:
			break;
		default:
			break;
		}
		m_activeBombCooldowns.push_back(bomb->GetCooldown());
		m_activeBombs.push_back(std::move(bomb));
	}
}

void CBombDispenser::Update(float dt)
{
	std::vector<int> elementsToRemove;
	for (int i = 0; i < m_activeBombCooldowns.size(); i++) {
		m_activeBombCooldowns[i] -= dt;
		if (m_activeBombCooldowns[i] <= 0.0F) {
			m_activeBombs[i]->Detonate();
			elementsToRemove.push_back(i);
		}
	}
	for (auto index : elementsToRemove) {
		m_activeBombCooldowns.erase(m_activeBombCooldowns.begin() + index);
		m_activeBombs.erase(m_activeBombs.begin() + index);
	}
}

void CBombDispenser::Render() {
	for (auto& bomb : m_activeBombs) {
		bomb->Render();
	}
}
