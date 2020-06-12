#include "Title.h"
#include "../Device/Camera.h"
#include "../GameBase/WindowInfo.h"


//コンストラクタ
Title::Title()
{
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
	fadetype = FadeType::FadeStop;
	fadeCount = 0.0f;
}
//更新
void Title::update(float deltaTime)
{
	switch (fadetype)
	{
	case FadeStart:
		if (fadeCount > fadeEndTime){
			fadetype = FadeStop;
			fadeCount = 0.0f;
		}
		else {
			fadeCount += deltaTime;
			return;
		}
		break;
	case FadeEnd:
		if (fadeCount > fadeEndTime) {
			isSceneEnd = true;    //Z押されたらシーン終了（今だけ）
			fadeCount = 0.0f;
		}
		else {
			fadeCount += deltaTime;
			return;
		}
		break;
	}

	if (Input::getInstance().isKeyDown(KEYCORD::SPACE))// || m_pInput->isGamePadBottonDown(GAMEPAD_KEYCORD::BUTTON_A,0))
	{
		Sound::getInstance().playSE("click01");
		mSelectName = "stage1";
		isAnim = true;
		fadetype = FadeEnd;
		//isSceneEnd = true;    //Z押されたらシーン終了（今だけ）
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
		renderer->draw2D("title", Vector2(0, -50), Vector2(0, 0), Vector2(600, 1000), Vector2(300, 450), Vector2(1.0f, 1.0f), 0, animAlpha);
		renderer->draw2D("titleText", Vector2(0, 850), Vector2(0, 0), Vector2(600, 70), Vector2(300, 70), Vector2(1.0f, 1.0f), 0, animAlpha);
	}
	else
	{
		renderer->draw2D("title", Vector2(0, -50), Vector2(0, 0), Vector2(600, 1000), Vector2(300, 450), Vector2(1.0f, 1.0f), 0, 255);
		renderer->draw2D("titleText", Vector2(0, 850), Vector2(0, 0), Vector2(600, 70), Vector2(300, 70), Vector2(1.0f, 1.0f), 0, alpha);
	}
	switch (fadetype)
	{
	case FadeStart:
		renderer->draw2D("fade", Vector2(0.0f, 1000.0f / fadeEndTime * fadeCount), Vector2(0, 0), Vector2(600, 1000), Vector2(300, 500), Vector2(1.0f, 1.0f), 0, 255);
		break;
	case FadeEnd:
		renderer->draw2D("fade", Vector2(0.0f, 900.0f - 1000.0f / fadeEndTime * fadeCount), Vector2(0, 0), Vector2(600, 1000), Vector2(300, 500), Vector2(1.0f, 1.0f), 0, 255);
		break;
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

