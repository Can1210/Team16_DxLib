#pragma once
#ifndef _MAPSPAWN_H_
#define _MAPSPAWN_H_

#include "../../Device/CSVReader.h"
#include "../CharaManager/EnemyBox.h"

//�}�b�v�^�����N���X
class MapSpawn
{
public:
	MapSpawn(CharactorManager& charactorManager);
	~MapSpawn();

	void addObject(int lineCnt, std::vector<std::string> record);
	//�}�b�v�̓ǂݍ���
	void loadMap(std::string fileName);
	float getWidth();  //��
	float getHeight(); //����

private:
	CharactorManager* m_pCharaManager;				   //�L�����}�l��ۑ�
	CSVReader* m_pCsvReader;
};


#endif // !_MAPSPAWN_H_
