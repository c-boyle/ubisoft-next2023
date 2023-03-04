//---------------------------------------------------------------------------------
// Blocks.cpp
//---------------------------------------------------------------------------------
#include "stdafx.h"
#include "../App/app.h"
#include "Blocks.h"

#pragma region ConcreteBlock

bool CConcreteBlock::Explode()
{
	return false;
}

CSimpleSprite* CConcreteBlock::GetSprite()
{
	return App::CreateSprite(".\\MyData\\ConcreteBlock.bmp", 1, 1);
}

#pragma endregion

#pragma region BrickBlock

bool CBrickBlock::Explode()
{
	if (--m_durability == 0) {
		Destroy();
		return true;
	}
	return false;
}

CSimpleSprite* CBrickBlock::GetSprite()
{
	return App::CreateSprite(".\\MyData\\BrickBlock.bmp", 1, 1);
}

#pragma endregion

