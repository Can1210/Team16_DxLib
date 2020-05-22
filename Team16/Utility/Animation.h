#pragma once
#ifndef _ANIMATION_H_
#define _ANIMATION_H_


#include "../Math/Vector2.h"
#include "Timer.h"

//�A�j���[�V�����N���X
class Animation
{
public:
	Animation(Vector2 drawSize, Vector2 textureSize,float changeTime);
	~Animation();

	//������
	void initialize();

	//�X�V
	void update(float deltaTime);
	//�A�j���[�V�����؂�ւ�
	void changeAnimation(float deltaTime);

#pragma region Get
	//������W�̎擾
	Vector2 getLeftSize() const;
	//�E����W�̒ǉ�
	Vector2 getDrawSize() const;

#pragma endregion

private:

	Vector2 mLeftSize;      //������W
	Vector2 mDrawSize;      //�T�C�Y
	Vector2 mTextureSize;   //�摜���T�C�Y
	float mChangeTime;      //�؂�ւ�����

	Timer* m_pTimer;        //�^�C�}�[�N���X



};

#endif // !_ANIMATION_H_