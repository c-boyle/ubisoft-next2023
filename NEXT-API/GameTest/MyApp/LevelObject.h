//---------------------------------------------------------------------------------
// LevelObject.h
//---------------------------------------------------------------------------------
#ifndef _LEVELOBJECT_H
#define _LEVELOBJECT_H

#include "..\stdafx.h"
#include "../App/SimpleSprite.h"
#include <memory>
#include "GameLogicSubclasses.h"

class CLevelObject {
public:
	CLevelObject() = default;
	CLevelObject(bool isBlocker, std::unique_ptr<CSimpleSprite> sprite, std::unique_ptr<CExplodeLogic> explodeLogic, std::unique_ptr<COnPlayerPickupLogic> onPlayerPickupLogic = nullptr);
	void Init(int row, int col);
	void Init(float x, float y);
	void GetPosition(int& row, int& col) { row = m_cellRow; col = m_cellCol; };
	void GetPosition(float& x, float& y) { m_sprite->GetPosition(x, y); }
	bool BlocksCell() { return m_isBlocker; }
	bool Explode();
	void OnPlayerPickup();
	void SetExplodeLogic(std::unique_ptr<CExplodeLogic> explodeLogic) { m_explodeLogic = std::move(explodeLogic); }
	virtual void ShiftHorizontally(float xChange);
	virtual void Destroy();
	virtual void Render();

protected:
	std::unique_ptr<CExplodeLogic> m_explodeLogic;
	std::unique_ptr<COnPlayerPickupLogic> m_onPlayerPickupLogic;
	bool m_isBlocker;
	int m_cellRow;
	int m_cellCol;
	std::unique_ptr<CSimpleSprite> m_sprite;
};

#endif