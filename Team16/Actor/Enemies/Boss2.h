#pragma once
#include"../CharaManager/BaseObject.h"
#include"../CharaManager/CharactorManager.h"



class Boss2 :public BaseObject
{
public:
	Boss2(Vector2 pos, CharactorManager *c);
	~Boss2();
	// BaseObject ÇâÓÇµÇƒåpè≥Ç≥ÇÍÇ‹ÇµÇΩ
	virtual void initialize() override;

	virtual void update(float deltaTime) override;

	virtual void draw(Renderer * renderer, Renderer3D* renderer3D) override;

	virtual void hit(BaseObject & other) override;

	//çUåÇä÷åW
	void shot(Vector2 pos, int t);
	void shot2(Vector2 p, int t);
	bool playerInArea();
private:
	enum Boss2Move {
		Move_1, Move_2, Move_3,Move_4,NoneMove,
	};
	bool DamgeFlag;
	CharactorManager* charaManager;
	Timer *mTimer;
	Timer* m_pCirecleTimer;
	Timer* m_pCirecleEndTimer;
	Timer* m_pCamreraTimer;
	Timer *mTimerDamege;
	int mDamageHit;
	Boss2Move boss2move;
	float rotx;
	int shotTime;

	bool isAnim;
	bool isChange;
	Timer* mAnimTimer;
	Timer* mEndTimer;

};
