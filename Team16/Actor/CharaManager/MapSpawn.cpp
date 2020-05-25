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
	int colCount = 1;  //��J�E���g�p
	//�n���ꂽ1�s����1��؂肸���ׂ郊�X�g�ɒǉ�
	for (auto string : record)
	{
		//0�̂Ƃ���͉������Ȃ�
		if (string == "0")
		{
			colCount++;  //��J�E���^�𑝂₷
			continue;
		}
		int strInt = std::stoi(string);
		//0�ȉ��Ȃ�
		if (strInt < 0)
		{
			colCount++;  //��J�E���^�𑝂₷
			continue;
		}

		m_pCharaManager->add(new EnemyBox(*m_pCharaManager, *m_pCamera, strInt, Vector2(((float)((colCount - 1) * 96) - 500.0f), (float)((lineCnt - 1) * 96))));
		colCount++;
	}
}

//CSVReader���g���ēǂݍ���
void MapSpawn::loadMap(std::string fileName)
{
	m_pCsvReader = new CSVReader();
	m_pCsvReader->read(fileName);
	auto data = m_pCsvReader->getData();  //csvReader�œǂݍ��񂾃f�[�^����
	for (int lineCount = 0; lineCount < data.size(); lineCount++)
	{
		addObject(lineCount, data[lineCount]);
	}
	CWindow::getInstance().log("�}�b�v�ǂݍ��ݐ���\n");
}
//�����̎擾
float MapSpawn::getWidth()
{
	return (float)(m_pCsvReader->getSize_X() * 96.0f);
}
//�c���̎擾
float MapSpawn::getHeight()
{
	return (float)(m_pCsvReader->getSize_Y()* 96.0f);
}
