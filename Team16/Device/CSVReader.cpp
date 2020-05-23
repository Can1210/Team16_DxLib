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
//読み込み
bool CSVReader::read(std::string& fileName)
{
	//ファイルを開く
	std::fstream fileStream(fileName);
	//ファイルを開けなかったら終了
	if (!fileStream.is_open()) return false;
	//区切り文字の設定
	const char delimiter = ',';
	//ファイルを読み込む
	while (!fileStream.eof())
	{
		//1行読み込む
		std::string buffer;
		fileStream >> buffer;
		//ファイルから読み込んだ1行の文字列を区切り文字で分け、リストに追加
		std::vector<std::string> record;          //１行分の文字列のリスト
		std::istringstream streamBuffer(buffer);  //文字列ストリーム
		std::string token;						  //１セル分の文字列

		while (std::getline(streamBuffer,token,delimiter))
		{
			//1セル分の文字列をリストに追加する
			record.insert(record.begin(), token);
		}
		//1行分の文字列を出力引数のリストに追加する
		fileData.insert(fileData.begin(), record);
	}
	return true;
}

void CSVReader::clear()
{
	//ファイル内を空にする
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
