#pragma once
#ifndef _SOUND_H_
#define _SOUND_H_
#include "Loader/SoundLoad.h"
#include "../Support/Singleton.h"

//���Đ��N���X
class Sound :public Singleton<Sound>
{
protected:
	Sound();
	virtual ~Sound();
public:
	friend class Singleton<Sound>;     //Singleton�ł̃C���X�^���X�쐬�͋���
	//���ʏ�����
	void volumeInitialize();

#pragma region BGM�֌W
	//BGM�Đ�
	void playBGM(std::string bgmName);
	//�Đ������ǂ������ׂ�
	bool checkPlayingBGM(std::string bgmName);
	//BGM�ꎞ��~
	void pauseBGM();
	//��~��BGM���Đ�
	void resumeBGM();
	void setBGMVolume(int volume);
#pragma endregion

#pragma region SE�֌W
	//SE�Đ�
	void playSE(std::string seName);
	void setSEVolume(int volume);
#pragma endregion


private:
	std::string mCurrentBGM;   //���ݍĐ�����BGM
	int mSEVolume;             //5000�ȉ��͂قƂ�Ǖ������Ȃ����A�����Ȃ艹�ʂ��オ��
	int mBGMVolume;			   //100����\�L0�܂ł̐���%

};

#endif // !_SOUND_H_
