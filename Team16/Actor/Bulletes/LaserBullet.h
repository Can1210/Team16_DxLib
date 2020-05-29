#pragma once
#include"../CharaManager/CharactorManager.h"
#include"../CharaManager/BaseObject.h"

class LaserBullet : public BaseObject
{
public:
	LaserBullet(Vector2 pos, CharactorManager* c, Type t, float angle);
	LaserBullet(Vector2 pos, CharactorManager* c, Type t, float angle,bool hitSound);
	~LaserBullet();
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
	Vector2 RotationZ(float ang);//z����]�̐�������

private:
	CharactorManager* charaManager;
	Type b_SetType;
	float PI = 3.141592653589793f;//�~����
	float bulletAngle;			  //bullet�̊p�x

	bool hits;
};