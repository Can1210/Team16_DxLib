#include "TextureLoad.h"
#include "../../Support/CWindow.h"

//コンストラクタ
TextureLoad::TextureLoad()
{
}

//デスストラクタ
TextureLoad::~TextureLoad()
{
	storageTexturesMap.clear();  //終了時に空にする
	callTextureMap.clear();		 //終了時に空にする
}
//テクスチャの追加
void TextureLoad::add(std::string callName, const TCHAR* textureName)
{
	if (!(storageTexturesMap.size() == 0))
	{
		auto result = storageTexturesMap.find(textureName);
		if (result != storageTexturesMap.end()) return;
	}
	////追加
	storageTexturesMap.emplace(textureName, callName);      //引数情報を追加
	int gra = LoadGraph(textureName);                       //テクスチャをロードする
	callTextureMap.emplace(callName, gra);                  //作った番号と呼び出し名を追加
}
//テクスチャを呼ぶ
int TextureLoad::set(std::string callName)
{
	return callTextureMap.at(callName);
}
