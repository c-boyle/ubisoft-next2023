//---------------------------------------------------------------------------------
// Bomb.cpp
//---------------------------------------------------------------------------------
#include "stdafx.h"
#include "Bomb.h"
#include "../App/app.h"

CBomb::CBomb(float detonationTime) : m_detonationTime(detonationTime) { }

void CBomb::Update(float dt)
{
    m_detonationTime -= dt;
    if (m_detonationTime <= 0.0F) {
        Detonate();
    }
}

bool CBomb::Explode()
{
    Detonate();
    return true;
}

bool CBomb::BlocksCell()
{
    return true;
}

CSimpleSprite* CBomb::GetSprite()
{
    return App::CreateSprite(".\\MyData\\BasicBomb.bmp", 1, 1);
}
