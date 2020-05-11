#include "Ending.h"
#include "../GameBase/Score.h"


Ending::Ending(Input* input)
{
	m_pInput = input;
}


Ending::~Ending()
{
}

void Ending::initialize()
{
	isSceneEnd = false;       //�ŏ���false
	CWindow::getInstance().log("���G���f�B���O�ɐ؂�ւ����\n");
}

void Ending::update(float deltaTime)
{
	if (m_pInput->isKeyDown(KEYCORD::Z))
	{
		isSceneEnd = true;    //Z�����ꂽ��V�[���I���i�������j
		Score::getInstance().initialize();
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
