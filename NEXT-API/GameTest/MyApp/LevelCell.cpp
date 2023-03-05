//---------------------------------------------------------------------------------
// LevelCell.cpp
//---------------------------------------------------------------------------------
#include "stdafx.h"
#include "LevelCell.h"
#include "GameLevel.h"
#include "EnemyController.h"

bool CLevelCell::Blocked()
{
	if (m_containedObject != nullptr) {
		return m_containedObject->BlocksCell();
	}
	for (auto& character : m_containedCharacters) {
		if (character->BlocksCell()) {
			return true;
		}
	}
	return false;
}

void CLevelCell::Render()
{
	if (m_containedObject != nullptr) {
		m_containedObject->Render();
	}
	for (auto& character : m_containedCharacters) {
		character->Render();
	}
}

void CLevelCell::OnPlayerPickup()
{
	for (auto& character : m_containedCharacters) {
		character->OnPlayerPickup();
	}
	if (m_containedObject != nullptr) {
		m_containedObject->OnPlayerPickup();
	}
}

void CLevelCell::ShiftHorizontally(float xChange)
{
	for (auto& character : m_containedCharacters) {
		character->ShiftHorizontally(xChange);
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
		m_containedCharacters.clear();
	}
}

void CLevelCell::Clear(bool clearObject, std::shared_ptr<CCharacterController> characterToClear)
{
	if (clearObject) {
		m_containedObject.reset();
	}
	m_containedCharacters.erase(characterToClear);
}

void CLevelCell::AddContainedCharacter(std::shared_ptr<CCharacterController> characterToContain)
{
	m_containedCharacters.emplace(characterToContain);
	CPlayerController* player = nullptr;
	int hurtCount = 0;
	for (auto& character : m_containedCharacters) {
		if (player == nullptr) {
			player = dynamic_cast<CPlayerController*>(character.get());
			if (player != nullptr) {
				continue;
			}
		}
		CEnemyController* enemy = dynamic_cast<CEnemyController*>(character.get());
		if (enemy->HurtsPlayer()) {
			hurtCount++;
		}
	}
	while (player != nullptr && hurtCount > 0) {
		player->Explode();
		--hurtCount;
	}
}

bool CLevelCell::Explode()
{
	for (auto it = m_containedCharacters.begin(); it != m_containedCharacters.end(); ) {
		if ((*it)->Explode()) {
			it = m_containedCharacters.erase(it);
		}
		else {
			++it;
		}
	}
	if (m_containedObject != nullptr) {
		return m_containedObject->Explode();
	}
	return true;
}
