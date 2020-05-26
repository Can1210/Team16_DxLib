#pragma once
#include"../CharaManager/BaseObject.h"
#include"../CharaManager/CharactorManager.h"


class CirecleMoveEnemy :public BaseObject
{
public:
	CirecleMoveEnemy(Vector2 pos, CharactorManager *c);
	~CirecleMoveEnemy();
	// BaseObject を介して継承されました
	virtual void initialize() override;

	virtual void update(float deltaTime) override;

	virtual void draw(Renderer * renderer, Renderer3D* renderer3D) override;

	virtual void hit(BaseObject & other) override;

	void Shot(Vector2 pos);

	//動き
	void move(float deltaTime);
	////プレイヤーの位置を調べる
	Vector2 checkPlayerPos(Vector2 vec);

private:
	Timer *m_pTimer;
	CharactorManager* charaManager;
	Vector2 mPlayerPos;
	//円運動
	float x;
	float y;
	float radius;
	float rotateSpeed;
	float moveTime;
};
