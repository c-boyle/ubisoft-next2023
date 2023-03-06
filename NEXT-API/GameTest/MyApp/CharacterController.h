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

class CCharacterController : public CLevelObject, public std::enable_shared_from_this<CCharacterController>
{
	using CLevelObject::CLevelObject;
public:
	virtual void Update(float deltaTime);
	virtual void Destroy() override;
	virtual void Move(float moveX, float moveY);

protected:
	virtual void DecideInput() = 0;
	float m_speed = 1.3F;

private:
	void AnimateMove(float moveX, float moveY);
	void AnimateMoveX(float moveX);
	void AnimateMoveY(float moveY);
	

};

#endif