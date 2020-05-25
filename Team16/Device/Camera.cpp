#include "Camera.h"
#include "../Actor/CharaManager/DeathPoint.h"

// ���C����`���͈�
#define LINE_AREA_SIZE			10000.0f

// ���C���̐�
#define LINE_NUM			5

//�R���X�g���N�^
Camera::Camera()
{
}

//�f�X�X�g�N�^
Camera::~Camera()
{
}
//������
void Camera::initialize()
{
	lookAtDistance = 1000.0f;
	mPosition = Vector3(0.0f,0.0f,lookAtDistance);
	mLookAtPosition = Vector3(0.0f, 0.0f, 0.0f);
	mSpeed = 20.0f;
}
//�X�V
void Camera::update(float deltaTime)
{
	cameraMove(deltaTime);
	cameraUpdate();
}
void Camera::cameraUpdate()
{
	// �ʒu�֌W��������悤�ɒn�ʂɃ��C����`�悷��
	{
		int i;
		VECTOR Pos1;
		VECTOR Pos2;

		SetUseZBufferFlag(TRUE);

		Pos1 = VGet(-LINE_AREA_SIZE / 2.0f, 0.0f, -LINE_AREA_SIZE / 2.0f);
		Pos2 = VGet(-LINE_AREA_SIZE / 2.0f, 0.0f, LINE_AREA_SIZE / 2.0f);
		for (i = 0; i <= LINE_NUM; i++)
		{
			DrawLine3D(Pos1, Pos2, GetColor(255, 255, 255));
			Pos1.x += LINE_AREA_SIZE / LINE_NUM;
			Pos2.x += LINE_AREA_SIZE / LINE_NUM;
		}

		Pos1 = VGet(-LINE_AREA_SIZE / 2.0f, 0.0f, -LINE_AREA_SIZE / 2.0f);
		Pos2 = VGet(LINE_AREA_SIZE / 2.0f, 0.0f, -LINE_AREA_SIZE / 2.0f);
		for (i = 0; i < LINE_NUM; i++)
		{
			DrawLine3D(Pos1, Pos2, GetColor(255, 255, 255));
			Pos1.z += LINE_AREA_SIZE / LINE_NUM;
			Pos2.z += LINE_AREA_SIZE / LINE_NUM;
		}

		SetUseZBufferFlag(FALSE);
	}

}


void Camera::cameraMove(float deltaTime)
{
	mVelocity.y = 1.0f;
	mPosition.y += mVelocity.y * mSpeed * deltaTime;
	mLookAtPosition.y = mPosition.y;   //Y�����������Ȃ�
	// �J�����̐ݒ�ɔ��f����
	SetCameraPositionAndTarget_UpVecY(VGet(mPosition.x, mPosition.y, mPosition.z), VGet(mLookAtPosition.x, mLookAtPosition.y, mLookAtPosition.z));

	DeathPoint::getInstance().setUp(mPosition.y + 800.0f);
	DeathPoint::getInstance().setDown(mPosition.y - 500.0f);
	DeathPoint::getInstance().setLeft(mPosition.x - 500.0f);
	DeathPoint::getInstance().setRight(mPosition.x + 500.0f);
}

#pragma region Get/Set

//�ʒu��Ԃ�
Vector3 Camera::getPosition() const
{
	return mPosition;
}
//�ʒu��ύX����
void Camera::setPosition(Vector2 position)
{
	mPosition = Vector3(position.x, position.y, lookAtDistance);
	DeathPoint::getInstance().setUp(mPosition.y + 800.0f);        //��
	DeathPoint::getInstance().setDown(mPosition.y - 500.0f);	  //��
	DeathPoint::getInstance().setLeft(mPosition.x - 500.0f);	  //�E
	DeathPoint::getInstance().setRight(mPosition.x + 500.0f);	  //��

}
//���x��ς���
void Camera::setSpeed(float speed)
{
	mSpeed = speed;
}
//�����Ă���ʒu��Ԃ�
Vector3 Camera::getLookAtPosition() const
{
	return mLookAtPosition;
}
//�����Ă���ʒu��ύX����
void Camera::setLookAtPosition(Vector3 lookAtPos)
{
	mLookAtPosition = lookAtPos;
}

#pragma endregion