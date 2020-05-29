#include "Title.h"
#include "../Device/Camera.h"


//�R���X�g���N�^
Title::Title(Input* input)
{
	m_pInput = input;     //���C���Ŏg���Ă�����̂����炤
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

}
//�X�V
void Title::update(float deltaTime)
{
	if (m_pInput->isKeyDown(KEYCORD::SPACE))// || m_pInput->isGamePadBottonDown(GAMEPAD_KEYCORD::BUTTON_A,0))
	{
		Sound::getInstance().playSE("click01");

		isSceneEnd = true;    //Z�����ꂽ��V�[���I���i�������j
	}

	if (m_pInput->isKeyDown(KEYCORD::Z))// || m_pInput->isGamePadBottonDown(GAMEPAD_KEYCORD::BUTTON_A,0))
	{
		Sound::getInstance().playSE("click01");
		mSelectName = "stage2";

		isSceneEnd = true;    //Z�����ꂽ��V�[���I���i�������j
	}

	//stageSelect(deltaTime);
	//if (mIsStageSelect) return;
	
}
//�`��
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
//�Z���N�g���̏���
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

