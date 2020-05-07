#include "SoundLoad.h"



SoundLoad::SoundLoad()
{
}


SoundLoad::~SoundLoad()
{
	//終了時空にする
	storageBGMMap.clear();   
	callBGMMap.clear();
	storageSEMap.clear();
	callSEMap.clear();
}
//音の追加
void SoundLoad::addBGM(std::string callName, const TCHAR * soundName)
{
	//すでに読み込み済みならリターン
	if (!(storageBGMMap.size == 0))
	{
		auto result = storageBGMMap.find(soundName);
		if (result != storageBGMMap.end()) return;
	}
	//音の追加
	storageBGMMap.emplace(soundName, callName);     //引数情報を追加
	int sound = LoadSoundMem(soundName);			//音を読み込む
	callBGMMap.emplace(callName, sound);			//作った番号と呼び出し名を追加
}
//音を指定
int SoundLoad::setBGM(std::string callName)
{
	return callBGMMap.at(callName);
}

void SoundLoad::addSE(std::string callName, const TCHAR * soundName)
{
	//すでに読み込み済みならリターン
	if (!(storageSEMap.size == 0))
	{
		auto result = storageSEMap.find(soundName);
		if (result != storageSEMap.end()) return;
	}
	//音の追加
	storageSEMap.emplace(soundName, callName);     //引数情報を追加
	int sound = LoadSoundMem(soundName);			//音を読み込む
	callSEMap.emplace(callName, sound);			//作った番号と呼び出し名を追加
}

int SoundLoad::setSE(std::string callName)
{
	return callSEMap.at(callName);
}
