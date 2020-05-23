#include "CSVReader.h"

#include <iostream>
#include <fstream>
#include <sstream> 

CSVReader::CSVReader():
	fileData(NULL)
{
}


CSVReader::~CSVReader()
{
	clear();
}
//�ǂݍ���
bool CSVReader::read(std::string& fileName)
{
	//�t�@�C�����J��
	std::fstream fileStream(fileName);
	//�t�@�C�����J���Ȃ�������I��
	if (!fileStream.is_open()) return false;
	//��؂蕶���̐ݒ�
	const char delimiter = ',';
	//�t�@�C����ǂݍ���
	while (!fileStream.eof())
	{
		//1�s�ǂݍ���
		std::string buffer;
		fileStream >> buffer;
		//�t�@�C������ǂݍ���1�s�̕��������؂蕶���ŕ����A���X�g�ɒǉ�
		std::vector<std::string> record;          //�P�s���̕�����̃��X�g
		std::istringstream streamBuffer(buffer);  //������X�g���[��
		std::string token;						  //�P�Z�����̕�����

		while (std::getline(streamBuffer,token,delimiter))
		{
			//1�Z�����̕���������X�g�ɒǉ�����
			record.insert(record.begin(), token);
		}
		//1�s���̕�������o�͈����̃��X�g�ɒǉ�����
		fileData.insert(fileData.begin(), record);
	}
	return true;
}

void CSVReader::clear()
{
	//�t�@�C��������ɂ���
	fileData.clear();
}

std::vector<std::vector<std::string>> CSVReader::getData()
{
	return fileData;
}

float CSVReader::getSize_X()
{
	return fileData[0].size();
}

float CSVReader::getSize_Y()
{
	return fileData.size();
}
