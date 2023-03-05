//---------------------------------------------------------------------------------
// Blocks.h
//---------------------------------------------------------------------------------
#ifndef _BLOCKS_H
#define _BLOCKS_H

#include "..\stdafx.h"
#include "Block.h"
#include "Items.h"

class CConcreteBlock : public CBlock {
public:
	// Inherited via CBlock
	virtual bool Explode() override;

protected:
	virtual CSimpleSprite* GetSprite() override;

};

class CBrickBlock : public CBlock {
public:
	CBrickBlock(int durability) : m_durability(durability) {};
	// Inherited via CBlock
	virtual bool Explode() override;

protected:
	virtual CSimpleSprite* GetSprite() override;

private:
	int m_durability;

};

class CItemBlock : public CBrickBlock {
public:
	CItemBlock(int durability, CItem* item) : CBrickBlock(durability), m_item(std::unique_ptr<CItem>(item)) {};
	// Inherited via CBlock
	virtual bool Explode() override;

private:
	std::unique_ptr<CItem> m_item;
};

#endif