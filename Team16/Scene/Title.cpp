#include "Title.h"
#include "../Device/Camera.h"
#include "../GameBase/WindowInfo.h"


//�R���X�g���N�^
Title::Title()
{
}

//�f�X�X�g���N�^
Title::~Title()
{
}
//������
void Title::initialize()
{
	isSceneEnd = false;       //�ŏ���false
	mIsStageSelect = false;   //�X�e�[�W�I�������邩�ǂ���
	mSelectName = "stage1";   //���u��
	CWindow::getInstance().log("���^�C�g���ɐ؂�ւ����\n");
	isReturn = false;
	alpha = 255;
	isAnim = false;
	animAlpha = 255;
	fadetype = FadeType::FadeStop;
	fadeCount = 0.0f;
}
//�X�V
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
			isSceneEnd = true;    //Z�����ꂽ��V�[���I���i�������j
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
		//isSceneEnd = true;    //Z�����ꂽ��V�[���I���i�������j
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
//�`��
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
//�I������
void Title::shutdown()
{
}
//�V�[�����I��������ǂ���
bool Title::isEnd()
{
	return isSceneEnd;
}
//���̃V�[��
std::string Title::nextScene()
{
	return  mSelectName;  //"test";  //
}

