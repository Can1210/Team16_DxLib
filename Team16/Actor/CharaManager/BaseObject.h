#pragma once
#ifndef _BASEOBJECT_H_
#define _BASEOBJECT_H_
#include "../../Device/Renderer.h"
#include "../../Device/Renderer3D.h"
#include "../../Math/Vector2.h"
#include "../../Utility/Timer.h"
//���̂̃^�C�v
enum Type
{
	PLAYER,
	ENEMY,
	PLAYER_BULLET,
	ENEMY_BULLET,
	CHANGE_BULLET,
};

//�`�悷��I�u�W�F�N�g�̊��N���X
class BaseObject
{


public:
	BaseObject();
	virtual ~BaseObject();

	//������
	virtual void initialize() = 0;
	//�X�V
	virtual void update(float deltaTime) = 0;
	//�`��
	virtual void draw(Renderer* renderer, Renderer3D* renderer3D) = 0;
	//�����肽���̏���
	virtual void hit(BaseObject& other) = 0;

#pragma region Get/Set

	//���S���Ă��邩
	virtual bool getIsDeath()const;
	virtual void setIsDeath(bool isDeath);
	//�����̎��
	virtual Type getType()const;
	//�����̈ʒu
	virtual Vector2 getPpstion()const;
	//�����̔��a
	virtual float getCircleSize()const;
#pragma endregion

	//�~���m�̓����蔻��
	bool circle_circle_Collision(BaseObject& other);

protected:
	int b_mHp;                //�̗�
	float b_mSpeed;           //����
	float b_mCircleSize;      //�~�̔���̔��a
	Vector2 b_mPosittion;     //�ʒu
	Vector2 b_mVelocity;      //�ړ�����
	Vector2 b_mSize;          //�摜�T�C�Y
	bool b_mIsDeath;          //���񂾂��ǂ���
	Type b_mType;             //�����̃^�C�v
	float b_mAngle;//�p�x
	bool b_mEndFlag;//�Q�[���I�[�o�[

	
};


#endif // !_BASEOBJECT_H_
