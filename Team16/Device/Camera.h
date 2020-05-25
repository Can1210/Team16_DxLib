#pragma once
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "../Math/Vector3.h"
#include "../Actor/CharaManager/CharactorManager.h"
//�J�����N���X
class Camera
{
public:
	Camera();
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
	void setPosition(Vector2 position);
	//������ς���
	void setSpeed(float speed);
	//�����Ă���ʒu��Ԃ�
	Vector3 getLookAtPosition() const;
	//�����̕ύX
	void setLookAtPosition(Vector3 lookAtPos);
#pragma endregion

private:
	//�J�����̈ړ�
	void cameraMove(float deltaTime);



private:

	Vector3 mPosition;        //�J�����ʒu
	float mSpeed;              //�X�s�[�h
	Vector3 mLookAtPosition;  //����
	Vector3 mAngle;           //��]
	Vector3 mVelocity;        //�ړ���

	float lookAtDistance;
};

#endif // !_CAMERA_H_
