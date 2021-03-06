#pragma once
#include"../CharaManager/BaseObject.h"
#include"../CharaManager/CharactorManager.h"


class Enemy :public BaseObject
{
public:
	Enemy(Vector2 pos, CharactorManager *c);
	~Enemy();

	virtual void initialize() override;

	virtual void update(float deltaTime) override;

	virtual void draw(Renderer * renderer, Renderer3D* renderer3D) override;

	virtual void hit(BaseObject & other) override;

	void Shot(Vector2 pos);
	//プレイヤーの位置を調べる
	Vector2 checkPlayerPos(Vector2 vec);
private:
	CharactorManager* charaManager;
	Timer *mTimer;
	Timer *mTimerDamege;
	int mDamageHit;
	bool isBom;
};
