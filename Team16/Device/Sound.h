#pragma once
#ifndef _SOUND_H_
#define _SOUND_H_
#include "Loader/SoundLoad.h"
#include "../Support/Singleton.h"

//音再生クラス
class Sound :public Singleton<Sound>
{
protected:
	Sound();
	virtual ~Sound();
public:
	friend class Singleton<Sound>;     //Singletonでのインスタンス作成は許可
	//音量初期化
	void volumeInitialize();

#pragma region BGM関係
	//BGM再生
	void playBGM(std::string bgmName);
	//再生中かどうか調べる
	bool checkPlayingBGM(std::string bgmName);
	//BGM一時停止
	void pauseBGM();
	//停止中BGMを再生
	void resumeBGM();
	void setBGMVolume(int volume);
#pragma endregion

#pragma region SE関係
	//SE再生
	void playSE(std::string seName);
	void setSEVolume(int volume);
#pragma endregion


private:
	std::string mCurrentBGM;   //現在再生中のBGM
	int mSEVolume;             //5000以下はほとんど聞こえないし、いきなり音量が上がる
	int mBGMVolume;			   //100から表記0までの整数%

};

#endif // !_SOUND_H_
