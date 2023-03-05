//---------------------------------------------------------------------------------
// LevelObject.cpp
//---------------------------------------------------------------------------------
#include "stdafx.h"
#include "LevelObject.h"
#include "GameLevel.h"

CLevelObject::CLevelObject(bool isBlocker, std::unique_ptr<CSimpleSprite> sprite, CExplodeLogic *explodeLogic)
	: m_isBlocker(isBlocker), m_explodeLogic(std::unique_ptr<CExplodeLogic>(explodeLogic)), m_sprite(std::move(sprite)) {}

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
	m_sprite->SetPosition(x, y);
	m_sprite->SetScale(1.0f);
}

void CLevelObject::Render()
{
	m_sprite->Draw();
}

bool CLevelObject::Explode()
{
	return m_explodeLogic != nullptr && m_explodeLogic->Explode(*this);
}

void CLevelObject::ShiftHorizontally(float xChange)
{
	float x, y;
	m_sprite->GetPosition(x, y);
	m_sprite->SetPosition(x - xChange, y);
}

void CLevelObject::Destroy()
{
	auto cell = CGameLevel::GetInstance().GetLevelCell(m_cellRow, m_cellCol);
	cell->Clear(true, true);
}
