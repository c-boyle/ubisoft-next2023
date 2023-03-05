//---------------------------------------------------------------------------------
// Item.h
//---------------------------------------------------------------------------------
#ifndef _ITEM_H
#define _ITEM_H

#include "..\stdafx.h"
#include "LevelObject.h"

class CItem : public CLevelObject {
public:
	// Inherited via CLevelObject
	virtual bool Explode() override;
	virtual bool BlocksCell() override;
};

#endif