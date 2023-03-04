//---------------------------------------------------------------------------------
// LevelCell.cpp
//---------------------------------------------------------------------------------
#include "stdafx.h"
#include "LevelCell.h"

bool CLevelCell::Blocked()
{
	if (m_containedObject != nullptr) {
		return m_containedObject->BlocksCell();
	}
	return false;
}

void CLevelCell::Render()
{
	if (m_containedObject != nullptr) {
		m_containedObject->Render();
	}
}

bool CLevelCell::Explode()
{
	if (m_containedObject != nullptr) {
		return m_containedObject->Explode();
	}
	return true;
}
