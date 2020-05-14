#include "GamePlay.h"
#include"../GameBase/Score.h"
#include"../Device/Sound.h"
bool GamePlay::BossEnd;
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
	//CWindow::getInstance().log("今ゲームプレイに切り替わった");
}

void GamePlay::update(float deltaTime)
{
	Sound::getInstance().playBGM("bgm");
	charaManager->update(deltaTime);
	if (!BossEnd)
	{
		enemySpawn->spawn();
		enemySpawn->update(deltaTime);
	}
	
	
	if (Score::getInstance().getScore() >= 1500&&bossFlag == FALSE)
	{
		bossFlag = TRUE;
		boss();
	}
	
	if (m_pInput->isKeyDown(KEYCORD::Z))
	{
		//charaManager->clear();
		isSceneEnd = true;    //Z押されたらシーン終了（今だけ）
	}
	SetBackgroundColor(0, 0, 0);
	
}

void GamePlay::draw(Renderer* renderer, Renderer3D* renderer3D)
{
	charaManager->draw(renderer,renderer3D);
	renderer->drawNumber("hpNumber", Vector2(400, 10), Score::getInstance().getScore(), 0, Vector2(0, 0), Vector2(1, 1), 0.0f, 255);
	renderer->drawText("Font", "HP", Vector2(0, 0), Vector2(0, 0), Vector2(1, 1), 0.0f, 255);
	if (BossEnd)
	{
		renderer->drawText("Font", "GAMECLEAR", Vector2(120, 500), Vector2(0, 0), Vector2(1, 1), 0.0f, 255);
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
	return "ending";
}
