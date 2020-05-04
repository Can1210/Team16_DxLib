#include "Camera.h"


// ���C����`���͈�
#define LINE_AREA_SIZE			10000.0f

// ���C���̐�
#define LINE_NUM			5


//�R���X�g���N�^
Camera::Camera(CharactorManager& chractorManager) :
	mPosition(0, 0, lookAtDistance),
	mLookAtPosition(0, 0, 0),
	m_pCharactorManager(&chractorManager),
	lookAtDistance(1000)
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
void Camera::update()
{
	input->update();
	searchPlayer();
	cameraUpdate();
}
void Camera::cameraUpdate()
{
	mLookAtPosition.y = mPosition.y;   //Y�����������Ȃ�
	if (input->isKeyState(KEYCORD::ARROW_DOWN))
	{
		mPosition.z--;
	}
	if (input->isKeyState(KEYCORD::ARROW_UP))
	{
		mPosition.z++;
	}

	// �J�����̐ݒ�ɔ��f����
	SetCameraPositionAndTarget_UpVecY(VGet(mPosition.x, mPosition.y, mPosition.z), VGet(mLookAtPosition.x, mLookAtPosition.y, mLookAtPosition.z));


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
//�v���C���[��T���Ĉʒu���v���C�[�ɂ���
void Camera::searchPlayer()
{
	for (auto object : m_pCharactorManager->getUseList())
	{
		//�I�u�W�F�N�g���v���C���[����Ȃ������烊�^�[��
		if (!object->getType() == Type::PLAYER) continue;

		mPosition.y = object->getPpstion().y;  //y�����������Ȃ�
	}
}

//�ʒu��Ԃ�
Vector3 Camera::getPosition()
{
	return mPosition;
}
//�ʒu��ύX����
void Camera::setPosition(Vector3 position)
{
	mPosition = position;
}
//�����Ă���ʒu��Ԃ�
Vector3 Camera::getLookAtPosition()
{
	return mLookAtPosition;
}
//�����Ă���ʒu��ύX����
void Camera::setLookAtPosition(Vector3 lookAtPos)
{
	mLookAtPosition = lookAtPos;
}