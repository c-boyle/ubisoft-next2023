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
	CBlock(int x, int y, BlockType type);

	// Inherited via ILevelObject
	virtual bool Explode() override;
	virtual bool BlocksCell() override;
	virtual void OnPlayerEnter() override;
	virtual void Render() override;

private:
	BlockType m_blockType;	
};

#endif