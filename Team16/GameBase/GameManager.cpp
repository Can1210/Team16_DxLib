#include "GameManager.h"
#include "GameTime.h"
#include "Score.h"
#include "../Actor/CharaManager/DeathPoint.h"
#include "../Device/Sound.h"
#include "../Device/Camera.h"
#include "../Scene/SceneManager.h"
#include "../Scene/Title.h"
#include "../Scene/GamePlay.h"
#include "../Scene/Ending.h"
#include "../Scene/LoadScene.h"
#include "../Scene/TestScene3D.h"
#include "../Scene/Stage01.h"
#include "../Scene/Stage02.h"

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
void GameManager::initialize()
{
	m_pRenderer = new Renderer();
	m_pRenderer3D = new Renderer3D();
	sceneInitialize();             //シーン関係を初期化
	Score::createInstance();            //スコアの生成
	Score::getInstance().initialize();  //スコアの初期化
	Sound::createInstance();
	Sound::getInstance().volumeInitialize();
	DeathPoint::createInstance();
	DeathPoint::getInstance().initialize();
	Camera::createInstance();
	Camera::getInstance().initialize();


}
void GameManager::sceneInitialize()
{
	//シーンマネージャーの初期化
	SceneManager::createInstance();  //シーンマネージャーの生成
	//シーンの追加
	SceneManager::getInstance().add("load", new LoadScene());
	SceneManager::getInstance().add("title", new Title());
	SceneManager::getInstance().add("gameplay", new GamePlay());
	SceneManager::getInstance().add("ending", new Ending());
	SceneManager::getInstance().add("test", new TestScene3D());
	SceneManager::getInstance().add("stage1", new Stage01());
	SceneManager::getInstance().add("stage2", new Stage02());
	SceneManager::getInstance().change("load");      //最初はタイトルに設定

}
//更新
void GameManager::update()
{
	//シーンマネージャーの更新処理
	SceneManager::getInstance().update(GameTime::getInstance().getDeltaTime());  //とりあえず更新
	SceneManager::getInstance().draw(m_pRenderer,m_pRenderer3D);
}
