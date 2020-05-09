#include "Ending.h"



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
	}
}

void Ending::draw(Renderer* renderer, Renderer3D* renderer3D)
{
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
