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
	//�����ɐF�X�ȓG�����Ă����A�̂��ɃG�l�~�[�{�b�N�X�݂����ȓG�̔�����Ă��������Ă���
	//1����ǉ����Ă���
	objectMap.emplace("1", new EnemyBox(*m_pCharaManager, *m_pCamera, 1, Vector2(0, 0)));
	//���ׂ郊�X�g
	std::vector<EnemyBox*> checkVec;
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
		switch (strInt)
		{
		case(0):
			break;
		case(1):
		{
			EnemyBox* enemyBox = new EnemyBox(*m_pCharaManager, *m_pCamera, 1, Vector2(0, 0));
			enemyBox->setPosition(Vector2((colCount - 1) * 64, (lineCnt - 1) * 64));
			checkVec.push_back(enemyBox);  //�}�b�v�ɒǉ�����
			colCount++;
		}
		break;
		default:
			break;
		}
	}
	return checkVec;
}

//CSVReader���g���ēǂݍ���
void MapSpawn::loadMap(std::string fileName)
{
	CSVReader* csvReader = new CSVReader();
	csvReader->read(fileName);
	auto data = csvReader->getData();  //csvReader�œǂݍ��񂾃f�[�^����
	for (int lineCount = 0; lineCount < data.size(); lineCount++)
	{
		mMapObjList.push_back(addObject(lineCount, data[lineCount]));
	}
	CWindow::getInstance().log("�}�b�v�ǂݍ��ݐ���\n");

	delete csvReader; //new�����̂ŉ������

}
//���g����ɂ���
void MapSpawn::clear()
{
	mMapObjList.clear();
}
//�X�V
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
			//������̓L�����N�^�[�}�l�[�W���[�ł�update�ōX�V����Ă��Ȃ��̂ł����ōX�V����
			object->update(deltaTime);
		}
	}
}
//�e�X�g�p
void MapSpawn::draw(Renderer* render,Renderer3D * render3D)
{
	for (auto map : mMapObjList)
	{
		for (auto object : map)
		{
			//������̓L�����N�^�[�}�l�[�W���[�ł�draw�ōX�V����Ă��Ȃ��̂ł����ōX�V����
			object->draw(render,render3D);
		}
	}
}
//�����̎擾
int MapSpawn::getWidth()
{
	//��̒����Ƃ�������̉������|����
	int col = (int)mMapObjList[0].size();
	int width = col * 64;   //�����}�b�v�̃T�C�Y
	return width;
}
//�c���̎擾
int MapSpawn::getHeight()
{
	//�s�̒����Ƃ�������̏c�����|����
	int row = (int)mMapObjList[0].size();
	int height = row * 64;
	return height;
}
