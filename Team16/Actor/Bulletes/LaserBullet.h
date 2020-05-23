#pragma once
#include"DxLib.h"
#include "../../Math/Vector2.h"
#include"../CharaManager/CharactorManager.h"
#include"../../Device/Renderer.h"
#include"../CharaManager/BaseObject.h"
#include"../../Support/CWindow.h"

class LaserBullet : public BaseObject
{
public:
	LaserBullet(Vector2 pos, CharactorManager* c, Type t, float angle,Vector2* posLaer);
	~LaserBullet();
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

	bool Death;
	CharactorManager* charaManager;
	Type b_SetType;
	Vector2 playerPos;//�v���C���[��pos;
	float angle;
	float PI = 3.141592653589793f;//�~����
	float bulletAngle;			  //bullet�̊p�x
	Vector2 RotationZ(float ang);//z����]�̐�������

	float laserY;
	Vector2 *v;
};