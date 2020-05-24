#include "GamePlay.h"
#include"../GameBase/Score.h"
#include"../Device/Sound.h"
bool GamePlay::BossEnd;
bool GamePlay::PlayerEnd;
GamePlay::GamePlay(Input* input)
{
	charaManager = new CharactorManager();
	m_pInput = input;
	enemySpawn = new EnemySpawn(*charaManager);
}


GamePlay::~GamePlay()
{
	delete enemySpawn;
	delete charaManager;
	
}

void GamePlay::boss()
{
	charaManager->add(new Boss(Vector2(260, 0), charaManager));
}

void GamePlay::initialize()
{
	charaManager->clear();
	isSceneEnd = false;   //最初はfalse
	charaManager->add(new Player(Vector2(260, 500), charaManager));
	enemySpawn->initialize();
	bossFlag = FALSE;
	BossEnd = false;
	PlayerEnd = false;
	Sound::getInstance().playBGM("bgm");
	Score::getInstance().initialize();
	backPos = -3000.0f;
	//CWindow::getInstance().log("今ゲームプレイに切り替わった");
}

void GamePlay::update(float deltaTime)
{
	if (PlayerEnd)
	{
		Sound::getInstance().pauseBGM();
		isSceneEnd = true;
	}
	
	if (!BossEnd)//終了したら全部止める
	{
		charaManager->update(deltaTime);
		if (!bossFlag)
		{
			enemySpawn->spawn();
			enemySpawn->update(deltaTime);
		}
		
	}
	else
	{
		if (m_pInput->isKeyDown(KEYCORD::SPACE))
		{
			//charaManager->clear();
			Sound::getInstance().pauseBGM();
			isSceneEnd = true;    //Z押されたらシーン終了（今だけ）
		}
	}
	
	
	if (Score::getInstance().getScore() >= 15000&&bossFlag == FALSE)
	{
		bossFlag = TRUE;
		boss();
	}
	
	backPos += 0.9f;
	SetBackgroundColor(0, 0, 0);
	
}

void GamePlay::draw(Renderer* renderer, Renderer3D* renderer3D)
{
	
	
	renderer->draw2D("back", Vector2(0, backPos), Vector2(0, 0), Vector2(600, 4110));
	charaManager->draw(renderer,renderer3D);
	renderer->drawText("Font", "SCORE", Vector2(160, 0), Vector2(0, 0), Vector2(1, 1), 0.0f, 255);
	renderer->drawNumber("hpNumber", Vector2(500, 10), Score::getInstance().getScore(), 0, Vector2(0, 0), Vector2(1, 1), 0.0f, 255);
	renderer->drawText("Font", "HP", Vector2(0, 0), Vector2(0, 0), Vector2(1, 1), 0.0f, 255);
	if (BossEnd)
	{
		renderer->drawText("Font", "GAMECLEAR", Vector2(110, 500), Vector2(0, 0), Vector2(1, 1), 0.0f, 255);
		renderer->drawText("Font", "PUSH SPACE", Vector2(100, 650), Vector2(0, 0), Vector2(1, 1), 0.0f, 255);
	}
}

void GamePlay::shutdown()
{
}
//シーンを終える
bool GamePlay::isEnd()
{
	return isSceneEnd;
}
//次のシーン（誤字には気お付ける）
std::string GamePlay::nextScene()
{
	return "title";
}
