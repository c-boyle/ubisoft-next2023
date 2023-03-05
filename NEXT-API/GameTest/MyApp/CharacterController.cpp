//------------------------------------------------------------------------
// CharacterController.cpp
//------------------------------------------------------------------------
#include "stdafx.h"
#include "CharacterController.h"
#include "GameLevel.h"

constexpr float speed = 1.3F;

void CCharacterController::Update(float deltaTime)
{
	// sprite->Update(deltaTime);
	HandleInput();
}

void CCharacterController::Move(float moveX, float moveY)
{
	if (moveX != 0.0F || moveY != 0.0F) {
		moveX *= speed;
		moveY *= speed;
		AnimateMove(moveX, moveY);
		float x, y;
		m_sprite->GetPosition(x, y);
		float targetX = x + moveX;
		float targetY = y + moveY;
		int decimalX = abs(static_cast<int>(((targetX + CGameLevel::GetInstance().GetTotalShift()) / cellSize) * 10)) % 10;
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
		bool positionChanged = newX != x || newY != y;
		if (positionChanged) {
			m_sprite->SetPosition(newX, newY);
			auto oldCell = CGameLevel::GetInstance().GetLevelCell(m_cellRow, m_cellCol);
			CGameLevel::GetInstance().VirtualCoordsToCell(x, y, m_cellRow, m_cellCol);
			auto newCell = CGameLevel::GetInstance().GetLevelCell(m_cellRow, m_cellCol);
			if (oldCell != newCell) {
				newCell->SetContainedCharacter(std::enable_shared_from_this<CCharacterController>::shared_from_this());
				oldCell->Clear(false);
			}
		}
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

void CCharacterController::Destroy()
{
	CLevelObject::Destroy();
	CGameLevel::GetInstance().RemoveCharacter(std::enable_shared_from_this<CCharacterController>::shared_from_this());
}

