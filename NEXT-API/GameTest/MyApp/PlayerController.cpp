//---------------------------------------------------------------------------------
// PlayerController.cpp
//---------------------------------------------------------------------------------
#include "stdafx.h"
#include "PlayerController.h"
#include "../App/app.h"
#include "Bombs.h"

CPlayerController::CPlayerController()
{
	m_basicDispenser = std::unique_ptr<CBombDispenser>(new CBombDispenser(std::unique_ptr<CBomb>(new CAxisBomb(10000.0F, 1)), 2));
	m_specialDispenser = std::unique_ptr<CBombDispenser>(new CBombDispenser(std::unique_ptr<CBomb>(new CAxisBomb(10000.0F, 2)), 1));
}

void CPlayerController::Render()
{
	m_basicDispenser->Render();
	m_specialDispenser->Render();
	CLevelObject::Render();
}

void CPlayerController::HandleInput()
{
	Move(App::GetController().GetLeftThumbStickX(), App::GetController().GetLeftThumbStickY());

	if (App::GetController().CheckButton(XINPUT_GAMEPAD_A, false))
	{
		float x, y;
		m_sprite->GetPosition(x, y);
		m_basicDispenser->Dispense(x, y);
	}
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_B, false))
	{
		float x, y;
		m_sprite->GetPosition(x, y);
		m_specialDispenser->Dispense(x, y);
	}
}

void CPlayerController::Update(float deltaTime)
{
	CCharacterController::Update(deltaTime);
	m_basicDispenser->Update(deltaTime);
	m_specialDispenser->Update(deltaTime);
}

CSimpleSprite* CPlayerController::GetSprite()
{
	return App::CreateSprite(".\\MyData\\Player.bmp", 2, 2);
}
