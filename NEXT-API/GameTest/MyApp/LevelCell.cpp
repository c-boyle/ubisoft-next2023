//---------------------------------------------------------------------------------
// LevelCell.cpp
//---------------------------------------------------------------------------------
#include "stdafx.h"
#include "LevelCell.h"
#include "GameLevel.h"

bool CLevelCell::Blocked()
{
	if (m_containedObject != nullptr) {
		return m_containedObject->BlocksCell();
	}
	if (m_containedCharacter != nullptr) {
		return m_containedCharacter->BlocksCell();
	}
	return false;
}

void CLevelCell::Render()
{
	if (m_containedObject != nullptr) {
		m_containedObject->Render();
	}
	if (m_containedCharacter != nullptr) {
		m_containedCharacter->Render();
	}
}

void CLevelCell::OnPlayerPickup()
{
	if (m_containedCharacter != nullptr) {
		m_containedCharacter->OnPlayerPickup();
	}
	if (m_containedObject != nullptr) {
		m_containedObject->OnPlayerPickup();
	}
}

void CLevelCell::ShiftHorizontally(float xChange)
{
	if (m_containedCharacter != nullptr) {
		m_containedCharacter->ShiftHorizontally(xChange);
	}
	if (m_containedObject != nullptr) {
		m_containedObject->ShiftHorizontally(xChange);
	}
}

void CLevelCell::Clear(bool clearObject, bool clearCharacter)
{
	if (clearObject) {
		m_containedObject.reset();
	}
	if (clearCharacter) {
		m_containedCharacter.reset();
	}
}

bool CLevelCell::Explode()
{
	if (m_containedCharacter != nullptr) {
		m_containedCharacter->Explode();
	}
	if (m_containedObject != nullptr) {
		return m_containedObject->Explode();
	}
	return true;
}
