//---------------------------------------------------------------------------------
// Block.cpp
//---------------------------------------------------------------------------------
#include "stdafx.h"
#include "Block.h"
#include "../App/app.h"

bool CBlock::Explode()
{
	return m_blockType != CONCRETE_BLOCK;
}

bool CBlock::BlocksCell()
{
	return true;
}

CSimpleSprite* CBlock::GetSprite()
{
	return App::CreateSprite(".\\MyData\\ConcreteBlock.bmp", 1, 1);
}
