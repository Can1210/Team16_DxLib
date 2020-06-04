#pragma once
#ifndef _TITLE_H_
#define _TITLE_H_

#include "BaseScene.h"


class Title : public BaseScene
{
public:
	Title();
	~Title();
	virtual void initialize() override;
	virtual void update(float deltaTime) override;
	virtual void draw(Renderer* renderer, Renderer3D* renderer3D) override;
	virtual void shutdown() override;
	virtual bool isEnd() override;
	virtual std::string nextScene() override;

private:
	std::string mSelectName;
	bool mIsStageSelect;     //ステージセレクト条件

	int alpha;
	bool isReturn;

	bool isAnim;
	int animAlpha;

};

#endif // !_TITLE_H
