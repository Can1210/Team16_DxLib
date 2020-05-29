#include "Stage02.h"
#include "../Actor/CharaManager/DeathPoint.h"
#include"../Actor/Player/Player.h"
#include"../Device/Camera.h"

Stage02::Stage02(Input * input)
{
	m_pCharaManager = new CharactorManager();
	m_pInput = input;
}

Stage02::~Stage02()
{
	delete m_pCharaManager;
	delete m_pMapSpawn;
}

void Stage02::initialize()
{
	DeathPoint::getInstance().initialize();
	m_pCharaManager->clear();
	isSceneEnd = false;   //最初はfalse
	m_pCharaManager->add(new Player(Vector2(0.0f, -600.0f), m_pCharaManager));  //プレイヤー
	m_pMapSpawn = new MapSpawn(*m_pCharaManager);
	m_pMapSpawn->loadMap("Resouce/Map/stage02.csv");
	mBackPos = -3000.0f;
	Sound::getInstance().playBGM("bgm");
	Score::getInstance().initialize();
	Camera::getInstance().setPosition(Vector2(0.0f, -600.0f));
	Camera::getInstance().setStop(false);
	mGameOver = false;              //ゲームオーバー（player死んだとき）
	mGameClear = false;				//ゲームクリア  （boss死んだとき）
}

void Stage02::update(float deltaTime)
{
	//背景エンドレス
	if (mBackPos >= 0.0f)mBackPos = -3000.0f;
	mBackPos += 2.0f;

	if (m_pCharaManager->getIsBossEed()) mGameClear = true;
	if (m_pCharaManager->getIsPlayerEed()) mGameOver = true;

	m_pCharaManager->update(deltaTime);
	Camera::getInstance().update(deltaTime);
}

void Stage02::draw(Renderer * renderer, Renderer3D * renderer3D)
{
	renderer->draw2D("back", Vector2(0, mBackPos), Vector2(0, 0), Vector2(600, 4110));
	m_pCharaManager->draw(renderer, renderer3D);
	//renderer->drawText("Font", "SCORE", Vector2(0.0f, 0.0f), Vector2(0, 0), Vector2(1, 1), 0.0f, 255);
	renderer->drawNumber("hpNumber", Vector2(550.0f, 0.0f), Score::getInstance().getScore(), 8, Vector2(0, 0), Vector2(1, 1), 0.0f, 255);
	if (mGameClear)
	{
		renderer->drawText("Font", "GAMECLEAR", Vector2(110, 500), Vector2(0, 0), Vector2(1, 1), 0.0f, 255);
		renderer->drawText("Font", "PUSH SPACE", Vector2(100, 650), Vector2(0, 0), Vector2(1, 1), 0.0f, 255);
		if (m_pInput->isKeyDown(KEYCORD::SPACE))
		{
			Sound::getInstance().pauseBGM();
			isSceneEnd = true;
		}
	}
	if (mGameOver)
	{
		renderer->drawText("Font", "GAMEOVER", Vector2(100, 450), Vector2(0, 0), Vector2(1, 1), 0.0f, 255);
		renderer->drawText("Font", "PUSH SPACE", Vector2(100, 550), Vector2(0, 0), Vector2(1, 1), 0.0f, 255);

		if (m_pInput->isKeyDown(KEYCORD::SPACE))
		{
			Sound::getInstance().pauseBGM();
			isSceneEnd = true;
		}
	}
}

void Stage02::shutdown()
{
}

bool Stage02::isEnd()
{
	return isSceneEnd;
}

std::string Stage02::nextScene()
{
	return "title";
}
