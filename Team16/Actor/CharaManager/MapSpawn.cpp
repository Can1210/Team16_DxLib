#include "MapSpawn.h"
#include <unordered_map>
#include "../Enemies/Enemy.h"
#include "../../Support/CWindow.h"

MapSpawn::MapSpawn(CharactorManager& charactorManager, Camera& camera):
	m_pCharaManager(&charactorManager),
	m_pCamera(&camera),
	mMapObjList(NULL)
{
}


MapSpawn::~MapSpawn()
{
	clear();
}

std::vector<EnemyBox*> MapSpawn::addObject(int lineCnt, std::vector<std::string> record)
{
	std::unordered_map<std::string, EnemyBox*> objectMap;
	objectMap.clear();
	//ここに色々な敵を入れていく、のちにエネミーボックスみたいな敵の箱作ってそいつを入れていく
	//1から追加していく
	objectMap.emplace("1", new EnemyBox(*m_pCharaManager, *m_pCamera, 1, Vector2(0, 0)));
	//調べるリスト
	std::vector<EnemyBox*> checkVec;
	int colCount = 1;  //列カウント用
	//渡された1行から1区切りずつ調べるリストに追加
	for (auto string : record)
	{
		//0のところは何もしない
		if (string == "0")
		{
			colCount++;  //列カウンタを増やす
			continue;
		}
		int strInt = std::stoi(string);
		switch (strInt)
		{
		case(0):
			break;
		case(1):
		{
			EnemyBox* enemyBox = new EnemyBox(*m_pCharaManager, *m_pCamera, 1, Vector2(0, 0));
			enemyBox->setPosition(Vector2((colCount - 1) * 64, (lineCnt - 1) * 64));
			checkVec.push_back(enemyBox);  //マップに追加する
			colCount++;
		}
		break;
		default:
			break;
		}
	}
	return checkVec;
}

//CSVReaderを使って読み込む
void MapSpawn::loadMap(std::string fileName)
{
	CSVReader* csvReader = new CSVReader();
	csvReader->read(fileName);
	auto data = csvReader->getData();  //csvReaderで読み込んだデータを代入
	for (int lineCount = 0; lineCount < data.size(); lineCount++)
	{
		mMapObjList.push_back(addObject(lineCount, data[lineCount]));
	}
	CWindow::getInstance().log("マップ読み込み成功\n");

	delete csvReader; //newしたので解放する

}
//中身を空にする
void MapSpawn::clear()
{
	mMapObjList.clear();
}
//更新
void MapSpawn::update(float deltaTime)
{
	object_update(deltaTime);

}
void MapSpawn::object_update(float deltaTime)
{
	for (auto map : mMapObjList)
	{
		for (auto object : map)
		{
			//こいつらはキャラクターマネージャーでのupdateで更新されていないのでここで更新する
			object->update(deltaTime);
		}
	}
}
//テスト用
void MapSpawn::draw(Renderer* render,Renderer3D * render3D)
{
	for (auto map : mMapObjList)
	{
		for (auto object : map)
		{
			//こいつらはキャラクターマネージャーでのdrawで更新されていないのでここで更新する
			object->draw(render,render3D);
		}
	}
}
//横幅の取得
int MapSpawn::getWidth()
{
	//列の長さといつ当たりの横幅を掛ける
	int col = (int)mMapObjList[0].size();
	int width = col * 64;   //ここマップのサイズ
	return width;
}
//縦幅の取得
int MapSpawn::getHeight()
{
	//行の長さといつ当たりの縦幅を掛ける
	int row = (int)mMapObjList[0].size();
	int height = row * 64;
	return height;
}
