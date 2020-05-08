#pragma once
#ifndef _SOUNDLOAD_H_
#define _SOUNDLOAD_H_
#include <DxLib.h>
#include <string>
#include<unordered_map>
#include "../../Support/Singleton.h"


//音を読み込むクラス
class SoundLoad : public Singleton<SoundLoad>
{
protected:
	SoundLoad();
	virtual ~SoundLoad();
public:

	friend class Singleton<SoundLoad>;          //Singletonでのインスタンス作成は許可
	//BGMの追加（扱いたい名前,音の名前（パスも含める））
	void addBGM(std::string callName, const TCHAR* soundName);
	//BGMの呼び出し
	int  setBGM(std::string callName);
	//SEの追加（扱いたい名前,音の名前（パスも含める））
	void addSE(std::string callName, const TCHAR* soundName);
	//SEの呼び出し
	int  setSE(std::string callName);


private:
	std::unordered_map<const TCHAR*, std::string> storageBGMMap;  //BGM格納用
	std::unordered_map<std::string, int> callBGMMap;

	std::unordered_map<const TCHAR*, std::string> storageSEMap;   //SE格納用
	std::unordered_map<std::string, int> callSEMap;

};

#endif // !_SOUNDLOAD_H_