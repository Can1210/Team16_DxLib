#pragma once
#include"../CharaManager/BaseObject.h"
#include"../CharaManager/CharactorManager.h"
#include"../Bulletes/BomBallet.h"


class BomEnemy :public BaseObject
{
public:
	BomEnemy(Vector2 pos, CharactorManager *c);
	~BomEnemy();

	// BaseObject ����Čp������܂���
	virtual void initialize() override;

	virtual void update(float deltaTime) override;

	virtual void draw(Renderer * renderer, Renderer3D* renderer3D) override;

	virtual void hit(BaseObject & other) override;
	void shot(Vector2 pos);
	Vector2 checkPlayerPos(Vector2 vec);

	bool isShot();
	
private:
	bool DamgeFlag;
	CharactorManager* charaManager;
	Timer *mTimer;
	Vector2 mPlayerPos;   //�v���C���[�̈ʒu

};
