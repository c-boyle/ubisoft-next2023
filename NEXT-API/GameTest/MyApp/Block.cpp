//---------------------------------------------------------------------------------
// Block.cpp
//---------------------------------------------------------------------------------
#include "stdafx.h"
#include "Block.h"
#include "../App/app.h"
#include <memory>

CBlock::CBlock(int x, int y, BlockType type)
{
	m_blockType = type;
	CSimpleSprite* sp = nullptr;
	if (m_blockType == BlockType::CONCRETE_BLOCK) {
		sp = App::CreateSprite(".\\MyData\\ConcreteBlock.bmp", 1, 1);
	}
	else if (m_blockType == BlockType::BRICK_BLOCK) {
		sp = App::CreateSprite(".\\MyData\\BrickBlock.bmp", 1, 1);
	}
	m_sprite = std::unique_ptr<CSimpleSprite>(sp);
	m_sprite->SetPosition(static_cast<float>(x), static_cast<float>(y));
	m_sprite->SetScale(1.0f);
}

bool CBlock::Explode()
{
	return m_blockType == CONCRETE_BLOCK;
}

bool CBlock::BlocksCell()
{
	return true;
}

void CBlock::OnPlayerEnter()
{
}

void CBlock::Render()
{
	m_sprite->Draw();
}
