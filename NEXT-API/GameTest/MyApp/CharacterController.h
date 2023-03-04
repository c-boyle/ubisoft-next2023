//---------------------------------------------------------------------------------
// CharacterController.h
//---------------------------------------------------------------------------------
#ifndef _CHARACTERCONTROLLER_H
#define _CHARACTERCONTROLLER_H

#include "..\stdafx.h"
#include "../App/SimpleSprite.h"
#include "LevelObject.h"
#include <memory>

enum
{
	ANIM_FORWARDS,
	ANIM_BACKWARDS,
	ANIM_LEFT,
	ANIM_RIGHT,
};

class CCharacterController : public CLevelObject
{
public:
	virtual void Update(float deltaTime);
	// Inherited via CLevelObject
	virtual bool Explode() override;
	virtual bool BlocksCell() override;

protected:
	virtual void Move(float moveX, float moveY);
	virtual void HandleInput() = 0;

private:
	void AnimateMove(float moveX, float moveY);
	void AnimateMoveX(float moveX);
	void AnimateMoveY(float moveY);
	

};

#endif