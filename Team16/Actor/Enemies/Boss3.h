#pragma once
#include"../CharaManager/BaseObject.h"
#include"../CharaManager/CharactorManager.h"



class Boss3 :public BaseObject
{
public:
	Boss3(Vector2 pos, CharactorManager *c);
	~Boss3();
	// BaseObject ÇâÓÇµÇƒåpè≥Ç≥ÇÍÇ‹ÇµÇΩ
	virtual void initialize() override;

	virtual void update(float deltaTime) override;

	virtual void draw(Renderer * renderer, Renderer3D* renderer3D) override;

	virtual void hit(BaseObject & other) override;

	void HoudaiSpow();
	void modeChange(float deltaTime);
	void modeChange2(float deltaTime);
	//çUåÇä÷åW
	
	void shot(Vector2 pos);
	void shotM(Vector2 pos, int t);
	void shotL(Vector2 pos, int t);
	void shotB(Vector2 pos, int t);
	void shotX(Vector2 pos, int t);
	void shotLazer(Vector2 pos);
	enum BossShotType
	{L,M,B,X,None};
	BossShotType b_shotT;

	Vector2 checkPlayerPos(Vector2 vec);
private:
	bool DamgeFlag;
	CharactorManager* charaManager;
	Timer *mTimer;
	Timer* m_pCirecleTimer;
	Timer* m_pCirecleEndTimer;
	Timer* m_pCamreraTimer;
	Timer *mTimerDamege;
	Timer *mShotTimer;
	float shotAngle;
	float bomshotAngle;
	Vector2 mPlayerPos;   //ÉvÉåÉCÉÑÅ[ÇÃà íu
	Vector2 angleVec;
	int mDamageHit;

	//â~â^ìÆ
	float x;
	float y;
	float radius;
	float rotateSpeed;
	float moveTime;

	float mChargeScalse;
	bool mIsCharge;
	bool setFlag;
	int lostCnt;
	//ÉÇÅ[ÉhïœçXå„
	bool modeChangeFlag;
	Timer *mTimerM;
	Timer *mTimerL;
	bool UltFlagM;
	bool UltFlagL;
	
	bool shotFlag;
	float ShotRing;//ó\íõ

	int shotTime;

};