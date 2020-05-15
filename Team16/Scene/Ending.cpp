#include "Ending.h"
#include "../GameBase/Score.h"
#include"../Device/Sound.h"


Ending::Ending(Input* input)
{
	m_pInput = input;
}


Ending::~Ending()
{
}

void Ending::initialize()
{

	isSceneEnd = false;       //最初はfalse
	CWindow::getInstance().log("今エンディングに切り替わった\n");
}

void Ending::update(float deltaTime)
{
	if (m_pInput->isKeyDown(KEYCORD::Z))
	{
		isSceneEnd = true;    //Z押されたらシーン終了（今だけ）
		Score::getInstance().initialize();
	}
}

void Ending::draw(Renderer* renderer, Renderer3D* renderer3D)
{
	renderer->drawText("Font", "ENDING", Vector2(110, 500), Vector2(0, 0), Vector2(1, 1), 0.0f, 255);
}

void Ending::shutdown()
{
}

bool Ending::isEnd()
{
	return isSceneEnd;
}

std::string Ending::nextScene()
{
	return "title";
}
