#include "Stage01.h"
#include "../Actor/CharaManager/DeathPoint.h"
#include "../Actor/Player/Player.h"

#include"../Device/Camera.h"


Stage01::Stage01()
{
	m_pCharaManager = new CharactorManager();
}

Stage01::~Stage01()
{
	delete m_pCharaManager;
	delete m_pMapSpawn;
}

void Stage01::initialize()
{
	DeathPoint::getInstance().initialize();
	m_pCharaManager->clear();
	isSceneEnd = false;   //最初はfalse
	m_pCharaManager->add(new Player(Vector2(0.0f, -600.0f), m_pCharaManager));  //プレイヤー
	Camera::getInstance().setPosition(Vector2(0.0f, -600.0f));
	Camera::getInstance().setStop(false);
	m_pMapSpawn = new MapSpawn(*m_pCharaManager);
	m_pMapSpawn->loadMap("Resouce/Map/stage01.csv");
	mBackPos = -3000.0f;
	Sound::getInstance().playBGM("bgm");
	Score::getInstance().initialize();
	mGameOver = false;              //ゲームオーバー（player死んだとき）
	mGameClear = false;				//ゲームクリア  （boss死んだとき）
	nextSceneName = "stage2";       //最初はステージ2
	sceneNum = 0;
	fadetype = FadeType::FadeStart;
	fadeCount = 0.0f;
}

void Stage01::update(float deltaTime)
{
	switch (fadetype)
	{
	case FadeStart:
		if (fadeCount > fadeEndTime) {
			fadetype = FadeStop;
			fadeCount = 0.0f;
		}
		else {
			fadeCount += deltaTime;
		}
		break;
	case FadeEnd:
		if (fadeCount > fadeEndTime) {
			Sound::getInstance().pauseBGM();
			isSceneEnd = true;
		}
		else {
			fadeCount += deltaTime;
		}
		break;
	}

	//背景エンドレス
	if (mBackPos >= 0.0f)mBackPos = -3000.0f;
	mBackPos += 0.9f;

	if (m_pCharaManager->getIsBossEed()) {
		mGameClear = true;
		nextSceneName = "stage2";
		if (Input::getInstance().isKeyDown(KEYCORD::SPACE) || Input::getInstance().isGamePadBottonDown(GAMEPAD_KEYCORD::BUTTON_A, 0))
		{
			fadetype = FadeEnd;
		}

	};
	if (m_pCharaManager->getIsPlayerEed()) {
		mGameOver = true;
		nextSceneName = "title";

		if (Input::getInstance().isKeyDown(KEYCORD::SPACE) || Input::getInstance().isGamePadBottonDown(GAMEPAD_KEYCORD::BUTTON_A, 0))
		{
			fadetype = FadeEnd;
		}
	};

	m_pCharaManager->update(deltaTime);
	Camera::getInstance().update(deltaTime);
}

void Stage01::draw(Renderer * renderer, Renderer3D * renderer3D)
{
	renderer->draw2D("back", Vector2(0, mBackPos), Vector2(0, 0), Vector2(600, 4110));                                   //背景
	m_pCharaManager->draw(renderer, renderer3D);
	renderer->draw2D("UI", Vector2(0, -50), Vector2(0, 0), Vector2(600, 200), Vector2(300, 100), Vector2(1.0f, 0.5f));	 //UI板
	//プレイヤーにあったUI関連
	renderer->draw2D("player", Vector2(10.0f, 28.0f), Vector2(0.0f, 0.0f), Vector2(64.0f, 64.0f), true, false);          //プレイヤーの実機絵
	renderer->drawText("Font_green", "x", Vector2(40.0f, -15.0f), Vector2(0, 0), Vector2(0.5f, 1), 0.0f, 255);            //X
	renderer->drawNumber("hpNumber", Vector2(130.0f, 10.0f), m_pCharaManager->getHp(), 0, Vector2(0.0f, 0.0f), Vector2(1.0f, 1.0f), 0.0f, 255);   //プレイヤーのHP
	renderer->draw2D(m_pCharaManager->getSub1(), Vector2(220.0f, 20.0f), Vector2(0.0f, 0.0f), Vector2(64.0f, 64.0f), Vector2(32.0f, 32.0f), Vector2(1.0f, 1.0f), 0, 255);	 //プレイヤーのアイテム1
	renderer->draw2D(m_pCharaManager->getSub2(), Vector2(290.0f, 20.0f), Vector2(0.0f, 0.0f), Vector2(64.0f, 64.0f), Vector2(32.0f, 32.0f), Vector2(1.0f, 1.0f), 0, 255);	 //プレイヤーのアイテム2
	renderer->drawText("Font_green", "Score", Vector2(355.0f, -15.0f), Vector2(0, 0), Vector2(0.4f, 0.5f), 0.0f, 255);    //スコア表示文字
	renderer->drawNumber("hpNumber", Vector2(570.0f, 30.0f), Score::getInstance().getScore(), 8, Vector2(0, 0), Vector2(1, 1), 0.0f, 255);

	if (mGameClear)
	{
		renderer->drawText("Font_green", "GAMECLEAR", Vector2(100, 450), Vector2(0, 0), Vector2(0.5f, 1), 0.0f, 255);
		renderer->drawText("Font_green", "PUSH Z", Vector2(120, 550), Vector2(0, 0), Vector2(0.5f, 1), 0.0f, 255);
		//if (Input::getInstance().isKeyDown(KEYCORD::Z))// || m_pInput->isGamePadBottonDown(GAMEPAD_KEYCORD::BUTTON_A, 0))
		//{
		//	Sound::getInstance().pauseBGM();
		//	nextSceneName = "stage2";
		//	isSceneEnd = true;
		//}
	}
	if (mGameOver)
	{
		renderer->drawText("Font_green", "GAMEOVER", Vector2(100, 450), Vector2(0, 0), Vector2(0.5f, 1), 0.0f, 255);
		renderer->drawText("Font_green", "PUSH Z", Vector2(120, 550), Vector2(0, 0), Vector2(0.5f, 1), 0.0f, 255);

		//if (Input::getInstance().isKeyDown(KEYCORD::Z))// || m_pInput->isGamePadBottonDown(GAMEPAD_KEYCORD::BUTTON_A, 0))
		//{
		//	Sound::getInstance().pauseBGM();
		//	nextSceneName = "title";
		//	isSceneEnd = true;
		//}
	}

	switch (fadetype)
	{
	case FadeStart:
		renderer->draw2D("player", Vector2(300.0f, 1000.0f / fadeEndTime * fadeCount), Vector2(0, 0), Vector2(64, 64), Vector2(32, 32), Vector2(3.0f, 3.0f), 0, 255);
		break;
	case FadeEnd:
		renderer->draw2D("player", Vector2(300.0f, 1000.0f - 1000.0f / fadeEndTime * fadeCount), Vector2(0, 0), Vector2(64, 64), Vector2(32, 32), Vector2(3.0f, 3.0f), 0, 255);
		break;
	}
}

void Stage01::shutdown()
{
}

bool Stage01::isEnd()
{
	return isSceneEnd;
}

std::string Stage01::nextScene()
{
	return nextSceneName;
}

void Stage01::choiceScene()
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
