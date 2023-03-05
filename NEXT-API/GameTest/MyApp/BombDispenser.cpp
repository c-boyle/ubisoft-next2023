//---------------------------------------------------------------------------------
// BombDispenser.cpp
//---------------------------------------------------------------------------------
#include "stdafx.h"
#include "BombDispenser.h"
#include "GameLevel.h"
#include <memory>

void CBombDispenser::Dispense(int row, int col)
{
	if (m_activeBombs.size() < m_maxActiveBombs) {
		auto cell = CGameLevel::GetInstance().GetLevelCell(row, col);
		if (cell->Blocked()) {
			return;
		}
		std::shared_ptr<CBomb> bomb = std::shared_ptr<CBomb>(new CBomb(m_bombType));
		bomb->Init(row, col);
		m_activeBombs.emplace(bomb);
		cell->SetContainedObject(bomb);
	}
}

void CBombDispenser::Update(float dt)
{
	for (auto it = m_activeBombs.begin(); it != m_activeBombs.end(); ) {
		if ((*it)->Update(dt)) {
			it = m_activeBombs.erase(it);
		}
		else {
			++it;
		}
	}
}

void CBombDispenser::Render() {
	for (auto& bomb : m_activeBombs) {
		bomb->Render();
	}
}
