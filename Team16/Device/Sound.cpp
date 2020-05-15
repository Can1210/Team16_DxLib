#include "Sound.h"


//�R���X�g���N�^
Sound::Sound():
	mBGMVolume(50),
	mSEVolume(7000)
{
}

//�f�X�X�g���N�^
Sound::~Sound()
{
}
//���ʏ�����
void Sound::volumeInitialize()
{
	mBGMVolume = 50;
	mSEVolume = 7000;
}
#pragma region BGM�֌W

//BGM�Đ�
void Sound::playBGM(std::string soundName)
{

	//mCurrentBGM�̂��ƂŃG���[���N���邩���F�w�肵�Ă�����̂��Ȃ��ꍇ���|��
	

	//�����ȂȂ牽�����Ȃ�
	//if (mCurrentBGM == soundName)return;

	//BGM�͍Đ����Ȃ��~
	if (checkPlayingBGM(soundName))
	{
		StopSoundMem(SoundLoad::getInstance().setBGM(soundName));
	}
	//���݂�BGM��ύX
	mCurrentBGM = soundName;
	// ���ʂ̐ݒ萮����
	ChangeVolumeSoundMem(255 * mBGMVolume / 100, SoundLoad::getInstance().setBGM(mCurrentBGM));

	//�ŏ�����Đ�����
	PlaySoundMem(SoundLoad::getInstance().setBGM(mCurrentBGM), DX_PLAYTYPE_LOOP);
}
//BGM���Đ�����Ă��邩�ǂ������ׂ�
bool Sound::checkPlayingBGM(std::string bgmName)
{
	return CheckSoundMem(SoundLoad::getInstance().setBGM(bgmName));
}
//�ꎞ��~
void Sound::pauseBGM()
{
	if (checkPlayingBGM(mCurrentBGM))
		StopSoundMem(SoundLoad::getInstance().setBGM(mCurrentBGM));
}
//�ꎞ��~����Đ�
void Sound::resumeBGM()
{
	if (checkPlayingBGM(mCurrentBGM))
		PlaySoundMem(SoundLoad::getInstance().setBGM(mCurrentBGM), DX_PLAYTYPE_LOOP,FALSE);
}
//BGM���ʒ���
void Sound::setBGMVolume(int volume)
{
	if (volume >= 10000) volume = 10000;
	if (volume <= 0) volume = 0;
	mBGMVolume = volume;
}


#pragma endregion

#pragma region SE�֌W

//SE�Đ�
void Sound::playSE(std::string seName)
{
	
	PlaySoundMem(SoundLoad::getInstance().setSE(seName), DX_PLAYTYPE_BACK);
}
//SE���ʒ���
void Sound::setSEVolume(int volume)
{
	//�␳
	if (volume >= 100) volume = 100;
	if (volume <= 0) volume = 0;

	mSEVolume = volume;
}

#pragma endregion
