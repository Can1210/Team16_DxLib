#pragma once
#ifndef _MAPSPAWN_H_
#define _MAPSPAWN_H_

#include "../../Device/CSVReader.h"
#include "../CharaManager/EnemyBox.h"

//マップ型生成クラス
class MapSpawn
{
public:
	MapSpawn(CharactorManager& charactorManager,Camera& camera);
	~MapSpawn();
	//オブジェクトの追加
	std::vector<EnemyBox*> addObject(int lineCnt, std::vector<std::string> record);
	//マップの読み込み
	void loadMap(std::string fileName);

	//リストのクリア
	void clear();
	//更新
	void update(float deltaTime);

	void object_update(float deltaTime);

	//描画
	void draw(Renderer* render,Renderer3D* render3D);

	int getWidth();  //幅
	int getHeight(); //高さ

private:
	std::vector<std::vector<EnemyBox*>> mMapObjList;   //オブジェクトのマップ配置用
	CharactorManager* m_pCharaManager;				   //キャラマネを保存
	Camera* m_pCamera;                                 //カメラを保存
};


#endif // !_MAPSPAWN_H_
