#pragma once
#ifndef _TESTSCENE3D_H_
#define _TESTSCENE3D_H_

#include "BaseScene.h"
#include"../Actor/CharaManager/EnemySpawn.h"
#include"../Actor/CharaManager/CharactorManager.h"
#include "../Actor/CharaManager/MapSpawn.h"

class TestScene3D : public BaseScene
{
public:
	TestScene3D();
	~TestScene3D();

	virtual void initialize() override;
	virtual void update(float deltaTime) override;
	virtual void draw(Renderer* renderer, Renderer3D* renderer3D) override;
	virtual void shutdown() override;
	virtual bool isEnd() override;
	virtual std::string nextScene() override;
private:
	CharactorManager* charaManager;
	MapSpawn* mapSpawn;
	float backPos;

	bool mGameOver;
	bool mGameClear;

};

#endif // !_TESTSCENE3D_H_
