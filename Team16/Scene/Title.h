#pragma once
#ifndef _TITLE_H_
#define _TITLE_H_

#include "BaseScene.h"
#include "../Actor/CharaManager/CharactorManager.h"
#include "../Device/Camera.h"


class Title : public BaseScene
{
public:
	Title(Input* input);
	~Title();
	virtual void initialize() override;
	virtual void update(float deltaTime) override;
	virtual void draw(Renderer* renderer, Renderer3D* renderer3D) override;
	virtual void shutdown() override;
	virtual bool isEnd() override;
	virtual std::string nextScene() override;

	static void choiceScene(int num);
private:
	//ステージセレクトを行う
	void stageSelect(float deltaTime);

public:
	static bool mChangeScne;
	static int mStageNum;

private:
	std::string mSelectName;
	bool mIsStageSelect;     //ステージセレクト条件
	
	CharactorManager* m_pCharaManager;
	Camera* m_pCamera;	
};

#endif // !_TITLE_H
