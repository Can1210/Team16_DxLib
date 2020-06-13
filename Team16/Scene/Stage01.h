#pragma once
#ifndef _STAGE01_H_
#define _STAGE01_H_

#include "BaseScene.h"
#include"../Actor/CharaManager/EnemySpawn.h"
#include"../Actor/CharaManager/CharactorManager.h"
#include "../Actor/CharaManager/MapSpawn.h"

//�X�e�[�W1
class Stage01 : public BaseScene
{
public:
	Stage01();
	~Stage01();

	virtual void initialize() override;
	virtual void update(float deltaTime) override;
	virtual void draw(Renderer* renderer, Renderer3D* renderer3D) override;
	virtual void shutdown() override;
	virtual bool isEnd() override;
	virtual std::string nextScene() override;

	void choiceScene();

private:
	void fadeFont();

private:
	CharactorManager* m_pCharaManager;
	MapSpawn* m_pMapSpawn;
	float mBackPos;
	bool mGameOver;
	bool mGameClear;

	int sceneNumArray[3];
	int sceneNum;
	std::string nextSceneName;

	FadeType fadetype;
	float fadeCount;
	const float fadeEndTime = 2.0f;
	bool mStageStart;
	int mFontAlpha;


};


#endif // !_STAGE01_H_

