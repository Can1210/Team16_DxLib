#include "GameManager.h"
#include "GameTime.h"
#include "../Scene/SceneManager.h"
#include "../Scene/Title.h"
#include "../Scene/GamePlay.h"
#include "../Scene/Ending.h"
#include "../Scene/LoadScene.h"
#include "../Scene/TestScene3D.h"
#include "Score.h"
#include"../Device/Sound.h"

//コンストラクタ
GameManager::GameManager()
{
}

//デスストラクタ
GameManager::~GameManager()
{
	delete m_pRenderer;
	delete m_pRenderer3D;
}
//初期化
void GameManager::initialize(Input* input)
{
	m_pRenderer = new Renderer();
	m_pRenderer3D = new Renderer3D();
	sceneInitialize(input);             //シーン関係を初期化
	Score::createInstance();            //スコアの生成
	Score::getInstance().initialize();  //スコアの初期化
	Sound::createInstance();
	Sound::getInstance().volumeInitialize();
}
void GameManager::sceneInitialize(Input* input)
{
	//シーンマネージャーの初期化
	SceneManager::createInstance();  //シーンマネージャーの生成
	//シーンの追加
	SceneManager::getInstance().add("load", new LoadScene());
	SceneManager::getInstance().add("title", new Title(input));
	SceneManager::getInstance().add("gameplay", new GamePlay(input));
	SceneManager::getInstance().add("ending", new Ending(input));
	SceneManager::getInstance().add("test", new TestScene3D(input));
	SceneManager::getInstance().change("load");      //最初はタイトルに設定
}
//更新
void GameManager::update()
{
	//シーンマネージャーの更新処理
	SceneManager::getInstance().update(GameTime::getInstance().getDeltaTime());  //とりあえず更新
	SceneManager::getInstance().draw(m_pRenderer,m_pRenderer3D);
}
