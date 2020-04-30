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
};

#endif // !_ENEMYSPAWN_H_
