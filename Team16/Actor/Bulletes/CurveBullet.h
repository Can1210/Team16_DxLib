#pragma once
#include"DxLib.h"
#include "../../Math/Vector2.h"
#include"../CharaManager/CharactorManager.h"
#include"../../Device/Renderer.h"
#include"../CharaManager/BaseObject.h"
#include"../../Support/CWindow.h"

class CurveBullet : public BaseObject
{
public:
	CurveBullet(Vector2 pos, CharactorManager* c, Type t, float angle,float deltaTime);
	~CurveBullet();
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
	float angle;
	bool Death;
	CharactorManager* charaManager;
	Type b_SetType;

	float PI = 3.141592653589793;//�~����
	float bulletAngle;			  //bullet�̊p�x
	bool isFound;//���������ǂ���
	float t;
	float rndTime;
	BaseObject* obj;//�^�[�Q�b�g�̃I�u�W�F
	Vector2 playerPos;//�v���C���[��pos;
	Vector2 target1, target2,enemyPos;

	void getOtherPos();	//otherPos������
	int GetRandom(int min, int max);
	int GetRandom(int min, int max ,float t);
	Vector2 RotationZ(float ang);//z����]�̐�������
	Vector2 traking(Vector2 v1);		//�e���^�[�Q�b�g�ɋ߂���
	Vector2 VecLerp(Vector2 v1,Vector2 v2,float t);	//lerp
	Vector2 Curve(Vector2 v0, Vector2 v1, Vector2 v2, Vector2 v3, float t);
};