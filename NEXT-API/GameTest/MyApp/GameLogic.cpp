//---------------------------------------------------------------------------------
// GameLogic.cpp
//---------------------------------------------------------------------------------
#include "stdafx.h"
#include "GameLogic.h"
#include "GameLevel.h"
#include "LevelObject.h"

CExplodeLogic::CExplodeLogic(std::unique_ptr<CDetonateLogic> detonateLogic, std::shared_ptr<CLevelObject> dropOnDestruction, int durability) : m_detonateLogic(std::move(detonateLogic)),
  m_dropOnDestruction(std::move(dropOnDestruction)), m_durability(durability) {}

CExplodeLogic::~CExplodeLogic() {}

bool CExplodeLogic::Explode(CLevelObject& object)
{
    if (--m_durability == 0) {
        if (m_detonateLogic != nullptr) {
            m_detonateLogic->Detonate(object);
        }
        int row, col;
        object.GetPosition(row, col);
        auto dropOnDestruction = m_dropOnDestruction;
        object.Destroy();
        if (dropOnDestruction != nullptr) {
            dropOnDestruction->Init(row, row);
            std::shared_ptr<CLevelObject> item = std::move(m_dropOnDestruction);
            CGameLevel::GetInstance().GetLevelCell(row, col)->SetContainedObject(std::move(item));
        }
        return true;
    }
    return false;
}
