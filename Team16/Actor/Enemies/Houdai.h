#pragma once
#include"../CharaManager/BaseObject.h"
#include"../CharaManager/CharactorManager.h"


class Houdai :public BaseObject
{
public:
	Houdai(Vector2 pos, CharactorManager *c);
	~Houdai();

	// BaseObject 
	virtual void initialize() override;

	virtual void update(float deltaTime) override;

	virtual void draw(Renderer * renderer, Renderer3D* renderer3D) override;

	virtual void hit(BaseObject & other) override;

	void ultAtak(float deltaTime);
	void Shot(Vector2 pos);
	void BomShot(Vector2 pos);
	
	//プレイヤーの位置を調べる
	Vector2 checkPlayerPos(Vector2 vec);
	static bool lostHoudai;
private:
	CharactorManager* charaManager;
	Timer *mTimer;
	Timer *mTimerDamege;
	Timer *mTimerBom;
	
	float ShotAngle;
	float mDamageHit;
	float ShotRing;//予兆用
	bool shotFlag;
	bool UltFlag;
};
