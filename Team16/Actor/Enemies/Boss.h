#pragma once
#include"../CharaManager/BaseObject.h"
#include"../CharaManager/CharactorManager.h"



class Boss :public BaseObject
{
public:
	Boss(Vector2 pos, CharactorManager *c);
	~Boss();
	// BaseObject ����Čp������܂���
	virtual void initialize() override;

	virtual void update(float deltaTime) override;

	virtual void draw(Renderer * renderer, Renderer3D* renderer3D) override;

	virtual void hit(BaseObject & other) override;


	//�U���֌W
	void attack(float deltaTime);
	void shot(Vector2 pos);
	void circleShot(float deltaTime);

	Vector2 checkPlayerPos(Vector2 vec);
private:
	bool DamgeFlag;
	CharactorManager* charaManager;
	Timer *mTimer;
	Timer* m_pCirecleTimer;
	Timer* m_pCirecleEndTimer;

	float shotAngle;
	float bomshotAngle;
	Vector2 mPlayerPos;   //�v���C���[�̈ʒu
	Vector2 angleVec;
};
