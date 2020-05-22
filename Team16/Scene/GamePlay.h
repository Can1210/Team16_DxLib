#pragma once
#ifndef _GAMEPLAY_H_
#define _GAMEPLAY_H_
#include "BaseScene.h"
#include"../Actor/Player/Player.h"
#include "../Actor/Enemies/Enemy.h"
#include"../Actor/CharaManager/EnemySpawn.h"
#include"../Actor/CharaManager/CharactorManager.h"
#include"../Actor/Enemies/Boss.h"



class GamePlay : public BaseScene
{
public:
	GamePlay(Input* input);
	~GamePlay();
	void  boss();
	virtual void initialize() override;
	virtual void update(float deltaTime) override;
	virtual void draw(Renderer* renderer, Renderer3D* renderer3D) override;
	virtual void shutdown() override;
	virtual bool isEnd() override;
	virtual std::string nextScene() override;
	static bool BossEnd;//å„ïœçX
	static bool PlayerEnd;
private:
	CharactorManager *charaManager;
	EnemySpawn *enemySpawn;
	int bossFlag;
	float backPos;
	
};


#endif // !_GAMEPLAY_H

