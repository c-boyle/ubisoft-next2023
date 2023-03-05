//---------------------------------------------------------------------------------
// GameLogicSubclasses.cpp
//---------------------------------------------------------------------------------
#include "stdafx.h"
#include "GameLogicSubclasses.h"
#include "GameLevel.h"

void CAxisDetonateLogic::Detonate(CLevelObject& object)
{
	bool leftBlocked = false;
	bool rightBlocked = false;
	bool upBlocked = false;
	bool downBlocked = false;

	int row, col;
	object.GetPosition(row, col);

	CGameLevel::GetInstance().GetLevelCell(row, col)->Explode();
	for (int i = 1; i <= m_range; i++) {
		if (!downBlocked) {
			downBlocked = !CGameLevel::GetInstance().GetLevelCell(row - i, col)->Explode();
		}
		if (!upBlocked) {
			upBlocked = !CGameLevel::GetInstance().GetLevelCell(row + i, col)->Explode();
		}
		if (!leftBlocked) {
			leftBlocked = !CGameLevel::GetInstance().GetLevelCell(row, col - i)->Explode();
		}
		if (!rightBlocked) {
			rightBlocked = !CGameLevel::GetInstance().GetLevelCell(row, col + i)->Explode();
		}
	}
}
