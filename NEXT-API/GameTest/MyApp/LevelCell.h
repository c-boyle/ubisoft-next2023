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
	void SetContainedObject(CLevelObject *objectToContain) { m_containedObject = std::unique_ptr<CLevelObject>(objectToContain); };

	// Inherited via ILevelObject
	bool Explode();
	bool Blocked();
	void Render();
	void Clear();

private:
	std::unique_ptr<CLevelObject> m_containedObject = nullptr;
};

#endif