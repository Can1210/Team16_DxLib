#include "Ending.h"
#include "../GameBase/Score.h"
#include"../Device/Sound.h"


Ending::Ending()
{
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
	if (Input::getInstance().isKeyDown(KEYCORD::Z))
	{
		isSceneEnd = true;    //Z�����ꂽ��V�[���I���i�������j
		Score::getInstance().initialize();
	}
}

void Ending::draw(Renderer* renderer, Renderer3D* renderer3D)
{
	renderer->drawText("Font_green", "ENDING", Vector2(110, 500), Vector2(0, 0), Vector2(1, 1), 0.0f, 255);
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
