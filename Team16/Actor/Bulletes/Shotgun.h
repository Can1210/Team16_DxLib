#pragma once
#include "../CharaManager/BaseObject.h"
#include "../CharaManager/CharactorManager.h"

//�V���b�g�K��
class Shotgun : public BaseObject
{
public:
	Shotgun(Vector2 pos, CharactorManager& c, Type t, float angle);
	~Shotgun();

	
	//������
	virtual void initialize()override;
	//�X�V
	virtual void update(float deltaTime)override;
	//�`��
	virtual void draw(Renderer* renderer, Renderer3D* renderer3D)override;
	//�����肽���̏���
	virtual void hit(BaseObject& other) override;

private:
	//�w��͈̗͂������o��
	int getRandom(int min, int max);
	void createBullet();
	void deathTime(float deltaTime);

private:
	//���񂾂񏬂���������
	Type b_SetType;
	float mCenterAngle;//�e�̊p�x
	int mBulletNum;    //�e�� �����_��
	float mRange;      //40�x�@�@-20�@�`�@20

	CharactorManager* m_pCharactorManager;
	float mCurrentTime;           //���݂̎���
	float mMaxTime;               //��������
	



};
