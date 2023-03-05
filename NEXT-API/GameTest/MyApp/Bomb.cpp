//---------------------------------------------------------------------------------
// Bomb.cpp
//---------------------------------------------------------------------------------
#include "stdafx.h"
#include "Bomb.h"
#include "../App/app.h"

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
