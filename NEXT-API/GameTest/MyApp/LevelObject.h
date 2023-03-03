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
	/// <returns>True iff this object was exploded</returns>
	virtual bool Explode() = 0;
	virtual bool BlocksCell() = 0;
	virtual void OnPlayerEnter() = 0;
	virtual void Render() = 0;

protected:
	std::unique_ptr<CSimpleSprite> m_sprite;
};

#endif