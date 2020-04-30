#pragma once
#ifndef _TEXTURELOAD_H_
#define _TEXTURELOAD_H_
#include <DxLib.h>
#include <string>
#include<unordered_map>
#include "../../Support/Singleton.h"

//テクスチャを読み込み管理する   シングルトン
class TextureLoad : public Singleton<TextureLoad>
{
protected:
	TextureLoad();
	virtual ~TextureLoad();

public:
	friend class Singleton<TextureLoad>;       //Singletonでのインスタンス作成は許可
	//テクスチャの追加　（扱いたい名前 , テクスチャの名前（パスも含める））
	void add(std::string callName, const TCHAR* textureName);
	//テクスチャの呼び出し　（登録してある扱いたい名前）
	int set(std::string callName);

private:
	std::unordered_map<const TCHAR*, std::string> storageTexturesMap;  //テクスチャ格納用
	std::unordered_map<std::string, int> callTextureMap;               //テクスチャ呼び出し用
};

#endif // ! _TEXTURELOAD_H_

