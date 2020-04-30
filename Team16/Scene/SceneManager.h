#pragma once
#ifndef _SCENEMANAGER_H_
#define _SCENEMANAGER_H_

#include <iostream>
#include <string>
#include <unordered_map>
#include "BaseScene.h"
#include "../Support/Singleton.h"


//シーン管理
class SceneManager :public Singleton<SceneManager>
{
	//コンストラクタ
	SceneManager();
	//デスストラクタ
	virtual ~SceneManager();
public:
	friend class Singleton<SceneManager>;                  //Singletonでのインスタンス作成は許可

	//シーンの追加
	void add(std::string name, BaseScene* addScene);
	//シーンの切り替え
	void change(std::string name);
	//更新
	void update(float deltaTime);
	//描画
	void draw(Renderer* renderer);
private:
	std::unordered_map <std::string, BaseScene*> scenes;     //シーンを格納
	BaseScene* currentScene;                                //現在のシーン

};
#endif // !_SCENEMANAGER_H

