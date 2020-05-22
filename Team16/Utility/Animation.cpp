#include "Animation.h"




//�R���X�g���N�^
Animation::Animation(Vector2 drawSize, Vector2 textureSize, float changeTime):
	mDrawSize(drawSize),
	mTextureSize(textureSize),
	m_pTimer(new Timer()),
	mChangeTime(changeTime)
{
}
//�f�X�X�g���N�^
Animation::~Animation()
{
	delete m_pTimer;
}
//������
void Animation::initialize()
{
	m_pTimer->initialize();
}
//�X�V
void Animation::update(float deltaTime)
{
	changeAnimation(deltaTime);
}
//�A�j���[�V�����؂�ւ�
void Animation::changeAnimation(float deltaTime)
{
	m_pTimer->update(deltaTime);   //�X�V
	//�^�C�}�[�̃Z�b�g
	if (m_pTimer->timerSet(mChangeTime))
	{
		//������W���e�N�X�`���T�C�Y���ł����Ȃ�����ʒu��0�ɖ߂�
		if ((mLeftSize.x + mDrawSize.x) >= mTextureSize.x)
		{
			mLeftSize.x = 0;
		}
		else
		{
			//������W��ύX����
			mLeftSize.x += mDrawSize.x;
		}
	}
}
//������W�̎擾
Vector2 Animation::getLeftSize() const
{
	return mLeftSize;
}

//�`��T�C�Y�̎擾
Vector2 Animation::getDrawSize() const
{
	return mDrawSize;
}
