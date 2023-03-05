//---------------------------------------------------------------------------------
// Bomb.cpp
//---------------------------------------------------------------------------------
#include "stdafx.h"
#include "Bomb.h"
#include "GameLogicSubclasses.h"

CBomb::CBomb(BombType type)
{
	m_isBlocker = true;
	m_sprite = std::unique_ptr<CSimpleSprite>(new CSimpleSprite(".\\MyData\\BasicBomb.bmp", 1, 1));
	std::unique_ptr<CDetonateLogic> detonationLogic;
	switch (type) {
	case BombType::BASIC_BOMB:
		detonationLogic = std::unique_ptr<CDetonateLogic>(new CAxisDetonateLogic(1));
		m_detonationTime = 2000.0F;
		break;
	case BombType::SUPERBOMB:
		detonationLogic = std::unique_ptr<CDetonateLogic>(new CAxisDetonateLogic(3));
		m_detonationTime = 4000.0F;
		break;
	case BombType::DIRTY_BOMB:
		break;
	}
	m_explodeLogic = std::unique_ptr<CExplodeLogic>(new CExplodeLogic(std::move(detonationLogic)));
}

bool CBomb::Update(float dt)
{
	if (m_detonated) {
		return true;
	}
	m_detonationTime -= dt;
	if (m_detonationTime <= 0.0F) {
		return Explode();
	}
	return false;
}
