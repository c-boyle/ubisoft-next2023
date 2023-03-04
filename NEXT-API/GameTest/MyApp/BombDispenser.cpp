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
		m_activeBombs.push_back(bomb);
		cell->SetContainedObject(bomb);
	}
}

void CBombDispenser::Update(float dt)
{
	std::vector<int> elementsToRemove;
	for (int i = 0; i < m_activeBombs.size(); i++) {
		if (m_activeBombs[i]->Update(dt)) {
			m_activeBombs[i].reset();
			elementsToRemove.push_back(i);
		}
	}
	for (auto index : elementsToRemove) {
		m_activeBombs.erase(m_activeBombs.begin() + index);
	}
}

void CBombDispenser::Render() {
	for (auto& bomb : m_activeBombs) {
		bomb->Render();
	}
}
