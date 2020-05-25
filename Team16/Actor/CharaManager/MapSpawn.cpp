#include "MapSpawn.h"
#include <unordered_map>
#include "../Enemies/Enemy.h"
#include "../../Support/CWindow.h"

MapSpawn::MapSpawn(CharactorManager& charactorManager, Camera& camera):
	m_pCharaManager(&charactorManager),
	m_pCamera(&camera)
{
}


MapSpawn::~MapSpawn()
{
	delete m_pCsvReader;
}

void MapSpawn::addObject(int lineCnt, std::vector<std::string> record)
{
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
		//0以下なら
		if (strInt < 0)
		{
			colCount++;  //列カウンタを増やす
			continue;
		}

		m_pCharaManager->add(new EnemyBox(*m_pCharaManager, *m_pCamera, strInt, Vector2(((float)((colCount - 1) * 96) - 500.0f), (float)((lineCnt - 1) * 96))));
		colCount++;
	}
}

//CSVReaderを使って読み込む
void MapSpawn::loadMap(std::string fileName)
{
	m_pCsvReader = new CSVReader();
	m_pCsvReader->read(fileName);
	auto data = m_pCsvReader->getData();  //csvReaderで読み込んだデータを代入
	for (int lineCount = 0; lineCount < data.size(); lineCount++)
	{
		addObject(lineCount, data[lineCount]);
	}
	CWindow::getInstance().log("マップ読み込み成功\n");
}
//横幅の取得
float MapSpawn::getWidth()
{
	return (float)(m_pCsvReader->getSize_X() * 96.0f);
}
//縦幅の取得
float MapSpawn::getHeight()
{
	return (float)(m_pCsvReader->getSize_Y()* 96.0f);
}
