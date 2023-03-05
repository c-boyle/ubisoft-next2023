//---------------------------------------------------------------------------------
// LevelCell.h
//---------------------------------------------------------------------------------
#ifndef _LEVELCELL_H
#define _LEVELCELL_H

#include "..\stdafx.h"
#include "LevelObject.h"
#include "CharacterController.h"
#include <memory>
#include <unordered_set>

constexpr int cellSize = 32;

class CLevelCell {
public:
	void SetContainedObject(std::shared_ptr<CLevelObject> objectToContain) { m_containedObject = objectToContain; };
	void AddContainedCharacter(std::shared_ptr<CCharacterController> characterToContain);

	
	bool Explode(bool enemiesOnly = false);
	bool Blocked();
	void Render();
	void OnPlayerPickup();
	void ShiftHorizontally(float xChange);
	void Clear(bool clearObject, bool clearCharacter = false);
	void Clear(bool clearObject, std::shared_ptr<CCharacterController> characterToClear);

private:
	std::shared_ptr<CLevelObject> m_containedObject = nullptr;
	std::unordered_set<std::shared_ptr<CCharacterController>> m_containedCharacters;
};

#endif