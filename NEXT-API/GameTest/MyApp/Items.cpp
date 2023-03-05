//---------------------------------------------------------------------------------
// Items.cpp
//---------------------------------------------------------------------------------
#include "stdafx.h"
#include "Items.h"
#include "GameLevel.h"
#include "../App/app.h"

#pragma region CDoorItem

void CDoorItem::OnPlayerPickup()
{
	CGameLevel::GetInstance().GenerateLevel(CGameLevel::GetInstance().GetDifficulty() + m_levelIncrease);
}

CSimpleSprite* CDoorItem::GetSprite()
{
	return App::CreateSprite(".\\MyData\\DoorItem.bmp", 1, 1);
}

#pragma endregion
