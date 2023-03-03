//------------------------------------------------------------------------
// CharacterController.cpp
//------------------------------------------------------------------------
#include "stdafx.h"
#include "..\App\app.h"
#include "CharacterController.h"

constexpr float speed = 1.3F;

CCharacterController::CCharacterController()
{
	auto sp = App::CreateSprite(".\\MyData\\Player.bmp", 2, 2);
	sprite = std::unique_ptr<CSimpleSprite>(sp);
	sprite->SetPosition(APP_VIRTUAL_WIDTH / 2, APP_VIRTUAL_HEIGHT / 2);
	sprite->SetScale(1.0f);
}

void CCharacterController::Update(float deltaTime)
{
	//sprite->Update(deltaTime);
	HandleInput();
}

void CCharacterController::Move(float moveX, float moveY)
{
	if (moveX != 0.0F && moveY != 0.0F) {
		moveX *= speed;
		moveY *= speed;
		AnimateMove(moveX, moveY);
		float x, y;
		sprite->GetPosition(x, y);
		sprite->SetPosition(x + moveX, y + moveY);
	}
}

void CCharacterController::AnimateMove(float moveX, float moveY)
{
	if (abs(moveX) > abs(moveY)) {
		AnimateMoveX(moveX);
	}
	else {
		AnimateMoveY(moveY);
	}
}

void CCharacterController::AnimateMoveX(float moveX)
{
	if (moveX > 0.0F) {
		sprite->SetFrame(ANIM_RIGHT);
	}
	else if (moveX < 0.0F) {
		sprite->SetFrame(ANIM_LEFT);
	}
}

void CCharacterController::AnimateMoveY(float moveY)
{
	if (moveY > 0.0F) {
		sprite->SetFrame(ANIM_BACKWARDS);
	}
	else if (moveY < 0.0F) {
		sprite->SetFrame(ANIM_FORWARDS);
	}
}

void CCharacterController::Render()
{
	sprite->Draw();
}

void CCharacterController::HandleInput()
{
	Move(App::GetController().GetLeftThumbStickX(), App::GetController().GetLeftThumbStickY());

	if (App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_UP, false))
	{
		sprite->SetScale(sprite->GetScale() + 0.1f);
	}
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_DOWN, false))
	{
		sprite->SetScale(sprite->GetScale() - 0.1f);
	}
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_LEFT, false))
	{
		sprite->SetAngle(sprite->GetAngle() + 0.1f);
	}
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_RIGHT, false))
	{
		sprite->SetAngle(sprite->GetAngle() - 0.1f);
	}
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_A, true))
	{
		sprite->SetAnimation(-1);
	}
	//------------------------------------------------------------------------
	// Sample Sound.
	//------------------------------------------------------------------------
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_B, true))
	{
		App::PlaySound(".\\TestData\\Test.wav");
	}
}

