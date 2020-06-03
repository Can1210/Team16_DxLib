#pragma once
#include"../CharaManager/CharactorManager.h"
#include"../CharaManager/BaseObject.h"


class CircleBullet :public BaseObject
{
public:
	CircleBullet(Vector2 pos, CharactorManager* c, Type t, float angle);
	~CircleBullet();
	//������
	virtual void initialize()override;
	//�X�V
	virtual void update(float deltaTime)override;
	//�`��
	virtual void draw(Renderer* renderer, Renderer3D* renderer3D)override;
	//�����肽���̏���
	virtual void hit(BaseObject& other) override;

private:
	//�e�̃^�C�v����
	void setBulletType();

private:
	CharactorManager* charaManager;
	Type b_SetType;

	bool curHit;
};
