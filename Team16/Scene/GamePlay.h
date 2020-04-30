#pragma once
#ifndef _GAMEPLAY_H_
#define _GAMEPLAY_H_
#include "BaseScene.h"
#include"../Actor/Player/Player.h"
#include "../Actor/Enemies/Enemy.h"
#include"../Actor/CharaManager/EnemySpawn.h"
#include"../Actor/CharaManager/CharactorManager.h"


class GamePlay : public BaseScene
{
public:
	GamePlay();
	~GamePlay();

	virtual void initialize() override;
	virtual void update(float deltaTime) override;
	virtual void draw(Renderer* renderer) override;
	virtual void shutdown() override;
	virtual bool isEnd() override;
	virtual std::string nextScene() override;
private:
	CharactorManager *charaManager;
	EnemySpawn *enemySpawn;
};


#endif // !_GAMEPLAY_H

