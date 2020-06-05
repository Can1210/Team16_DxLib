#pragma once
#include"../CharaManager/BaseObject.h"
#include"../CharaManager/CharactorManager.h"



class Boss3 :public BaseObject
{
public:
	Boss3(Vector2 pos, CharactorManager *c);
	~Boss3();
	// BaseObject を介して継承されました
	virtual void initialize() override;

	virtual void update(float deltaTime) override;

	virtual void draw(Renderer * renderer, Renderer3D* renderer3D) override;

	virtual void hit(BaseObject & other) override;

	void HoudaiSpow();
	//攻撃関係
	void attack(float deltaTime);
	void shot(Vector2 pos);
	void circleShot(float deltaTime);
	void circleMove(float deltaTime);
	bool charge();

	Vector2 checkPlayerPos(Vector2 vec);
private:
	bool DamgeFlag;
	CharactorManager* charaManager;
	Timer *mTimer;
	Timer* m_pCirecleTimer;
	Timer* m_pCirecleEndTimer;
	Timer* m_pCamreraTimer;

	float shotAngle;
	float bomshotAngle;
	Vector2 mPlayerPos;   //プレイヤーの位置
	Vector2 angleVec;

	//円運動
	float x;
	float y;
	float radius;
	float rotateSpeed;
	float moveTime;

	float mChargeScalse;
	bool mIsCharge;
	bool setFlag;
};