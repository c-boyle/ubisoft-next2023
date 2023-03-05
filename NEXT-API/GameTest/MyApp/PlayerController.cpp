//---------------------------------------------------------------------------------
// PlayerController.cpp
//---------------------------------------------------------------------------------
#include "stdafx.h"
#include "PlayerController.h"
#include "../App/app.h"
#include "Bombs.h"
#include "GameLevel.h"

constexpr int levelLeftBuffer = APP_VIRTUAL_WIDTH / 2;
constexpr int levelRightBuffer = levelWidth - levelLeftBuffer;

CPlayerController::CPlayerController()
{
	m_basicDispenser = std::unique_ptr<CBombDispenser>(new CBombDispenser(std::unique_ptr<CBomb>(new CAxisBomb(1000.0F, 1)), 2));
	m_specialDispenser = std::unique_ptr<CBombDispenser>(new CBombDispenser(std::unique_ptr<CBomb>(new CAxisBomb(1000.0F, 2)), 1));
}

void CPlayerController::Render()
{
	m_basicDispenser->Render();
	m_specialDispenser->Render();
	CLevelObject::Render();
}

void CPlayerController::HandleInput()
{
	if (m_dead) {
		if (App::GetController().CheckButton(XINPUT_GAMEPAD_A, true))
		{
			CGameLevel::GetInstance().GenerateLevel(0);
			m_dead = false;
		}
		return;
	}
	Move(App::GetController().GetLeftThumbStickX(), App::GetController().GetLeftThumbStickY());

	if (App::GetController().CheckButton(XINPUT_GAMEPAD_A, true))
	{
		float x, y;
		m_sprite->GetPosition(x, y);
		m_basicDispenser->Dispense(x, y);
	}
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_B, true))
	{
		float x, y;
		m_sprite->GetPosition(x, y);
		m_specialDispenser->Dispense(x, y);
	}
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_X, true))
	{
		float x, y;
		m_sprite->GetPosition(x, y);
		CGameLevel::GetInstance().VirtualCoordsToLevelCell(x, y)->OnPlayerPickup();
	}
}

void CPlayerController::Update(float deltaTime)
{
	CCharacterController::Update(deltaTime);
	m_basicDispenser->Update(deltaTime);
	m_specialDispenser->Update(deltaTime);
}

void CPlayerController::Move(float moveX, float moveY)
{
	float oldX, oldY;
	m_sprite->GetPosition(oldX, oldY);
	CCharacterController::Move(moveX, moveY);
	float newX, newY;
	m_sprite->GetPosition(newX, newY);
	if (newX + CGameLevel::GetInstance().GetTotalShift() >= levelLeftBuffer && newX + CGameLevel::GetInstance().GetTotalShift() <= levelRightBuffer) {
		float xChange = newX - oldX;
		newX = levelLeftBuffer;
		m_sprite->SetPosition(newX, newY);
		CGameLevel::GetInstance().ShiftLevelHorizontally(xChange);
	}

}

CSimpleSprite* CPlayerController::GetSprite()
{
	auto sp = App::CreateSprite(".\\MyData\\BaseCharacter.bmp", 2, 2);
	sp->SetColor(0.0F, 1.0F, 0.0F);
	return sp;
}
