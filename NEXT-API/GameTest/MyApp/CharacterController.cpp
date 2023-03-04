//------------------------------------------------------------------------
// CharacterController.cpp
//------------------------------------------------------------------------
#include "stdafx.h"
#include "CharacterController.h"
#include "../App/app.h"
#include "GameLevel.h"

constexpr float speed = 1.3F;

CCharacterController::CCharacterController()
{
	auto sp = App::CreateSprite(".\\MyData\\Player.bmp", 2, 2);
	m_sprite = std::unique_ptr<CSimpleSprite>(sp);
	m_sprite->SetPosition(static_cast<float>(APP_VIRTUAL_WIDTH / 2) + 0.5F, static_cast<float>(APP_VIRTUAL_HEIGHT / 2) + 0.5F);
	m_sprite->SetScale(1.0f);
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
		m_sprite->GetPosition(x, y);
		float targetX = x + moveX;
		float targetY = y + moveY;
		int decimalX = abs(static_cast<int>((targetX / cellSize) * 10)) % 10;
		int decimalY = abs(static_cast<int>((targetY / cellSize) * 10)) % 10;
		bool atCenterOfCellX = decimalX >= 4 && decimalX <= 6;
		bool atCenterOfCellY = decimalY >= 4 && decimalY <= 6;
		float widthBuffer = m_sprite->GetWidth() / 2.0F;
		bool movingLeft = signbit(moveX);
		if (movingLeft) {
			widthBuffer = -widthBuffer;
		}
		float heightBuffer = m_sprite->GetHeight() / 2.0F;
		bool movingDown = signbit(moveY);
		if (movingDown) {
			heightBuffer = -heightBuffer;
		}
		float newX = CGameLevel::GetInstance().IsBlocked(targetX + widthBuffer, y) || !atCenterOfCellY ? x : targetX;
		float newY = CGameLevel::GetInstance().IsBlocked(x, targetY + heightBuffer) || !atCenterOfCellX ? y : targetY;
		m_sprite->SetPosition(newX, newY);
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
		m_sprite->SetFrame(ANIM_RIGHT);
	}
	else if (moveX < 0.0F) {
		m_sprite->SetFrame(ANIM_LEFT);
	}
}

void CCharacterController::AnimateMoveY(float moveY)
{
	if (moveY > 0.0F) {
		m_sprite->SetFrame(ANIM_BACKWARDS);
	}
	else if (moveY < 0.0F) {
		m_sprite->SetFrame(ANIM_FORWARDS);
	}
}

void CCharacterController::Render()
{
	m_sprite->Draw();
	/*
	float x, y;
	m_sprite->GetPosition(x, y);
	char textBuffer[64];
	sprintf(textBuffer, "x: %0.4f y: %0.4f", x / cellSize, y / cellSize);
	App::Print(x, y, textBuffer, 1.0f, 0.0f, 1.0f, GLUT_BITMAP_HELVETICA_10);
	*/
}

void CCharacterController::HandleInput()
{
	Move(App::GetController().GetLeftThumbStickX(), App::GetController().GetLeftThumbStickY());

	if (App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_UP, false))
	{
		m_sprite->SetScale(m_sprite->GetScale() + 0.1f);
	}
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_DOWN, false))
	{
		m_sprite->SetScale(m_sprite->GetScale() - 0.1f);
	}
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_LEFT, false))
	{
		m_sprite->SetAngle(m_sprite->GetAngle() + 0.1f);
	}
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_RIGHT, false))
	{
		m_sprite->SetAngle(m_sprite->GetAngle() - 0.1f);
	}
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_A, true))
	{
		m_sprite->SetAnimation(-1);
	}
}

