#include "GamePlay.h"

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

void GamePlay::initialize()
{
	charaManager->clear();
	isSceneEnd = false;   //�ŏ���false
	charaManager->add(new Player(Vector2(260, 500), charaManager));
	enemySpawn->initialize();
	charaManager->add(new Boss(Vector2(260, -1500), charaManager));
	//CWindow::getInstance().log("���Q�[���v���C�ɐ؂�ւ����");
}

void GamePlay::update(float deltaTime)
{
	charaManager->update(deltaTime);
	enemySpawn->spawn();
	enemySpawn->update(deltaTime);
	if (m_pInput->isKeyDown(KEYCORD::Z))
	{
		//charaManager->clear();
		isSceneEnd = true;    //Z�����ꂽ��V�[���I���i�������j
	}
	SetBackgroundColor(0, 0, 0);
}

void GamePlay::draw(Renderer* renderer, Renderer3D* renderer3D)
{
	charaManager->draw(renderer,renderer3D);
	renderer->drawText("Font", "HP", Vector2(0, 0), Vector2(0, 0), Vector2(1, 1), 0.0f, 255);
}

void GamePlay::shutdown()
{
}
//�V�[�����I����
bool GamePlay::isEnd()
{
	return isSceneEnd;
}
//���̃V�[���i�뎚�ɂ͋C���t����j
std::string GamePlay::nextScene()
{
	return "ending";
}
