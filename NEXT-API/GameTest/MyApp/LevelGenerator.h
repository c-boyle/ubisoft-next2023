//---------------------------------------------------------------------------------
// LevelGenerator.h
//---------------------------------------------------------------------------------
#ifndef _LEVELGENERATOR_H
#define _LEVELGENERATOR_H

#include "..\stdafx.h"
#include "LevelObject.h"

enum {
	GENERATE_ENEMY,
	GENERATE_ITEM,
	GENERATE_GOLD,
	GENERATE_BOMBTYPE,
	GENERATE_EXPLOSIVE,
	GENERATE_BRICK,
	GENERATE_DOOR,
	GENERATE_EMPTY,
	END
};

class CLevelGenerator {
public:
	void Init();
	CLevelObject* GenerateRandomObject();

private:
	CDetonateLogic* GetRandomDetonateLogic(bool allowAttackDetonates = true);
	CExplodeLogic* GetRandomExplodeLogic();
	COnPlayerPickupLogic* GetRandomPlayerPickupLogic(int forcePick = -1);
	CAIInputLogic* GetRandomAIInputLogic();
	CLevelObject* GenerateRandomEnemy();
	CLevelObject* GenerateGoldBlock();
	CLevelObject* GenerateRandomItem();
	CLevelObject* GenerateRandomBombTypeItem();
	CLevelObject* GenerateExplosiveBlock();
	CLevelObject* GenerateBrickBlock();
	CLevelObject* GenerateDoorBlock();
	int m_numEnemiesToGenerate;
	int m_numItemsToGenerate;
	int m_numGoldBlocksToGenerate;
	int m_numBombTypesToGenerate;
	int m_numExplosiveBlocksToGenerate;
	int m_numDoorsToGenerate;
	int m_numBricksToGenerate;
	int m_numEmptyToGenerate;

};

#endif