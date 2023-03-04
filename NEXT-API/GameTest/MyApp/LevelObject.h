//---------------------------------------------------------------------------------
// LevelObject.h
//---------------------------------------------------------------------------------
#ifndef _LEVELOBJECT_H
#define _LEVELOBJECT_H

#include "..\stdafx.h"
#include "../App/SimpleSprite.h"
#include <memory>

class CLevelObject {
public:
	virtual void Init(int row, int col);
	virtual void Init(float x, float y);
	/// <returns>True iff this object was exploded</returns>
	virtual bool Explode() = 0;
	virtual bool BlocksCell() = 0;
	virtual void Render();

protected:
	virtual void Destroy();
	virtual CSimpleSprite *GetSprite() = 0;

protected:
	int m_cellRow;
	int m_cellCol;
	std::unique_ptr<CSimpleSprite> m_sprite;

};

#endif