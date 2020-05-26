#include "TestScene3D.h"
#include "../Actor/CharaManager/DeathPoint.h"
#include "../Actor/Player/Player.h"

//コンストラクタ
TestScene3D::TestScene3D(Input * input)
{
	charaManager = new CharactorManager();
	m_pInput = input;
	
}
//デスストラクタ
TestScene3D::~TestScene3D()
{
	delete charaManager;
	delete mapSpawn;
	delete camera;
}
//初期化
void TestScene3D::initialize()
{
	DeathPoint::getInstance().initialize();
	charaManager->clear();
	isSceneEnd = false;   //最初はfalse
	charaManager->add(new Player(Vector2(0.0f, -600.0f), charaManager));  //プレイヤー
	camera = new Camera();
	camera->initialize();
	camera->setPosition(Vector2(0.0f, -600.0f));
	mapSpawn = new MapSpawn(*charaManager,*camera);
	mapSpawn->loadMap("Resouce/Map/stage01.csv");
	backPos = -3000.0f;
	Sound::getInstance().playBGM("bgm");
	Score::getInstance().initialize();
	mGameOver = false;              //ゲームオーバー（player死んだとき）
	mGameClear = false;				//ゲームクリア  （boss死んだとき）
}
//更新
void TestScene3D::update(float deltaTime)
{
	//背景エンドレス
	if (backPos >= 0.0f)backPos = -3000.0f;
	backPos += 0.9f;

	if (charaManager->getIsBossEed()) mGameClear =  true;
	if (charaManager->getIsPlayerEed()) mGameOver = true;
	charaManager->update(deltaTime);
	camera->update(deltaTime);
}
//描画
void TestScene3D::draw(Renderer * renderer, Renderer3D * renderer3D)
{
	renderer->draw2D("back", Vector2(0, backPos), Vector2(0, 0), Vector2(600, 4110));
	charaManager->draw(renderer, renderer3D);
	//renderer->drawText("Font", "SCORE", Vector2(0.0f, 0.0f), Vector2(0, 0), Vector2(1, 1), 0.0f, 255);
	renderer->drawNumber("hpNumber"   , Vector2(550.0f, 0.0f), Score::getInstance().getScore(), 8, Vector2(0, 0), Vector2(1, 1), 0.0f, 255);
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
	//renderer3D->draw3DTexture("enemy", Vector3(camera->getPosition().x, camera->getPosition().y, 0.0f), Vector2(0.0f, 0.0f), Vector2(64.0f, 64.0f), 32.0f, 0.0f);
	//renderer3D->draw3DTexture("enemy", Vector3(camera->getPosition().x, DeathPoint::getInstance().getUp(), 0.0f), Vector2(0.0f, 0.0f), Vector2(64.0f, 64.0f), 32.0f, 0.0f);
	//renderer3D->draw3DTexture("enemy", Vector3(camera->getPosition().x, DeathPoint::getInstance().getDown(), 0.0f), Vector2(0.0f, 0.0f), Vector2(64.0f, 64.0f), 32.0f, 0.0f);
	//renderer3D->draw3DTexture("enemy", Vector3(DeathPoint::getInstance().getLeft(), camera->getPosition().y, 0.0f), Vector2(0.0f, 0.0f), Vector2(64.0f, 64.0f), 32.0f, 0.0f);
	//renderer3D->draw3DTexture("enemy", Vector3(DeathPoint::getInstance().getRight(), camera->getPosition().y, 0.0f), Vector2(0.0f, 0.0f), Vector2(64.0f, 64.0f), 32.0f, 0.0f);
}

//終了処理
void TestScene3D::shutdown()
{
}
//シーン終了
bool TestScene3D::isEnd()
{
	return isSceneEnd;
}
//次のシーン
std::string TestScene3D::nextScene()
{
	return "title";
}
