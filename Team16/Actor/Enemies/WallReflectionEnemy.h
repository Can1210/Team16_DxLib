#pragma once
#include"../../Device/Renderer.h"
#include"../CharaManager/BaseObject.h"
#include"../CharaManager/CharactorManager.h"


class WallReflectionEnemy :public BaseObject
{
public:
	WallReflectionEnemy(Vector2 pos, CharactorManager *c);
	~WallReflectionEnemy();
	// BaseObject を介して継承されました
	virtual void initialize() override;

	virtual void update(float deltaTime) override;

	virtual void draw(Renderer * renderer, Renderer3D* renderer3D) override;

	virtual void hit(BaseObject & other) override;

	void Shot(Vector2 pos);
	//動き
	void move(float deltaTime);

	//死亡エリア
	void deathArea();
private:
	Timer *m_pTimer;
	CharactorManager* charaManager;

	Vector2 startPos;
	bool startEnd;
	int shottime;

	//円運動
	float x;
	float y;
	float radius;
	float rotateSpeed;
	float moveTime;
};
