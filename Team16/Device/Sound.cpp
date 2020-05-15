#include "Sound.h"


//コンストラクタ
Sound::Sound():
	mBGMVolume(50),
	mSEVolume(7000)
{
}

//デスストラクタ
Sound::~Sound()
{
}
//音量初期化
void Sound::volumeInitialize()
{
	mBGMVolume = 50;
	mSEVolume = 7000;
}
#pragma region BGM関係

//BGM再生
void Sound::playBGM(std::string soundName)
{

	//mCurrentBGMのことでエラーが起きるかも：指定しているものがない場合が怖い
	

	//同じ曲なら何もしない
	//if (mCurrentBGM == soundName)return;

	//BGMは再生中なら停止
	if (checkPlayingBGM(soundName))
	{
		StopSoundMem(SoundLoad::getInstance().setBGM(soundName));
	}
	//現在のBGMを変更
	mCurrentBGM = soundName;
	// 音量の設定整数％
	ChangeVolumeSoundMem(255 * mBGMVolume / 100, SoundLoad::getInstance().setBGM(mCurrentBGM));

	//最初から再生する
	PlaySoundMem(SoundLoad::getInstance().setBGM(mCurrentBGM), DX_PLAYTYPE_LOOP);
}
//BGMが再生されているかどうか調べる
bool Sound::checkPlayingBGM(std::string bgmName)
{
	return CheckSoundMem(SoundLoad::getInstance().setBGM(bgmName));
}
//一時停止
void Sound::pauseBGM()
{
	if (checkPlayingBGM(mCurrentBGM))
		StopSoundMem(SoundLoad::getInstance().setBGM(mCurrentBGM));
}
//一時停止から再生
void Sound::resumeBGM()
{
	if (checkPlayingBGM(mCurrentBGM))
		PlaySoundMem(SoundLoad::getInstance().setBGM(mCurrentBGM), DX_PLAYTYPE_LOOP,FALSE);
}
//BGM音量調節
void Sound::setBGMVolume(int volume)
{
	if (volume >= 10000) volume = 10000;
	if (volume <= 0) volume = 0;
	mBGMVolume = volume;
}


#pragma endregion

#pragma region SE関係

//SE再生
void Sound::playSE(std::string seName)
{
	
	PlaySoundMem(SoundLoad::getInstance().setSE(seName), DX_PLAYTYPE_BACK);
}
//SE音量調節
void Sound::setSEVolume(int volume)
{
	//補正
	if (volume >= 100) volume = 100;
	if (volume <= 0) volume = 0;

	mSEVolume = volume;
}

#pragma endregion
