//---------------------------------------------------------------------------------
// Bombs.cpp
//---------------------------------------------------------------------------------
#include "stdafx.h"
#include "Bombs.h"
#include "GameLevel.h"

#pragma region AxisBomb

CAxisBomb::CAxisBomb(float detonationTime, int range) : CBomb(detonationTime), m_range(range) { }

void CAxisBomb::Detonate()
{
	m_detonated = true;
	bool leftBlocked = false;
	bool rightBlocked = false;
	bool upBlocked = false;
	bool downBlocked = false;
	for (int i = 1; i <= m_range; i++) {
		if (!downBlocked) {
			downBlocked = !CGameLevel::GetInstance().GetLevelCell(m_cellRow - i, m_cellCol)->Explode();
		}
		if (!upBlocked) {
			upBlocked = !CGameLevel::GetInstance().GetLevelCell(m_cellRow + i, m_cellCol)->Explode();
		}
		if (!leftBlocked) {
			leftBlocked = !CGameLevel::GetInstance().GetLevelCell(m_cellRow, m_cellCol - i)->Explode();
		}
		if (!rightBlocked) {
			rightBlocked = !CGameLevel::GetInstance().GetLevelCell(m_cellRow, m_cellCol + i)->Explode();
		}
	}
}

std::unique_ptr<CBomb> CAxisBomb::GetCopy()
{
	return std::make_unique<CAxisBomb>(CAxisBomb(m_detonationTime, m_range));
}

#pragma endregion

