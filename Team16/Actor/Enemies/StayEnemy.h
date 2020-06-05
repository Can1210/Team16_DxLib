#pragma once
#include"../CharaManager/BaseObject.h"
#include"../CharaManager/CharactorManager.h"


class StayEnemy :public BaseObject
{
public:
	StayEnemy(Vector2 pos, CharactorManager *c);
	~StayEnemy();

	// BaseObject 
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
	Timer *m_inTimer;
	float ShotAngle;
	bool modeChange;

};
