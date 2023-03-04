//---------------------------------------------------------------------------------
// LevelObject.cpp
//---------------------------------------------------------------------------------
#include "stdafx.h"
#include "LevelObject.h"
#include "GameLevel.h"

void CLevelObject::Init(int row, int col)
{
	float x, y;
	CGameLevel::GetInstance().CellToVirtualCoords(row, col, x, y);
	m_cellRow = row;
	m_cellCol = col;
	Init(x, y);
}

void CLevelObject::Init(float x, float y)
{
	m_sprite = std::unique_ptr<CSimpleSprite>(GetSprite());
	m_sprite->SetPosition(x, y);
	m_sprite->SetScale(1.0f);
}

void CLevelObject::Render()
{
	m_sprite->Draw();
}

void CLevelObject::Destroy()
{
	float x, y;
	m_sprite->GetPosition(x, y);
	auto cell = CGameLevel::GetInstance().VirtualCoordsToLevelCell(x, y);
	cell->Clear();
}
