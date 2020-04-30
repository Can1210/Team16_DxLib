#include "Ending.h"



Ending::Ending()
{
}


Ending::~Ending()
{
}

void Ending::initialize()
{
	m_pInput = new Input;
	m_pInput->init();            //input初期化
	isSceneEnd = false;       //最初はfalse
	CWindow::getInstance().log("今エンディングに切り替わった");
}

void Ending::update(float deltaTime)
{
	m_pInput->update();         //input更新
	if (m_pInput->isKeyDown(KEYCORD::Z))
	{
		isSceneEnd = true;    //Z押されたらシーン終了（今だけ）
	}
}

void Ending::draw(Renderer* renderer)
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
