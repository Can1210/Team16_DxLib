#pragma once
#ifndef _SOUNDLOAD_H_
#define _SOUNDLOAD_H_
#include <DxLib.h>
#include <string>
#include<unordered_map>
#include "../../Support/Singleton.h"


//����ǂݍ��ރN���X
class SoundLoad : public Singleton<SoundLoad>
{
protected:
	SoundLoad();
	virtual ~SoundLoad();
public:

	friend class Singleton<SoundLoad>;          //Singleton�ł̃C���X�^���X�쐬�͋���
	//BGM�̒ǉ��i�����������O,���̖��O�i�p�X���܂߂�j�j
	void addBGM(std::string callName, const TCHAR* soundName);
	//BGM�̌Ăяo��
	int  setBGM(std::string callName);
	//SE�̒ǉ��i�����������O,���̖��O�i�p�X���܂߂�j�j
	void addSE(std::string callName, const TCHAR* soundName);
	//SE�̌Ăяo��
	int  setSE(std::string callName);


private:
	std::unordered_map<const TCHAR*, std::string> storageBGMMap;  //BGM�i�[�p
	std::unordered_map<std::string, int> callBGMMap;

	std::unordered_map<const TCHAR*, std::string> storageSEMap;   //SE�i�[�p
	std::unordered_map<std::string, int> callSEMap;

};

#endif // !_SOUNDLOAD_H_