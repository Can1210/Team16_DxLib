#pragma once
#ifndef _ENDING_H_
#define _ENDING_H_
#include "BaseScene.h"

class Ending : public BaseScene
{
public:
	Ending();
	~Ending();
	virtual void initialize() override;
	virtual void update(float deltaTime) override;
	virtual void draw(Renderer* renderer) override;
	virtual void shutdown() override;
	virtual bool isEnd() override;
	virtual std::string nextScene() override;
private:

};

#endif // !_ENDING_H