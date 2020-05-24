#pragma once
#include"../CharaManager/BaseObject.h"
#include"../CharaManager/CharactorManager.h"


class Enemy :public BaseObject
{
public:
	Enemy(Vector2 pos, CharactorManager *c);
	~Enemy();

	// BaseObject ����Čp�������܂���
	virtual void initialize() override;

	virtual void update(float deltaTime) override;

	virtual void draw(Renderer * renderer, Renderer3D* renderer3D) override;

	virtual void hit(BaseObject & other) override;

	void Shot(Vector2 pos);
private:
	CharactorManager* charaManager;
	Timer *mTimer;
};
