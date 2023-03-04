//---------------------------------------------------------------------------------
// Block.h
//---------------------------------------------------------------------------------
#ifndef _BLOCK_H
#define _BLOCK_H

#include "..\stdafx.h"
#include "LevelObject.h"

class CBlock : public CLevelObject {
public:
	// Inherited via ILevelObject
	virtual bool BlocksCell() override;

};

#endif