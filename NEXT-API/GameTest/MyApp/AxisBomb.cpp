//---------------------------------------------------------------------------------
// AxisBomb.cpp
//---------------------------------------------------------------------------------
#include "stdafx.h"
#include "AxisBomb.h"
#include "GameLevel.h"

CAxisBomb::CAxisBomb(float detonationTime, int range) : CBomb(detonationTime), m_range(range) { }

float CAxisBomb::GetCooldown()
{
	return 1000.0F;
}

void CAxisBomb::Detonate()
{
	bool leftBlocked = false;
	bool rightBlocked = false;
	bool upBlocked = false;
	bool downBlocked = false;
	for (int i = 0; i < m_range; i++) {
		if (!leftBlocked) {
			leftBlocked = !CGameLevel::GetInstance().GetLevelCell(m_cellCol - i, m_cellCol)->Explode();
		}
		if (!rightBlocked) {
			rightBlocked = !CGameLevel::GetInstance().GetLevelCell(m_cellCol + i, m_cellCol)->Explode();
		}
		if (!upBlocked) {
			upBlocked = !CGameLevel::GetInstance().GetLevelCell(m_cellCol, m_cellCol - i)->Explode();
		}
		if (!downBlocked) {
			downBlocked = !CGameLevel::GetInstance().GetLevelCell(m_cellCol, m_cellCol + i)->Explode();
		}
	}
}
