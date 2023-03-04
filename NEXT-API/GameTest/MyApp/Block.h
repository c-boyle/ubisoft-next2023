//---------------------------------------------------------------------------------
// Block.h
//---------------------------------------------------------------------------------
#ifndef _BLOCK_H
#define _BLOCK_H

#include "..\stdafx.h"
#include "LevelObject.h"

enum BlockType
{
	CONCRETE_BLOCK,
	BRICK_BLOCK,
};

class CBlock : public CLevelObject {
public:
	// Inherited via ILevelObject
	virtual bool Explode() override;
	virtual bool BlocksCell() override;

protected:
	virtual CSimpleSprite* GetSprite() override;

private:
	BlockType m_blockType;	
};

#endif