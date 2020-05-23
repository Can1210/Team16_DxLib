#pragma once
#ifndef _ENEMYSPAWN_H_
#define _ENEMYSPAWN_H_
#include "CharactorManager.h"
#include "../../Utility/Timer.h"

//敵生成クラス
class EnemySpawn
{
public:
	EnemySpawn(CharactorManager& charactorManager);
	~EnemySpawn();
	//初期化
	void initialize();
	//更新
	void update(float deltaTime);
	//生成
	void spawn();
	
private:
	CharactorManager* mCharactorManager;   //キャラクターマネジャー
	Timer* mTimer;                         //タイマー
	int spawnTime;

	float sizeX = 64.0f;
	float sizeY = 64.0f;

	float middleX = 600.0f / 2.0f - 32.0f;
};

#endif // !_ENEMYSPAWN_H_
