#pragma once
#ifndef _CSVREADER_H_
#define _CSVREADER_H_
#include <vector>
#include <string>

//CSV�ǂݍ��ރN���X
class CSVReader
{
public:
	CSVReader();
	~CSVReader();
	//CSV�t�@�C����ǂݍ���
	bool read(std::string& fileName);
	//�N���A
	void clear();
	//�ǂݍ��񂾃f�[�^��n��
	std::vector<std::vector<std::string>> getData();

	float getSize_X();
	float getSize_Y();
private:
	std::vector<std::vector<std::string>> fileData;   //SCV�t�@�C���f�[�^
};


#endif // !_CSVREADER_H_