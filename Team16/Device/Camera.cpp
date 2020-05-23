#include "Camera.h"


// ���C����`���͈�
#define LINE_AREA_SIZE			10000.0f

// ���C���̐�
#define LINE_NUM			5


//�R���X�g���N�^
Camera::Camera(CharactorManager& chractorManager,Vector2 pos) :
	mPosition(pos.x, pos.y, lookAtDistance),
	mLookAtPosition(0, 0, 0),
	m_pCharactorManager(&chractorManager),
	lookAtDistance(1000),
	mSpeed(20.0f)
{
}

//�f�X�X�g�N�^
Camera::~Camera()
{
	delete input;
}
//������
void Camera::initialize()
{
	mPosition = Vector3(0,0,lookAtDistance);
	mLookAtPosition = Vector3(0, 0, 0);
	input = new Input();
	input->init();
}
//�X�V
void Camera::update(float deltaTime)
{
	input->update();
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
}


//�ʒu��Ԃ�
Vector3 Camera::getPosition() const
{
	return mPosition;
}
//�ʒu��ύX����
void Camera::setPosition(Vector3 position)
{
	mPosition = position;
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
