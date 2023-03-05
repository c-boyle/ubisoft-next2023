//---------------------------------------------------------------------------------
// LevelCell.h
//---------------------------------------------------------------------------------
#ifndef _LEVELCELL_H
#define _LEVELCELL_H

#include "..\stdafx.h"
#include "LevelObject.h"
#include "CharacterController.h"
#include <memory>

constexpr int cellSize = 32;

class CLevelCell {
public:
	void SetContainedObject(std::shared_ptr<CLevelObject> objectToContain) { m_containedObject = objectToContain; };
	void SetContainedCharacter(std::shared_ptr<CCharacterController> characterToContain) { m_containedCharacter = std::move(characterToContain); }

	
	bool Explode();
	bool Blocked();
	void Render();
	void OnPlayerPickup();
	void ShiftHorizontally(float xChange);
	void Clear(bool clearObject, bool clearCharacter = true);

private:
	std::shared_ptr<CLevelObject> m_containedObject = nullptr;
	std::shared_ptr<CCharacterController> m_containedCharacter = nullptr;
};

#endif