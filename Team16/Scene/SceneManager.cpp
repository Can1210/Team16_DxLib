#include "SceneManager.h"


//コンストラクタ  初期化並び
SceneManager::SceneManager() :
	currentScene(nullptr)
{
}

//デスストラクタ
SceneManager::~SceneManager()
{
	//シーンの削除
	for (auto scene : scenes)
	{
		delete scene.second;
	}
}
//シーンの追加
void SceneManager::add(std::string name, BaseScene * addScene)
{
	//すでにシーンが登録されていたら何もしない
	if (!(scenes.size() == 0))
	{
		auto result = scenes.find(name);
		if (result != scenes.end()) return;
	}
	//シーンの追加
	scenes.emplace(name, addScene);

}
//シーンの切り替え
void SceneManager::change(std::string name)
{
	//現在のシーンがNULLだったら終了処理を行う
	if (currentScene != nullptr)
	{
		currentScene->shutdown();
	}
	currentScene = scenes[name];     //シーンを切り替える
	currentScene->initialize();      //シーンを初期化
}
//更新
void SceneManager::update(float deltaTime)
{
	if (currentScene == nullptr) return;   //現在のシーンがなければ早期リターン
	currentScene->update(deltaTime);       //現在のシーンを更新
	if (currentScene->isEnd())             //終了したら次のシーンに切り替える
	{
		change(currentScene->nextScene());
	}
}

void SceneManager::draw(Renderer* renderer, Renderer3D* renderer3D)
{
	if (currentScene == nullptr) return;   //現在のシーンがなければ早期リターン
	currentScene->draw(renderer, renderer3D);          //現在のシーンを描画

}
