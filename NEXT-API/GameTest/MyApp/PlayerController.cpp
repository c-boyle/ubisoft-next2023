//---------------------------------------------------------------------------------
// PlayerController.cpp
//---------------------------------------------------------------------------------
#include "stdafx.h"
#include "PlayerController.h"
#include "../App/app.h"
#include "GameLevel.h"
#include "EnemyController.h"

constexpr int levelLeftBuffer = APP_VIRTUAL_WIDTH / 2;
constexpr int levelRightBuffer = levelWidth - levelLeftBuffer;

void CPlayerController::Render()
{
	m_basicDispenser->Render();
	m_specialDispenser->Render();
	if (!m_dead) {
		CLevelObject::Render();
	}
}

void CPlayerController::SetBasicDispenser(BombType bombType)
{
	if (m_basicDispenser == nullptr) {
		m_basicDispenser = std::unique_ptr<CBombDispenser>(new CBombDispenser(bombType));
	}
	else {
		m_basicDispenser->SetBomb(bombType);
	}
}

void CPlayerController::SetSpecialDispenser(BombType bombType)
{
	if (m_specialDispenser == nullptr) {
		m_specialDispenser = std::unique_ptr<CBombDispenser>(new CBombDispenser(bombType));
	}
	else {
		m_specialDispenser->SetBomb(bombType);
	}
}

void CPlayerController::DecideInput()
{
	if (m_dead) {
		if (App::GetController().CheckButton(XINPUT_GAMEPAD_A, true))
		{
			CGameLevel::GetInstance().Respawn();
			m_dead = false;
		}
		return;
	}
	Move(App::GetController().GetLeftThumbStickX(), App::GetController().GetLeftThumbStickY());

	if (App::GetController().CheckButton(XINPUT_GAMEPAD_A, true))
	{
		m_basicDispenser->Dispense(m_cellRow, m_cellCol);
	}
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_B, true))
	{
		m_specialDispenser->Dispense(m_cellRow, m_cellCol);
	}
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_X, true))
	{
		CGameLevel::GetInstance().GetLevelCell(m_cellRow, m_cellCol)->OnPlayerPickup();
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
