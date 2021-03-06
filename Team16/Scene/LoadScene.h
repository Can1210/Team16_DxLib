#pragma once
#ifndef _LOADSCENE_H_
#define _LOADSCENE_H_
#include "BaseScene.h"

//読み込みするクラス
class LoadScene : public BaseScene
{
public:
	LoadScene();
	~LoadScene();
	virtual void initialize() override;
	virtual void update(float deltaTime) override;
	virtual void draw(Renderer* renderer, Renderer3D* renderer3D) override;
	virtual void shutdown() override;
	virtual bool isEnd() override;
	virtual std::string nextScene() override;
};

#endif // !_LOADSCENE_H_

