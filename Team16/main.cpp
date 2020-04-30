#include "GameBase/WindowInfo.h"
#include "GameBase/GameManager.h"
#include "GameBase/GameTime.h"
#include "Support/CWindow.h"
#include "Device/Input.h"

//�֐��v���g�^�C�v�錾
bool initialize();  //������
void gameUpdate();	//���[�v����
void release();		//���

//�O���[�o���ϐ�
Input* input;

//������
bool initialize()
{
	//����A�f�o�b�O�ɕK�v�Ȃ��̂�������
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	ChangeWindowMode(true);
	SetMainWindowText("game16");
	SetGraphMode(WindowInfo::WindowWidth, WindowInfo::WindowHeight, 16);
	SetBackgroundColor(0, 50, 50);
	if (DxLib_Init() == -1)	return false;
	//�e�N���X�̐����E������
	CWindow::createInstance();
	CWindow::getInstance().showConsole();
	GameManager::createInstance();
	GameManager::getInstance().initialize();
	GameTime::createInstance();
	input = new Input();
	input->init();
	return true;
}

//���[�v����
void gameUpdate()
{

	while (ProcessMessage() == 0)
	{
		if (input->isKeyDown(KEYCORD::ESCAPE))
			return;
		input->update();
		//�w�i���N���A��
		ClearDrawScreen();
		GameTime::getInstance().update();
		GameManager::getInstance().update();
		ScreenFlip();
	}
}
//���
void release()
{
	delete input;
}

//WinMain
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	if (!initialize()) return 0;
	gameUpdate();
	DxLib_End();
	release();
	return 0;
}
