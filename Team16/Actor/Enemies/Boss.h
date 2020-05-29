#pragma once
#include"../CharaManager/BaseObject.h"
#include"../CharaManager/CharactorManager.h"



class Boss :public BaseObject
{
public:
	Boss(Vector2 pos, CharactorManager *c);
	~Boss();
	// BaseObject ‚ğ‰î‚µ‚ÄŒp³‚³‚ê‚Ü‚µ‚½
	virtual void initialize() override;

	virtual void update(float deltaTime) override;

	virtual void draw(Renderer * renderer, Renderer3D* renderer3D) override;

	virtual void hit(BaseObject & other) override;


	//UŒ‚ŠÖŒW
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
	Vector2 mPlayerPos;   //ƒvƒŒƒCƒ„[‚ÌˆÊ’u
	Vector2 angleVec;

	//‰~‰^“®
	float x;
	float y;
	float radius;
	float rotateSpeed;
	float moveTime;

	float mChargeScalse;
	bool mIsCharge;
};