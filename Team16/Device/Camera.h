#pragma once
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "../Math/Vector3.h"
#include "../Actor/CharaManager/CharactorManager.h"
#include "../Support/Singleton.h"
//�J�����N���X
class Camera : public Singleton<Camera>
{
protected:
	Camera();
	virtual ~Camera();

public:
	friend class Singleton<Camera>;  //Singleton�ł̃C���X�^���X�쐬�͋���
	//������
	void initialize();
	//�X�V
	void update(float deltaTime);

#pragma region  Get/Set
	//�ʒu��Ԃ�
	Vector3 getPosition() const;
	//�ʒu��ύX����
	void setPosition(Vector2 position);
	//������ς���
	void setSpeed(float speed);
	float getSpeed()const;

	//�~�܂�t���O
	bool getStop() const;
	void setStop(bool stop);
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
	bool isStop;


};

#endif // !_CAMERA_H_
