#pragma once
#include"../CharaManager/CharactorManager.h"
#include"../CharaManager/BaseObject.h"

class WallReflectionBullet : public BaseObject
{
public:
	WallReflectionBullet(Vector2 pos, CharactorManager* c, Type t, int angle);
	~WallReflectionBullet();
	//�e�̃^�C�v����
	void setBulletType();
	//������
	virtual void initialize()override;
	//�X�V
	virtual void update(float deltaTime)override;
	//�`��
	virtual void draw(Renderer* renderer, Renderer3D* renderer3D)override;
	//�����肽���̏���
	virtual void hit(BaseObject& other) override;

private:
	enum WallType {
		R,
		L,
		None,
	};

	Vector2 RotationZ(float ang);//z����]�̐�������

private:
	CharactorManager* charaManager;
	Type b_SetType;
	int angle;
	float PI = 3.141592653589793f;//�~����
	float bulletAngle;			  //bullet�̊p�x

	WallType type;
};