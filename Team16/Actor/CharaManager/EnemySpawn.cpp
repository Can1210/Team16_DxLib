#include "EnemySpawn.h"
#include <random>
#include "../Enemies/Enemy.h"
#include"../Enemies/CircleMoveEnemy.h"
#include"../Enemies/BomEnemy.h"
#include"../Enemies/ThreeWayEnemy.h"
#include"../Enemies/UFOEnemy.h"

EnemySpawn::EnemySpawn(CharactorManager& charactorManager) :
	mCharactorManager(&charactorManager),
	mTimer(new Timer())
{
}


EnemySpawn::~EnemySpawn()
{
	delete mTimer;
}

void EnemySpawn::initialize()
{
	mTimer->initialize();  //タイマーを初期化
}

void EnemySpawn::update(float deltaTime)
{
	mTimer->update(deltaTime);
}

void EnemySpawn::spawn()
{
	//5秒おきに敵が生成される
	if (mTimer->timerSet(5))
	{
		//疑似乱数に初期シードを与える
		std::mt19937 mt{ std::random_device{}() };
		//ディストリビューションを使って範囲指定（整数）
		std::uniform_int_distribution<int> spawnNum(1, 9);
		std::uniform_int_distribution<int> spawnNum2(1, 9);
		std::uniform_int_distribution<int> spawnNum3(1, 3);
		std::uniform_int_distribution<int> spawnNum4(1, 3);
		for (int i = 0; i < spawnNum(mt); i++)
		{
			mCharactorManager->add(new Enemy(Vector2((i + 1) * 100, (i + 1)* -100), mCharactorManager));
		}

		for (int i = 0; i < spawnNum2(mt); i++)
		{
			mCharactorManager->add(new CirecleMoveEnemy(Vector2((i + 1) * 130, (i + 1) * -200), mCharactorManager));
		}

		for (int i = 0; i < spawnNum3(mt); i++)
		{
			mCharactorManager->add(new BomEnemy(Vector2((i + 1) * 160, (i + 1) * -400), mCharactorManager));
		}

		for (int i = 0; i < spawnNum4(mt); i++)
		{
			mCharactorManager->add(new UFOEnemy(Vector2((i + 1) * 190, (i + 1) * -300), mCharactorManager, 260.0f, 270.0f, 280.0f,Vector2(0.0f,500.0f)));
		}
	}
}
