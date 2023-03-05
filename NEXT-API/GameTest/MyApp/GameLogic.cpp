//---------------------------------------------------------------------------------
// GameLogic.cpp
//---------------------------------------------------------------------------------
#include "stdafx.h"
#include "GameLogic.h"
#include "GameLevel.h"
#include "LevelObject.h"
#include "CharacterController.h"

CExplodeLogic::CExplodeLogic(std::unique_ptr<CDetonateLogic> detonateLogic, std::shared_ptr<CLevelObject> dropOnDestruction, int durability, int score) : m_detonateLogic(std::move(detonateLogic)),
  m_dropOnDestruction(std::move(dropOnDestruction)), m_durability(durability), m_score(score) {}

CExplodeLogic::~CExplodeLogic() {}

bool CExplodeLogic::Explode(CLevelObject& object)
{
    if (--m_durability == 0) {
        CGameLevel::GetInstance().AddScore(m_score);
        if (m_detonateLogic != nullptr) {
            m_detonateLogic->Detonate(object);
        }
        auto dropOnDestruction = std::move(m_dropOnDestruction);
        int row, col;
        object.GetPosition(row, col);
        object.Destroy();
        if (dropOnDestruction != nullptr) {
            std::shared_ptr<CCharacterController> spawnedCharacter = std::dynamic_pointer_cast<CCharacterController>(dropOnDestruction);
            if (spawnedCharacter != nullptr) {
                CGameLevel::GetInstance().AddCharacter(spawnedCharacter, row, col);
            }
            else {
                dropOnDestruction->Init(row, col);
                std::shared_ptr<CLevelObject> object = std::move(dropOnDestruction);
                CGameLevel::GetInstance().GetLevelCell(row, col)->SetContainedObject(std::move(object));
            }
        }
        return true;
    }
    return false;
}

bool CExplodeLogic::GetDetonated()
{
    if (m_detonateLogic != nullptr) {
        return m_detonateLogic->GetDetonated();
    }
    return false;
}

bool CAIInputLogic::NeedNewInput(CCharacterController& character)
{
    float oldX, oldY;
    character.GetPosition(oldX, oldY);
    int oldRow, oldCol;
    character.GetPosition(oldRow, oldCol);
    character.Move(static_cast<float>(m_dirX), static_cast<float>(m_dirY));
    float newX, newY;
    character.GetPosition(newX, newY);
    int newRow, newCol;
    character.GetPosition(newRow, newCol);
    bool notMoving = oldX == newX && oldY == newY;
    bool freshCell = !notMoving && !CGameLevel::GetInstance().IsCenterOfCell(oldX, oldY) && CGameLevel::GetInstance().IsCenterOfCell(newX, newY);
    return notMoving || freshCell;
}

void COnPlayerPickupLogic::OnPlayerPickup(CLevelObject& object)
{
    object.Destroy();
}
