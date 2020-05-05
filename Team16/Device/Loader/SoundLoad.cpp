#include "SoundLoad.h"



SoundLoad::SoundLoad()
{
}


SoundLoad::~SoundLoad()
{
	//�I������ɂ���
	storageBGMMap.clear();   
	callBGMMap.clear();
	storageSEMap.clear();
	callSEMap.clear();
}
//���̒ǉ�
void SoundLoad::addBGM(std::string callName, const TCHAR * soundName)
{
	//���łɓǂݍ��ݍς݂Ȃ烊�^�[��
	if (!(storageBGMMap.size == 0))
	{
		auto result = storageBGMMap.find(soundName);
		if (result != storageBGMMap.end()) return;
	}
	//���̒ǉ�
	storageBGMMap.emplace(soundName, callName);     //��������ǉ�
	int sound = LoadSoundMem(soundName);			//����ǂݍ���
	callBGMMap.emplace(callName, sound);			//������ԍ��ƌĂяo������ǉ�
}
//�����w��
int SoundLoad::setBGM(std::string callName)
{
	return callBGMMap.at(callName);
}

void SoundLoad::addSE(std::string callName, const TCHAR * soundName)
{
	//���łɓǂݍ��ݍς݂Ȃ烊�^�[��
	if (!(storageSEMap.size == 0))
	{
		auto result = storageSEMap.find(soundName);
		if (result != storageSEMap.end()) return;
	}
	//���̒ǉ�
	storageSEMap.emplace(soundName, callName);     //��������ǉ�
	int sound = LoadSoundMem(soundName);			//����ǂݍ���
	callSEMap.emplace(callName, sound);			//������ԍ��ƌĂяo������ǉ�
}

int SoundLoad::setSE(std::string callName)
{
	return callSEMap.at(callName);
}
