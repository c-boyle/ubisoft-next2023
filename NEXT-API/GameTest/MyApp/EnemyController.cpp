//---------------------------------------------------------------------------------
// EnemyController.cpp
//---------------------------------------------------------------------------------
#include "stdafx.h"
#include "EnemyController.h"
#include "../App/app.h"

void CEnemyController::HandleInput()
{
	Move(0.0F, -1.0F);
}

CSimpleSprite* CEnemyController::GetSprite()
{
	auto sp = App::CreateSprite(".\\MyData\\BaseCharacter.bmp", 2, 2);
	sp->SetColor(1.0F, 0.0F, 0.0F);
	return sp;
}
