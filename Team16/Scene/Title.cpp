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
	isReturn = false;
	alpha = 255;
	isAnim = false;
	animAlpha = 255;
}
//更新
void Title::update(float deltaTime)
{
	if (m_pInput->isKeyDown(KEYCORD::SPACE))// || m_pInput->isGamePadBottonDown(GAMEPAD_KEYCORD::BUTTON_A,0))
	{
		Sound::getInstance().playSE("click01");
		//isAnim = true;
		isSceneEnd = true;    //Z押されたらシーン終了（今だけ）
	}

	if (m_pInput->isKeyDown(KEYCORD::Z))// || m_pInput->isGamePadBottonDown(GAMEPAD_KEYCORD::BUTTON_A,0))
	{
		Sound::getInstance().playSE("click01");
		mSelectName = "stage2";
		//isAnim = true;
		isSceneEnd = true;    //Z押されたらシーン終了（今だけ）
	}

	if (isReturn)
	{
		alpha += 5;
		if (alpha >= 255)
		{
			alpha = 255;
			isReturn = false;
		}
	}
	else
	{
		alpha -= 5;
		if (alpha <= 30)
		{
			alpha = 30;
			isReturn = true;
		}
	}

	if (isAnim)
	{
		animAlpha -= 5;
		if (animAlpha <= 0)
		{
			isSceneEnd = true;
		}
	}


	
}
//描画
void Title::draw(Renderer* renderer, Renderer3D* renderer3D)
{
	if (isAnim)
	{
		renderer->draw2D("title", Vector2(0, 0), Vector2(0, 0), Vector2(600, 900), Vector2(300, 450), Vector2(1.0f, 1.0f), 0, animAlpha);
		renderer->draw2D("titleText", Vector2(0, 700), Vector2(0, 0), Vector2(600, 70), Vector2(300, 70), Vector2(1.0f, 1.0f), 0, animAlpha);
	}
	else
	{
		renderer->draw2D("title", Vector2(0, 0), Vector2(0, 0), Vector2(600, 900), Vector2(300, 450), Vector2(1.0f, 1.0f), 0, 255);
		renderer->draw2D("titleText", Vector2(0, 700), Vector2(0, 0), Vector2(600, 70), Vector2(300, 70), Vector2(1.0f, 1.0f), 0, alpha);
	}
	/*if (!mIsStageSelect)
	{
		renderer->drawText("Font", "TITLE", Vector2(180, 250), Vector2(0, 0), Vector2(1, 1), 0.0f, 255);
		renderer->drawText("Font", "PUSH SPACE", Vector2(100, 300), Vector2(0, 0), Vector2(1, 1), 0.0f, 255);
		renderer->draw2D("sousa", Vector2(100, 400), Vector2(0, 0), Vector2(400, 300));
	}
	else
	{
		renderer->drawText("Font", "STAGE SELECT", Vector2(40.0f, 0.0f), Vector2(0, 0), Vector2(1, 1), 0.0f, 255);
	}*/
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

