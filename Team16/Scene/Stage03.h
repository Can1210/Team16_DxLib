#pragma once
#ifndef _STAGE03_H_
#define _STAGE03_H_

#include "BaseScene.h"
#include"../Actor/CharaManager/EnemySpawn.h"
#include"../Actor/CharaManager/CharactorManager.h"
#include "../Actor/CharaManager/MapSpawn.h"



//ステージ3
class Stage03 : public BaseScene
{
public:
	Stage03();
	~Stage03();

	virtual void initialize() override;
	virtual void update(float deltaTime) override;
	virtual void draw(Renderer* renderer, Renderer3D* renderer3D) override;
	virtual void shutdown() override;
	virtual bool isEnd() override;
	virtual std::string nextScene() override;
	void choiceScene();
private:
	CharactorManager* m_pCharaManager;
	MapSpawn* m_pMapSpawn;
	float mBackPos;
	bool mGameOver;
	bool mGameClear;

	int sceneNumArray[3];
	int sceneNum;
	std::string nextSceneName;
};


#endif // !_STAGE03_H_
