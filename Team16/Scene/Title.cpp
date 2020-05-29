#include "Title.h"
#include "../Device/Camera.h"


//コンストラクタ
Title::Title(Input* input)
{
	m_pInput = input;     //メインで使っているものをもらう
}

//デスストラクタ
Title::~Title()
{
}
//初期化
void Title::initialize()
{
	isSceneEnd = false;       //最初はfalse
	mIsStageSelect = false;   //ステージ選択をするかどうか
	mSelectName = "stage1";   //仮置き
	CWindow::getInstance().log("今タイトルに切り替わった\n");

}
//更新
void Title::update(float deltaTime)
{
	if (m_pInput->isKeyDown(KEYCORD::SPACE))// || m_pInput->isGamePadBottonDown(GAMEPAD_KEYCORD::BUTTON_A,0))
	{
		Sound::getInstance().playSE("click01");

		isSceneEnd = true;    //Z押されたらシーン終了（今だけ）
	}

	if (m_pInput->isKeyDown(KEYCORD::Z))// || m_pInput->isGamePadBottonDown(GAMEPAD_KEYCORD::BUTTON_A,0))
	{
		Sound::getInstance().playSE("click01");
		mSelectName = "stage2";

		isSceneEnd = true;    //Z押されたらシーン終了（今だけ）
	}

	//stageSelect(deltaTime);
	//if (mIsStageSelect) return;
	
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
//セレクト時の処理
void Title::stageSelect(float deltaTime)
{
	if (!mIsStageSelect) return;

	/*if (mChangeScne)
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
	}*/
}

