#pragma once
#include"DxLib.h"
#include "../../Math/Vector2.h"
#include"../CharaManager/CharactorManager.h"
#include"../../Device/Renderer.h"
#include"../CharaManager/BaseObject.h"
#include"../../Support/CWindow.h"

class WallReflectionBullet : public BaseObject
{
public:
	WallReflectionBullet(Vector2 pos, CharactorManager* c, Type t, float angle);
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

	bool Death;
	CharactorManager* charaManager;
	Type b_SetType;
	Vector2 playerPos;//�v���C���[��pos;
	float angle;
	float PI = 3.141592653589793f;//�~����
	float bulletAngle;			  //bullet�̊p�x
	Vector2 RotationZ(float ang);//z����]�̐�������

	WallType type;
};