#pragma once
#ifndef _LOADSCENE_H_
#define _LOADSCENE_H_
#include "BaseScene.h"

//ì«Ç›çûÇ›Ç∑ÇÈÉNÉâÉX
class LoadScene : public BaseScene
{
public:
	LoadScene();
	~LoadScene();
	virtual void initialize() override;
	virtual void update(float deltaTime) override;
	virtual void draw(Renderer* renderer) override;
	virtual void shutdown() override;
	virtual bool isEnd() override;
	virtual std::string nextScene() override;
};

#endif // !_LOADSCENE_H_

