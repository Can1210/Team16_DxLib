#pragma once
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "DxLib.h"
#include "../Math/Vector3.h"
#include "../Actor/CharaManager/CharactorManager.h"
#include "../Device/Input.h"

//�J�����N���X
class Camera
{
public:
	Camera(CharactorManager& chractorManager, Vector2 pos);
	~Camera();
	//������
	void initialize();
	//�X�V
	void update(float deltaTime);

	//�J�����̍X�V
	void cameraUpdate();

#pragma region  Get/Set
	//�ʒu��Ԃ�
	Vector3 getPosition() const;
	//�ʒu��ύX����
	void setPosition(Vector3 position);
	//�����Ă���ʒu��Ԃ�
	Vector3 getLookAtPosition() const;
	//�����̕ύX
	void setLookAtPosition(Vector3 lookAtPos);

private:
	//�J�����̈ړ�
	void cameraMove(float deltaTime);


#pragma endregion

private:

	Vector3 mPosition;        //�J�����ʒu
	float mSpeed;              //�X�s�[�h
	Vector3 mLookAtPosition;  //����
	Vector3 mAngle;           //��]
	Vector3 mVelocity;        //�ړ���

	CharactorManager* m_pCharactorManager;   //�v���C���[��T���p
	const float lookAtDistance;   //�Ƃ肠����700
	Input* input;
};

#endif // !_CAMERA_H_
