#pragma once
#ifndef _MAPSPAWN_H_
#define _MAPSPAWN_H_

#include "../../Device/CSVReader.h"
#include "../CharaManager/EnemyBox.h"

//マップ型生成クラス
class MapSpawn
{
public:
	MapSpawn(CharactorManager& charactorManager);
	~MapSpawn();

	void addObject(int lineCnt, std::vector<std::string> record);
	//マップの読み込み
	void loadMap(std::string fileName);
	float getWidth();  //幅
	float getHeight(); //高さ

private:
	CharactorManager* m_pCharaManager;				   //キャラマネを保存
	CSVReader* m_pCsvReader;
};


#endif // !_MAPSPAWN_H_
