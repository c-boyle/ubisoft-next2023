//---------------------------------------------------------------------------------
// LevelObject.h
//---------------------------------------------------------------------------------
#ifndef _LEVELOBJECT_H
#define _LEVELOBJECT_H

#include "..\stdafx.h"
#include "../App/SimpleSprite.h"
#include <memory>
#include "GameLogic.h"

class CLevelObject {
public:
	CLevelObject() = default;
	CLevelObject(bool isBlocker, std::unique_ptr<CSimpleSprite> sprite, CExplodeLogic *explodeLogic);
	void Init(int row, int col);
	void Init(float x, float y);
	void GetPosition(int& row, int& col) { row = m_cellRow; col = m_cellCol; };
	bool BlocksCell() { return m_isBlocker; }
	bool Explode();
	/// <returns>True iff this object was exploded</returns>
	virtual void OnPlayerPickup() {};
	virtual void ShiftHorizontally(float xChange);
	virtual void Destroy();
	virtual void Render();

protected:
	std::unique_ptr<CExplodeLogic> m_explodeLogic;
	bool m_isBlocker;
	int m_cellRow;
	int m_cellCol;
	std::unique_ptr<CSimpleSprite> m_sprite;
};

#endif