#include "Camera.h"
#include "../Actor/CharaManager/DeathPoint.h"
#include "../Support/CWindow.h"

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
	mSpeed = 100.0f;
}
//�X�V
void Camera::update(float deltaTime)
{
	cameraMove(deltaTime);
}

void Camera::cameraMove(float deltaTime)
{



	mVelocity.y = 1.0f;
	mPosition.y += mVelocity.y * mSpeed * deltaTime;

	if (mPosition.y >= 6050.0f)
	{
		mPosition.y = 6050.0f;
	}



	mLookAtPosition.y = mPosition.y;   //Y�����������Ȃ�
	// �J�����̐ݒ�ɔ��f����
	SetCameraPositionAndTarget_UpVecY(VGet(mPosition.x, mPosition.y, mPosition.z), VGet(mLookAtPosition.x, mLookAtPosition.y, mLookAtPosition.z));

	DeathPoint::getInstance().setUp(mPosition.y + 800.0f);
	DeathPoint::getInstance().setDown(mPosition.y - 500.0f);
	DeathPoint::getInstance().setLeft(mPosition.x - 500.0f);
	DeathPoint::getInstance().setRight(mPosition.x + 500.0f);
	DeathPoint::getInstance().setCenter(mPosition.y);
	DeathPoint::getInstance().cameraVely(mVelocity.y * mSpeed);

	

	//CWindow::getInstance().log("�����W %f\n", mPosition.y);
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
	DeathPoint::getInstance().setCenter(mPosition.y);
	DeathPoint::getInstance().cameraVely(mVelocity.y * mSpeed);
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