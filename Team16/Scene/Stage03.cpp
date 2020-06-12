#include "Stage03.h"
#include "../Actor/CharaManager/DeathPoint.h"
#include"../Actor/Player/Player.h"
#include"../Device/Camera.h"

Stage03::Stage03()
{
	m_pCharaManager = new CharactorManager();
}

Stage03::~Stage03()
{
	delete m_pCharaManager;
	delete m_pMapSpawn;
}

void Stage03::initialize()
{
	DeathPoint::getInstance().initialize();
	m_pCharaManager->clear();
	isSceneEnd = false;   //最初はfalse
	m_pCharaManager->add(new Player(Vector2(0.0f, -600.0f), m_pCharaManager));  //プレイヤー
	m_pMapSpawn = new MapSpawn(*m_pCharaManager);
	m_pMapSpawn->loadMap("Resouce/Map/stage03.csv");
	mBackPos = -3000.0f;
	Sound::getInstance().playBGM("bgm");
	Score::getInstance().initialize();
	Camera::getInstance().setPosition(Vector2(0.0f, -600.0f));
	Camera::getInstance().setStop(false);
	mGameOver = false;              //ゲームオーバー（player死んだとき）
	mGameClear = false;				//ゲームクリア  （boss死んだとき）
}

void Stage03::update(float deltaTime)
{
	//背景エンドレス
	if (mBackPos >= 0.0f)mBackPos = -3000.0f;
	mBackPos += 0.9f;

	if (m_pCharaManager->getIsBossEed()) mGameClear = true;
	if (m_pCharaManager->getIsPlayerEed()) mGameOver = true;

	m_pCharaManager->update(deltaTime);
	Camera::getInstance().update(deltaTime);
}

void Stage03::draw(Renderer * renderer, Renderer3D * renderer3D)
{
	renderer->draw2D("back2", Vector2(0, mBackPos), Vector2(0, 0), Vector2(600, 4110));
	m_pCharaManager->draw(renderer, renderer3D);
	renderer->draw2D("UI", Vector2(0, -50), Vector2(0, 0), Vector2(600, 200), Vector2(300, 100), Vector2(1.0f, 0.5f));	 //UI板
	//プレイヤーにあったUI関連
	renderer->draw2D("player", Vector2(10.0f, 28.0f), Vector2(0.0f, 0.0f), Vector2(64.0f, 64.0f), true, false);          //プレイヤーの実機絵
	renderer->drawText("Font_green", "x", Vector2(40.0f, -15.0f), Vector2(0, 0), Vector2(0.5f, 1), 0.0f, 255);            //X
	renderer->drawNumber("hpNumber", Vector2(130.0f, 10.0f), m_pCharaManager->getHp(), 0, Vector2(0.0f, 0.0f), Vector2(1.0f, 1.0f), 0.0f, 255);   //プレイヤーのHP
	renderer->draw2D(m_pCharaManager->getSub1(), Vector2(220.0f, 20.0f), Vector2(0.0f, 0.0f), Vector2(64.0f, 64.0f), Vector2(32.0f, 32.0f), Vector2(1.0f, 1.0f), 0, 255);	 //プレイヤーのアイテム1
	renderer->draw2D(m_pCharaManager->getSub2(), Vector2(290.0f, 20.0f), Vector2(0.0f, 0.0f), Vector2(64.0f, 64.0f), Vector2(32.0f, 32.0f), Vector2(1.0f, 1.0f), 0, 255);	 //プレイヤーのアイテム2
	renderer->drawNumber("hpNumber", Vector2(550.0f, 10.0f), Score::getInstance().getScore(), 8, Vector2(0, 0), Vector2(1, 1), 0.0f, 255);

	if (mGameClear)
	{
		renderer->drawText("Font_green", "GAMECLEAR", Vector2(100, 450), Vector2(0, 0), Vector2(0.5f, 1), 0.0f, 255);
		renderer->drawText("Font_green", "PUSH Z", Vector2(120, 550), Vector2(0, 0), Vector2(0.5f, 1), 0.0f, 255);
		if (Input::getInstance().isKeyDown(KEYCORD::Z))
		{
			Sound::getInstance().pauseBGM();
			nextSceneName = "title";
			isSceneEnd = true;
		}
	}
	if (mGameOver)
	{
		renderer->drawText("Font_green", "GAMEOVER", Vector2(100, 450), Vector2(0, 0), Vector2(0.5f, 1), 0.0f, 255);
		renderer->drawText("Font_green", "PUSH Z", Vector2(120, 550), Vector2(0, 0), Vector2(0.5f, 1), 0.0f, 255);

		if (Input::getInstance().isKeyDown(KEYCORD::Z))
		{
			Sound::getInstance().pauseBGM();
			nextSceneName = "stage3";
			isSceneEnd = true;
		}
	}
}

void Stage03::shutdown()
{
}

bool Stage03::isEnd()
{
	return isSceneEnd;
}

std::string Stage03::nextScene()
{
	return nextSceneName;
}

void Stage03::choiceScene()
{
	switch (sceneNum)
	{
	case 0:
		nextSceneName = "title";
		break;
	case 1:
		nextSceneName = "stage1";
		break;
	case 2:
		nextSceneName = "stage2";
		break;
	default:
		break;
	}

	if (Input::getInstance().isKeyDown(KEYCORD::ARROW_LEFT)) sceneNum--;
	if (Input::getInstance().isKeyDown(KEYCORD::ARROW_RIGHT)) sceneNum++;

	if (sceneNum <= 0)sceneNum = 0;
	if (sceneNum >= 2)sceneNum = 2;
}
