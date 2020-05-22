#pragma once
#include "../CharaManager/BaseObject.h"
#include "../CharaManager/CharactorManager.h"
//�V���b�g�K���̒e
class ShotgunBullet : public BaseObject
{
public:
	ShotgunBullet(Vector2 pos, CharactorManager* c, Type t, float angle);
	~ShotgunBullet();
private:
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
	//���S�ɂ����鎞��
	void deathTime(float deltaTime);
	void move(float deltaTime);

	Vector2 RotationZ(float ang);//z����]�̐�������

private:
	bool mIsDeath;
	Type m_SetType;
	Vector2 playerPos;//�v���C���[��pos;
	float angle;
	float PI = 3.141592653589793f;//�~����
	float bulletAngle;			  //bullet�̊p�x
	float mCurrentTime;           //���݂̎���
	float mMaxTime;               //��������
	CharactorManager* m_pCharaManager;

	float alphaNum;      //���l


};

