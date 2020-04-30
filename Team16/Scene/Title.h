#pragma once
#ifndef _TITLE_H_
#define _TITLE_H_
#include "BaseScene.h"
#include "../Math/Vector2.h"

class Title : public BaseScene
{
public:
	Title();
	~Title();
	virtual void initialize() override;
	virtual void update(float deltaTime) override;
	virtual void draw(Renderer* renderer) override;
	virtual void shutdown() override;
	virtual bool isEnd() override;
	virtual std::string nextScene() override;
private:
};

#endif // !_TITLE_H
