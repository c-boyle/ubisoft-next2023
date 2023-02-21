//------------------------------------------------------------------------
// CharacterController.cpp
//------------------------------------------------------------------------
#include "stdafx.h"
#include "..\App\app.h"
#include "CharacterController.h"

constexpr float speed = 1.3F;

CCharacterController::CCharacterController()
{
	auto sp = App::CreateSprite(".\\TestData\\Test.bmp", 8, 4);
	sprite = std::unique_ptr<CSimpleSprite>(sp);
	sprite->SetPosition(400.0f, 400.0f);
	float speed = 1.0f / 15.0f;
	sprite->CreateAnimation(ANIM_BACKWARDS, speed, { 0,1,2,3,4,5,6,7 });
	sprite->CreateAnimation(ANIM_LEFT, speed, { 8,9,10,11,12,13,14,15 });
	sprite->CreateAnimation(ANIM_RIGHT, speed, { 16,17,18,19,20,21,22,23 });
	sprite->CreateAnimation(ANIM_FORWARDS, speed, { 24,25,26,27,28,29,30,31 });
	sprite->SetScale(1.0f);
}

void CCharacterController::Update(float deltaTime)
{
	sprite->Update(deltaTime);
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
	if (moveX > 0.0F) {
		sprite->SetAnimation(ANIM_RIGHT);
	}
	else if (moveX < 0.0F) {
		sprite->SetAnimation(ANIM_LEFT);
	}
	if (moveY > 0.0F) {
		sprite->SetAnimation(ANIM_FORWARDS);
	}
	else if (moveY < 0.0F) {
		sprite->SetAnimation(ANIM_BACKWARDS);
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

