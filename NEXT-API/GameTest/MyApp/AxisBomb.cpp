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
		if (!leftBlocked) {
			leftBlocked = !CGameLevel::GetInstance().GetLevelCell(m_cellRow, m_cellCol + i)->Explode();
		}
	}
}
