#pragma once
#ifndef _CSVREADER_H_
#define _CSVREADER_H_
#include <vector>
#include <string>

//CSV読み込むクラス
class CSVReader
{
public:
	CSVReader();
	~CSVReader();
	//CSVファイルを読み込む
	bool read(std::string& fileName);
	//クリア
	void clear();
	//読み込んだデータを渡す
	std::vector<std::vector<std::string>> getData();
private:
	std::vector<std::vector<std::string>> fileData;   //SCVファイルデータ
};


#endif // !_CSVREADER_H_