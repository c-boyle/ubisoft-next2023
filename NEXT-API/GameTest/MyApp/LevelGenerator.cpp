//---------------------------------------------------------------------------------
// LevelGenerator.cpp
//---------------------------------------------------------------------------------
#include "stdafx.h"
#include "LevelGenerator.h"
#include <random>
#include "../App/app.h"
#include "GameLevel.h"

// Cite: https://stackoverflow.com/questions/1761626/weighted-random-numbers
int GetTypeToGenerate(int weights[], int numWeights) {
	int sum_of_weight = 0;
	for (int i = 0; i < numWeights; i++) {
		sum_of_weight += weights[i];
	}
	int rnd = sum_of_weight != 0 ? rand() % sum_of_weight : 0;
	for (int i = 0; i < numWeights; i++) {
		if (rnd < weights[i])
			return i;
		rnd -= weights[i];
	}
}

CLevelObject* GetDoorItem() {
	auto sp = App::CreateSprite(".\\MyData\\DoorItem.bmp", 1, 1);
	auto increaseLevel = new CIncreaseLevelOnPlayerPickupLogic();
	return new CLevelObject(false, std::unique_ptr<CSimpleSprite>(sp), nullptr, std::unique_ptr<COnPlayerPickupLogic>(increaseLevel));
}

void CLevelGenerator::Init()
{
	float percentComplete = static_cast<float>(CGameLevel::GetInstance().m_currentDifficulty) / static_cast<float>(maxLevels);
	int availableCellCountCopy = availableCellCount;
	m_numEnemiesToGenerate = availableCellCount * std::fmin(percentComplete / 2.0F, 0.8F);
	m_numItemsToGenerate = 1;
	m_numGoldBlocksToGenerate = 1;
	m_numBombTypesToGenerate = 1;
	m_numExplosiveBlocksToGenerate = 1;
	m_numDoorsToGenerate = 1;
	if (percentComplete >= 0.25F) {
		++m_numExplosiveBlocksToGenerate;
	}
	if (percentComplete >= 0.5F) {
		++m_numItemsToGenerate;
		++m_numGoldBlocksToGenerate;
		m_numExplosiveBlocksToGenerate *= 2;
	}
	if (percentComplete >= 0.75F) {
		++m_numItemsToGenerate;
	}
	availableCellCountCopy -= m_numEnemiesToGenerate;
	availableCellCountCopy -= m_numItemsToGenerate;
	availableCellCountCopy -= m_numBombTypesToGenerate;
	availableCellCountCopy -= m_numGoldBlocksToGenerate;
	availableCellCountCopy -= m_numDoorsToGenerate;
	m_numBricksToGenerate = availableCellCountCopy * (1.0F - percentComplete) / 2.0F;
	m_numEmptyToGenerate = availableCellCountCopy - m_numBricksToGenerate;
}

CLevelObject* CLevelGenerator::GenerateRandomObject()
{
	int weights[END] = {
		m_numEnemiesToGenerate, m_numItemsToGenerate, m_numGoldBlocksToGenerate, m_numBombTypesToGenerate, m_numExplosiveBlocksToGenerate,
		m_numBricksToGenerate, m_numDoorsToGenerate, m_numEmptyToGenerate
	};
	int typeToGenerate = GetTypeToGenerate(weights, END);
	switch (typeToGenerate) {
	case GENERATE_ENEMY:
		--m_numEnemiesToGenerate;
		return GenerateRandomEnemy();
	case GENERATE_ITEM:
		--m_numItemsToGenerate;
		return GenerateRandomItem();
	case GENERATE_GOLD:
		--m_numGoldBlocksToGenerate;
		return GenerateGoldBlock();
	case GENERATE_BOMBTYPE:
		--m_numBombTypesToGenerate;
		return GenerateRandomBombTypeItem();
	case GENERATE_EXPLOSIVE:
		--m_numExplosiveBlocksToGenerate;
		return GenerateExplosiveBlock();
	case GENERATE_BRICK:
		--m_numBricksToGenerate;
		return GenerateBrickBlock();
	case GENERATE_DOOR:
		--m_numDoorsToGenerate;
		return GenerateDoorBlock();
	case GENERATE_EMPTY:
		--m_numEmptyToGenerate;
		return nullptr;
	}
	return nullptr;
}

CDetonateLogic* CLevelGenerator::GetRandomDetonateLogic(bool allowAttackDetonates)
{
	int random = rand();
	int power = random % 3;
	if (!allowAttackDetonates || rand() % 2 == 1) {
		return new CAxisDetonateLogic(power);
	}
	else {
		return new CAttackDetonateLogic(power);
	}
}

CExplodeLogic* CLevelGenerator::GetRandomExplodeLogic()
{
	int random = rand();
	return new CExplodeLogic(std::unique_ptr<CDetonateLogic>(GetRandomDetonateLogic()), std::shared_ptr<CLevelObject>(GenerateRandomObject()), random % 2 + 1,  random % 300 + 1);
}

COnPlayerPickupLogic* CLevelGenerator::GetRandomPlayerPickupLogic(int forcePick)
{
	int random = rand();
	int pick = forcePick == -1 ? random % 3 : forcePick;
	if (pick == 0) {
		return new CIncreaseLevelOnPlayerPickupLogic(random % 2 + 1);
	}
	else if (pick == 1) {
		return new CAddLivesOnPlayerPickupLogic(random % 3 + 1);
	}
	else {
		float randMultiplier = 0.8F + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1.2F - 0.8F)));
		return new CEditBombDispenserPickupLogic(random % 2 == 1, static_cast<BombType>(random % BombType::NONE), random % 2, randMultiplier);
	}
}

CAIInputLogic* CLevelGenerator::GetRandomAIInputLogic()
{
	int random = rand();
	if (random % 2 == 1) {
		return new CHugWallAIInput();
	}
	else {
		return new CAStarAIInput(CGameLevel::GetInstance().m_player, rand() % 2 == 1);
	}
}

CLevelObject* CLevelGenerator::GenerateRandomEnemy()
{
	auto sp = App::CreateSprite(".\\MyData\\BaseCharacter.bmp", 2, 2);
	sp->SetColor(1.0F, 0.0F, 0.0F);
	auto explodeLogic = rand() % 5 == 0 ? GetRandomExplodeLogic() : new CExplodeLogic();
	auto inputLogic = GetRandomAIInputLogic();
	bool hurtsPlayer = rand() % 5 < 4;
	auto onPlayerPickupLogic = !hurtsPlayer ? GetRandomPlayerPickupLogic() : nullptr;
	if (explodeLogic != nullptr) {
		sp->SetColor(1.0F, 0.64F, 0.0F);
	}
	else if (!hurtsPlayer) {
		if (rand() % 3 == 1) {
			sp->SetColor(1.0F, 0.0F, 1.0F);
		}
	}
	return new CEnemyController(false, std::unique_ptr<CSimpleSprite>(sp), std::unique_ptr<CExplodeLogic>(explodeLogic), std::unique_ptr<CAIInputLogic>(inputLogic), std::unique_ptr<COnPlayerPickupLogic>(onPlayerPickupLogic), hurtsPlayer);
}

CLevelObject* CLevelGenerator::GenerateGoldBlock()
{
	auto sp = App::CreateSprite(".\\MyData\\BrickBlock.bmp", 1, 1);
	sp->SetColor(1.0F, 1.0F, 0.0F);
	auto explodeLogic = new CExplodeLogic(nullptr, nullptr, 3, 200);
	return new CLevelObject(true, std::unique_ptr<CSimpleSprite>(sp), std::unique_ptr<CExplodeLogic>(explodeLogic), nullptr);
}

CLevelObject* CLevelGenerator::GenerateRandomItem()
{
	auto sp = App::CreateSprite(".\\MyData\\Item.bmp", 1, 1);
	return new CLevelObject(false, std::unique_ptr<CSimpleSprite>(sp), nullptr, std::unique_ptr<COnPlayerPickupLogic>(GetRandomPlayerPickupLogic(1)));
}

CLevelObject* CLevelGenerator::GenerateRandomBombTypeItem()
{
	auto sp = App::CreateSprite(".\\MyData\\Item.bmp", 1, 1);
	sp->SetColor(1.0F, 0.64F, 0.0F);
	return new CLevelObject(false, std::unique_ptr<CSimpleSprite>(sp), nullptr, std::unique_ptr<COnPlayerPickupLogic>(GetRandomPlayerPickupLogic(2)));
}

CLevelObject* CLevelGenerator::GenerateExplosiveBlock()
{
	auto sp = App::CreateSprite(".\\MyData\\BrickBlock.bmp", 1, 1);
	sp->SetColor(1.0F, 0.0F, 0.0F);
	return new CLevelObject(true, std::unique_ptr<CSimpleSprite>(sp), std::unique_ptr<CExplodeLogic>(GetRandomExplodeLogic()), nullptr);
}

CLevelObject* CLevelGenerator::GenerateBrickBlock()
{
	auto sp = App::CreateSprite(".\\MyData\\BrickBlock.bmp", 1, 1);
	auto explodeLogic = new CExplodeLogic();
	return new CLevelObject(true, std::unique_ptr<CSimpleSprite>(sp), std::unique_ptr<CExplodeLogic>(explodeLogic), nullptr);
}

CLevelObject* CLevelGenerator::GenerateDoorBlock()
{
	auto sp = App::CreateSprite(".\\MyData\\BrickBlock.bmp", 1, 1);
	auto explodeLogic = new CExplodeLogic(nullptr, std::shared_ptr<CLevelObject>(GetDoorItem()), 1, 100);
	return new CLevelObject(true, std::unique_ptr<CSimpleSprite>(sp), std::unique_ptr<CExplodeLogic>(explodeLogic), nullptr);
}
