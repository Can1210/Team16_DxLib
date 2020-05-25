#include "EnemySpawn.h"
#include <random>
#include "../Enemies/Enemy.h"
#include"../Enemies/CircleMoveEnemy.h"
#include"../Enemies/BomEnemy.h"
#include"../Enemies/ThreeWayEnemy.h"
#include"../Enemies/UFOEnemy.h"
#include"../Enemies/PlatoonEnemy.h"
#include"../Enemies/HomingEnemy.h"
#include"../Enemies/LaserEnemy.h"
#include"../Enemies/WallReflectionEnemy.h"
#include"../Enemies/Boss.h"
#include"../../GameBase/Score.h"

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
	spawnTime = 0;
}

void EnemySpawn::update(float deltaTime)
{
	mTimer->update(deltaTime);
}

void EnemySpawn::spawn()
{
	//5秒おきに敵が生成される
	//if (mTimer->timerSet(5))
	//{
	//	//疑似乱数に初期シードを与える
	//	std::mt19937 mt{ std::random_device{}() };
	//	//ディストリビューションを使って範囲指定（整数）
	//	std::uniform_int_distribution<int> spawnNum(1, 9);
	//	std::uniform_int_distribution<int> spawnNum2(1, 9);
	//	std::uniform_int_distribution<int> spawnNum3(1, 3);
	//	std::uniform_int_distribution<int> spawnNum4(1, 3);
	//	for (int i = 0; i < spawnNum(mt); i++)
	//	{
	//		mCharactorManager->add(new Enemy(Vector2((i + 1) * 100, (i + 1)* -100), mCharactorManager));
	//	}

	//	for (int i = 0; i < spawnNum2(mt); i++)
	//	{
	//		mCharactorManager->add(new CirecleMoveEnemy(Vector2((i + 1) * 130, (i + 1) * -200), mCharactorManager));
	//	}

	//	for (int i = 0; i < spawnNum3(mt); i++)
	//	{
	//		mCharactorManager->add(new BomEnemy(Vector2((i + 1) * 160, (i + 1) * -400), mCharactorManager));
	//	}

	//	/*for (int i = 0; i < spawnNum4(mt); i++)
	//	{
	//		mCharactorManager->add(new PlatoonEnemy(Vector2(600.0f, -10.0f), mCharactorManager, 260.0f, 270.0f, 280.0f,Vector2(0.0f,500.0f)));
	//	}*/
	//}

	//#ifの1にしてelifを0にすれば生成が切り替わる
#if 0
	switch (spawnTime)
	{
	case 60 * 3:
		mCharactorManager->add(new Enemy(Vector2(sizeX * 1, -sizeY), mCharactorManager));
		mCharactorManager->add(new Enemy(Vector2(sizeX * 2, -sizeY), mCharactorManager));
		mCharactorManager->add(new Enemy(Vector2(sizeX * 1, -sizeY * 2), mCharactorManager));
		mCharactorManager->add(new Enemy(Vector2(sizeX * 2, -sizeY * 2), mCharactorManager));

		mCharactorManager->add(new Enemy(Vector2(600 - sizeX * 2, -sizeY), mCharactorManager));
		mCharactorManager->add(new Enemy(Vector2(600 - sizeX * 3, -sizeY), mCharactorManager));
		mCharactorManager->add(new Enemy(Vector2(600 - sizeX * 2, -sizeY * 2), mCharactorManager));
		mCharactorManager->add(new Enemy(Vector2(600 - sizeX * 3, -sizeY * 2), mCharactorManager));
		break;//3

	case 60 * 7:
		mCharactorManager->add(new CirecleMoveEnemy(Vector2(sizeX * 2, -sizeY), mCharactorManager));
		break;
	case 60 * 7 + 20:
		mCharactorManager->add(new CirecleMoveEnemy(Vector2(sizeX * 2, -sizeY), mCharactorManager));
		break;
	case 60 * 7 + 40:
		mCharactorManager->add(new CirecleMoveEnemy(Vector2(sizeX * 2, -sizeY), mCharactorManager));
		break;
	case 60 * 7 + 60://8
		mCharactorManager->add(new CirecleMoveEnemy(Vector2(sizeX * 2, -sizeY), mCharactorManager));
		break;//7～

	case 60 * 11:
		mCharactorManager->add(new BomEnemy(Vector2(sizeX * 1, -sizeY), mCharactorManager));
		mCharactorManager->add(new BomEnemy(Vector2(600 - sizeX * 2, -sizeY), mCharactorManager));
		break;//11

	case 60 * 16:
		mCharactorManager->add(new UFOEnemy(Vector2(sizeX * 2, -sizeY), mCharactorManager, 260.0f, 270.0f, 280.0f, Vector2(600 / 2 + 32, 500.0f)));
		break;//16

	case 60 * 20:
		mCharactorManager->add(new PlatoonEnemy(Vector2(600.0f, -10.0f), mCharactorManager, 260.0f, 270.0f, 280.0f, Vector2(0.0f, 500.0f)));
		break;
	case 60 * 20 + 25:
		mCharactorManager->add(new PlatoonEnemy(Vector2(600.0f, -10.0f), mCharactorManager, 260.0f, 270.0f, 280.0f, Vector2(0.0f, 500.0f)));
		break;
	case 60 * 20 + 50:
		mCharactorManager->add(new PlatoonEnemy(Vector2(600.0f, -10.0f), mCharactorManager, 260.0f, 270.0f, 280.0f, Vector2(0.0f, 500.0f)));
		break;
	case 60 * 20 + 75:
		mCharactorManager->add(new PlatoonEnemy(Vector2(600.0f, -10.0f), mCharactorManager, 260.0f, 270.0f, 280.0f, Vector2(0.0f, 500.0f)));
		break;
	case 60 * 20 + 100:
		mCharactorManager->add(new PlatoonEnemy(Vector2(600.0f, -10.0f), mCharactorManager, 260.0f, 270.0f, 280.0f, Vector2(0.0f, 500.0f)));
		break;//20～

	case 60 * 25:
		mCharactorManager->add(new ThreeWayEnemy(Vector2(600.0f, -sizeY), mCharactorManager, 260.0f, 270.0f, 280.0f, Vector2(0.0f, 1000.0f)));
		break;//25
	case 60 * 25 + 20 * 1:
		mCharactorManager->add(new ThreeWayEnemy(Vector2(sizeX, -sizeY), mCharactorManager, 260.0f, 270.0f, 280.0f, Vector2(600.0f, 1000.0f)));
		break;
	case 60 * 25 + 20 * 4:
		mCharactorManager->add(new ThreeWayEnemy(Vector2(sizeX * 2, -sizeY), mCharactorManager, 260.0f, 270.0f, 280.0f, Vector2(300.0f, 1000.0f)));
		break;
	case 60 * 25 + 20 * 7:
		mCharactorManager->add(new ThreeWayEnemy(Vector2(sizeX * 8, -sizeY), mCharactorManager, 260.0f, 270.0f, 280.0f, mCharactorManager->getPlayerPosition()));
		break;

	case 60 * 30:
		mCharactorManager->add(new HomingEnemy(Vector2(0, -sizeY), mCharactorManager, 260.0f, 270.0f, 280.0f, Vector2(600, 1000)));
		break;

	case 60 * 34:
		mCharactorManager->add(new LaserEnemy(Vector2(sizeX * 8, -sizeY), mCharactorManager, 260.0f, 270.0f, 280.0f, Vector2(sizeX, 1000)));
		break;

	case 60 * 40:
		spawnTime = 0;//繰り返し
		break;

	case 60:
		mCharactorManager->add(new WallReflectionEnemy(Vector2(sizeX * 2, -sizeY), mCharactorManager));
		break;

	default:
		break;
	}

#elif 1
switch (spawnTime)
{
case 60 * 3:
	mCharactorManager->add(new Enemy(Vector2(middleX, -sizeY), mCharactorManager));//真ん中

	mCharactorManager->add(new Enemy(Vector2(middleX - sizeX * 2, -sizeY * 2), mCharactorManager));//左
	mCharactorManager->add(new Enemy(Vector2(middleX + sizeX * 2, -sizeY * 2), mCharactorManager));//右

	mCharactorManager->add(new Enemy(Vector2(middleX - sizeX * 3 - 32.0f, -sizeY * 3), mCharactorManager));//左
	mCharactorManager->add(new Enemy(Vector2(middleX + sizeX * 3 + 32.0f, -sizeY * 3), mCharactorManager));//右
	break;//3

case 60 * 7:
	mCharactorManager->add(new CirecleMoveEnemy(Vector2(sizeX * 2, -sizeY), mCharactorManager));
	break;
case 60 * 7 + 20:
	mCharactorManager->add(new CirecleMoveEnemy(Vector2(sizeX * 2, -sizeY), mCharactorManager));
	break;
case 60 * 7 + 40:
	mCharactorManager->add(new CirecleMoveEnemy(Vector2(sizeX * 2, -sizeY), mCharactorManager));
	break;
case 60 * 7 + 60://8
	mCharactorManager->add(new CirecleMoveEnemy(Vector2(sizeX * 2, -sizeY), mCharactorManager));
	break;//7～

case 60 * 11:
	mCharactorManager->add(new BomEnemy(Vector2(sizeX * 1, -sizeY), mCharactorManager));
	mCharactorManager->add(new BomEnemy(Vector2(600 - sizeX * 2, -sizeY), mCharactorManager));
	mCharactorManager->add(new HomingEnemy(Vector2(0, -sizeY), mCharactorManager, 260.0f, 270.0f, 280.0f, Vector2(600, 1000)));

	break;//11

case 60 * 16:
	mCharactorManager->add(new UFOEnemy(Vector2(sizeX * 2, -sizeY), mCharactorManager, 260.0f, 270.0f, 280.0f, Vector2(600 / 2 + 32, 500.0f)));
	break;//16

case 60 * 20:
	mCharactorManager->add(new PlatoonEnemy(Vector2(600.0f, -10.0f), mCharactorManager, 260.0f, 270.0f, 280.0f, Vector2(0.0f, 500.0f)));
	break;
case 60 * 20 + 25:
	mCharactorManager->add(new PlatoonEnemy(Vector2(600.0f, -10.0f), mCharactorManager, 260.0f, 270.0f, 280.0f, Vector2(0.0f, 500.0f)));
	break;
case 60 * 20 + 50:
	mCharactorManager->add(new PlatoonEnemy(Vector2(600.0f, -10.0f), mCharactorManager, 260.0f, 270.0f, 280.0f, Vector2(0.0f, 500.0f)));
	break;
case 60 * 20 + 75:
	mCharactorManager->add(new PlatoonEnemy(Vector2(600.0f, -10.0f), mCharactorManager, 260.0f, 270.0f, 280.0f, Vector2(0.0f, 500.0f)));
	break;
case 60 * 20 + 100:
	mCharactorManager->add(new PlatoonEnemy(Vector2(600.0f, -10.0f), mCharactorManager, 260.0f, 270.0f, 280.0f, Vector2(0.0f, 500.0f)));
	break;//20～

case 60 * 25:
	mCharactorManager->add(new ThreeWayEnemy(Vector2(600.0f, -sizeY), mCharactorManager, 260.0f, 270.0f, 280.0f, Vector2(0.0f, 1000.0f)));
	break;//25
case 60 * 25 + 20 * 1:
	mCharactorManager->add(new ThreeWayEnemy(Vector2(sizeX, -sizeY), mCharactorManager, 260.0f, 270.0f, 280.0f, Vector2(600.0f, 1000.0f)));
	break;
case 60 * 25 + 20 * 4:
	mCharactorManager->add(new ThreeWayEnemy(Vector2(sizeX * 2, -sizeY), mCharactorManager, 260.0f, 270.0f, 280.0f, Vector2(300.0f, 1000.0f)));
	break;
case 60 * 25 + 20 * 7:
	mCharactorManager->add(new ThreeWayEnemy(Vector2(sizeX * 8, -sizeY), mCharactorManager, 260.0f, 270.0f, 280.0f, mCharactorManager->getPlayerPosition()));
	break;

case 60 * 30:
	mCharactorManager->add(new HomingEnemy(Vector2(0, -sizeY), mCharactorManager, 260.0f, 270.0f, 280.0f, Vector2(600, 1000)));
	break;

case 60 * 34:
	mCharactorManager->add(new LaserEnemy(Vector2(sizeX * 8, -sizeY), mCharactorManager, 260.0f, 270.0f, 280.0f, Vector2(sizeX, 1000)));
	mCharactorManager->add(new HomingEnemy(Vector2(0, -sizeY), mCharactorManager, 260.0f, 270.0f, 280.0f, Vector2(600, 1000)));
	break;

case 60 * 37:
	mCharactorManager->add(new WallReflectionEnemy(Vector2(sizeX * 8, -sizeY), mCharactorManager));
	break;

case 60 * 40:
	spawnTime = 0;//繰り返し
	break;

case 60:
	mCharactorManager->add(new HomingEnemy(Vector2(0, -sizeY), mCharactorManager, 260.0f, 270.0f, 280.0f, Vector2(600, 1000)));
	break;

default:
	break;
}
#endif // 0
	spawnTime++;
}
