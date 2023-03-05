//---------------------------------------------------------------------------------
// Blocks.cpp
//---------------------------------------------------------------------------------
#include "stdafx.h"
#include "../App/app.h"
#include "Blocks.h"
#include "GameLevel.h"

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

bool CItemBlock::Explode()
{
	int row = m_cellRow;
	int col = m_cellCol;
	m_item->Init(m_cellRow, m_cellCol);
	std::unique_ptr<CItem> item = std::move(m_item);

	bool exploded = CBrickBlock::Explode();

	CGameLevel::GetInstance().GetLevelCell(row, col)->SetContainedObject(std::move(item));
	
	return exploded;
}
