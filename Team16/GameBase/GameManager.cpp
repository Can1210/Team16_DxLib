#include "GameManager.h"
#include "GameTime.h"
#include "../Scene/SceneManager.h"
#include "../Scene/Title.h"
#include "../Scene/GamePlay.h"
#include "../Scene/Ending.h"
#include "../Scene/LoadScene.h"
//コンストラクタ
GameManager::GameManager()
{
}

//デスストラクタ
GameManager::~GameManager()
{
	delete m_pRenderer;
}
//初期化
void GameManager::initialize()
{
	m_pRenderer = new Renderer();
	sceneInitialize();   //シーン関係を初期化
}
void GameManager::sceneInitialize()
{
	//シーンマネージャーの初期化
	SceneManager::createInstance();  //シーンマネージャーの生成
	//シーンの追加
	SceneManager::getInstance().add("load", new LoadScene);
	SceneManager::getInstance().add("title", new Title);
	SceneManager::getInstance().add("gameplay", new GamePlay);
	SceneManager::getInstance().add("ending", new Ending);
	SceneManager::getInstance().change("load");      //最初はタイトルに設定
}
//更新
void GameManager::update()
{
	//シーンマネージャーの更新処理
	SceneManager::getInstance().update(GameTime::getInstance().getDeltaTime());  //とりあえず更新
	SceneManager::getInstance().draw(m_pRenderer);
}
