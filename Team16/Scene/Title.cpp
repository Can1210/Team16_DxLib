#include "Title.h"
#include "../Actor/CharaManager/DeathPoint.h"
#include "../Actor/Player/Player.h"
#include "../Actor/Enemies/SelectEnemy.h"

bool Title::mChangeScne;
int  Title::mStageNum;

//コンストラクタ
Title::Title(Input* input)
{
	m_pInput = input;     //メインで使っているものをもらう
}

//デスストラクタ
Title::~Title()
{
	delete m_pCharaManager;
	delete m_pCamera;
}
//初期化
void Title::initialize()
{
	isSceneEnd = false;       //最初はfalse
	mIsStageSelect = false;   //ステージ選択をするかどうか
	mStageNum = 1;
	mChangeScne = false;
	mSelectName = "stage1";   //仮置き
	CWindow::getInstance().log("今タイトルに切り替わった\n");
	m_pCharaManager = new CharactorManager();
	m_pCharaManager->clear();
	m_pCamera = new Camera();
	m_pCamera->initialize();
	m_pCamera->setPosition(Vector2(0.0f, -600.0f));


}
//更新
void Title::update(float deltaTime)
{
	stageSelect(deltaTime);
	if (mIsStageSelect) return;
	if (m_pInput->isKeyDown(KEYCORD::SPACE) || m_pInput->isGamePadBottonDown(GAMEPAD_KEYCORD::BUTTON_A,0))
	{
		Sound::getInstance().playSE("click01");
		mIsStageSelect = true;

		m_pCharaManager->add(new Player(Vector2(0.0f, -800.0f), m_pCharaManager));  //プレイヤー
		m_pCharaManager->add(new SelectEnemy(Vector2( 100.0f, -300.0f), m_pCharaManager, 1));
		m_pCharaManager->add(new SelectEnemy(Vector2(-100.0f, -300.0f), m_pCharaManager, 2));
		//isSceneEnd = true;    //Z押されたらシーン終了（今だけ）
	}
}
//描画
void Title::draw(Renderer* renderer, Renderer3D* renderer3D)
{
	if (!mIsStageSelect)
	{
		renderer->drawText("Font", "TITLE", Vector2(180, 250), Vector2(0, 0), Vector2(1, 1), 0.0f, 255);
		renderer->drawText("Font", "PUSH SPACE", Vector2(100, 300), Vector2(0, 0), Vector2(1, 1), 0.0f, 255);
		renderer->draw2D("sousa", Vector2(100, 400), Vector2(0, 0), Vector2(400, 300));
	}
	else
	{
		renderer->drawText("Font", "STAGE SELECT", Vector2(40.0f, 0.0f), Vector2(0, 0), Vector2(1, 1), 0.0f, 255);
		renderer->drawText("Font", "1", Vector2(190, 100), Vector2(0, 0), Vector2(1, 1), 0.0f, 255);
		renderer->drawText("Font", "2", Vector2(360, 100), Vector2(0, 0), Vector2(1, 1), 0.0f, 255);
		m_pCharaManager->draw(renderer, renderer3D);
	}
}
//終了処理
void Title::shutdown()
{
}
//シーンが終わったかどうか
bool Title::isEnd()
{
	return isSceneEnd;
}
//次のシーン
std::string Title::nextScene()
{
	return  mSelectName;  //"test";  //
}
void Title::choiceScene(int num)
{
	mChangeScne = true;
	mStageNum = num;
}
//セレクト時の処理
void Title::stageSelect(float deltaTime)
{
	if (!mIsStageSelect) return;
	m_pCharaManager->update(deltaTime);
	m_pCamera->update(deltaTime);

	if (mChangeScne)
	{
		switch (mStageNum)
		{
		case 1:
			mSelectName = "stage1";
			isSceneEnd = true;
			break;
		case 2:
			mSelectName = "stage2";
			isSceneEnd = true;
			break;
		default:
			break;
		}
	}
}

