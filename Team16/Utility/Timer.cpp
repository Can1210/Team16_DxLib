#include "Timer.h"


//�R���X�g���N�^
Timer::Timer()
	:mCurrentTime(0)
{
}

//�f�X�X�g���N�^
Timer::~Timer()
{
}
//������
void Timer::initialize()
{
	mCurrentTime = 0;//0�ŏ�����
}
void Timer::update(float deltaTime)
{
	mCurrentTime += deltaTime;         //���݂̎��Ԃɉ��Z����
}
//�^�C�}�[�Z�b�g
bool Timer::timerSet(float setTime)
{
	//���݂̎��Ԃ��ő�ɂȂ�����true
	if (mCurrentTime >= setTime)
	{
		initialize();    //������
		return true;
	}
	return false;
}
//�����Ń��Z�b�g����
bool Timer::timerSet_Self(float setTime)
{
	//���݂̎��Ԃ��ő�ɂȂ�����true
	if (mCurrentTime >= setTime)
	{
		return true;
	}
	return false;
}
