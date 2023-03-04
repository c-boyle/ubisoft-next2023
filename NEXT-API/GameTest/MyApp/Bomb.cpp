//---------------------------------------------------------------------------------
// Bomb.cpp
//---------------------------------------------------------------------------------
#include "stdafx.h"
#include "Bomb.h"
#include "../App/app.h"

CBomb::CBomb(float detonationTime) : m_detonationTime(detonationTime) { }

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

bool CBomb::Explode()
{
    if (!m_detonated) {
        Detonate();
        Destroy();
    }
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
