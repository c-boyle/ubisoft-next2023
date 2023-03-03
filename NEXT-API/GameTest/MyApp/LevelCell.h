//---------------------------------------------------------------------------------
// LevelCell.h
//---------------------------------------------------------------------------------
#ifndef _LEVELCELL_H
#define _LEVELCELL_H

#include "..\stdafx.h"
#include "LevelObject.h"
#include <memory>

class CLevelCell : public CLevelObject {
public:
	void SetContainedObject(CLevelObject *objectToContain) { m_containedObject = std::unique_ptr<CLevelObject>(objectToContain); };

	// Inherited via ILevelObject
	virtual bool Explode() override;
	virtual bool BlocksCell() override;
	virtual void OnPlayerEnter() override;
	virtual void Render() override;

private:
	std::unique_ptr<CLevelObject> m_containedObject = nullptr;
};

#endif