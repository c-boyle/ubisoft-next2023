//---------------------------------------------------------------------------------
// Items.h
//---------------------------------------------------------------------------------
#ifndef _ITEMS_H
#define _ITEMS_H

#include "..\stdafx.h"
#include "Item.h"

class CDoorItem : public CItem {
public:
	CDoorItem(int levelIncrease = 1) : m_levelIncrease(levelIncrease) {};
	virtual void OnPlayerPickup() override;

protected:
	virtual CSimpleSprite* GetSprite() override;

private:
	int m_levelIncrease;

};

#endif