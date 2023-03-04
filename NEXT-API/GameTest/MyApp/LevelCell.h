//---------------------------------------------------------------------------------
// LevelCell.h
//---------------------------------------------------------------------------------
#ifndef _LEVELCELL_H
#define _LEVELCELL_H

#include "..\stdafx.h"
#include "LevelObject.h"
#include <memory>

constexpr int cellSize = 32;

class CLevelCell {
public:
	void SetContainedObject(std::shared_ptr<CLevelObject> objectToContain) { m_containedObject = objectToContain; };

	// Inherited via ILevelObject
	bool Explode();
	bool Blocked();
	void Render();
	void ShiftHorizontally(float xChange);
	void Clear();

private:
	std::shared_ptr<CLevelObject> m_containedObject = nullptr;
};

#endif