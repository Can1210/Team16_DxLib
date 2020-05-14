#include "Title.h"
#include"../Device/Sound.h"

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
	CWindow::getInstance().log("今タイトルに切り替わった\n");
}
//更新
void Title::update(float deltaTime)
{
	if (m_pInput->isKeyDown(KEYCORD::Z))
	{
		Sound::getInstance().playSE("click01");
		isSceneEnd = true;    //Z押されたらシーン終了（今だけ）
	}

}
//描画
void Title::draw(Renderer* renderer, Renderer3D* renderer3D)
{
	renderer->drawText("Font", "TITLE", Vector2(180, 450), Vector2(0, 0), Vector2(1, 1), 0.0f, 255);
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
	return "gameplay";
}
