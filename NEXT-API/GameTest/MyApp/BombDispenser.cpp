//---------------------------------------------------------------------------------
// BombDispenser.cpp
//---------------------------------------------------------------------------------
#include "stdafx.h"
#include "BombDispenser.h"
#include "GameLevel.h"
#include "Bombs.h"
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
		std::shared_ptr<CBomb> bomb = std::move(m_bomb->GetCopy());
		bomb->Init(row, col);
		m_activeBombs.insert(bomb);
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
