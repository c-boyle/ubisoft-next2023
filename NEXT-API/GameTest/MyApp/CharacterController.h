//---------------------------------------------------------------------------------
// CharacterController.h
//---------------------------------------------------------------------------------
#ifndef _CHARACTERCONTROLLER_H
#define _CHARACTERCONTROLLER_H

#include "..\stdafx.h"
#include "..\App\app.h"
#include <memory>

enum
{
	ANIM_FORWARDS,
	ANIM_BACKWARDS,
	ANIM_LEFT,
	ANIM_RIGHT,
};

class CCharacterController
{
public:
	CCharacterController();
	void Update(float deltaTime);
	void Render();

private:
	void Move(float moveX, float moveY);
	void HandleInput();
	void AnimateMove(float moveX, float moveY);
	void AnimateMoveX(float moveX);
	void AnimateMoveY(float moveY);

private:
	std::unique_ptr<CSimpleSprite> sprite;
};

#endif