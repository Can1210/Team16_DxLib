#pragma once
#ifndef _STAGE02_H_
#define _STAGE02_H_

#include "BaseScene.h"
#include"../Actor/CharaManager/EnemySpawn.h"
#include"../Actor/CharaManager/CharactorManager.h"
#include "../Actor/CharaManager/MapSpawn.h"
#include"../Device/Camera.h"


//ステージ2
class Stage02 : public BaseScene
{
public:
	Stage02(Input* input);
	~Stage02();

	virtual void initialize() override;
	virtual void update(float deltaTime) override;
	virtual void draw(Renderer* renderer, Renderer3D* renderer3D) override;
	virtual void shutdown() override;
	virtual bool isEnd() override;
	virtual std::string nextScene() override;
private:
	CharactorManager* m_pCharaManager;
	MapSpawn* m_pMapSpawn;
	Camera* m_pCamera;
	float mBackPos;
	bool mGameOver;
	bool mGameClear;
};


#endif // !_STAGE02_H_