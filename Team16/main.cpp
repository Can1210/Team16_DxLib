#include "GameBase/WindowInfo.h"
#include "GameBase/GameManager.h"
#include "GameBase/GameTime.h"
#include "Support/CWindow.h"
#include "Device/Input.h"




//�֐��v���g�^�C�v�錾
bool initialize();  //������
void gameUpdate();	//���[�v����
void release();		//���

//������
bool initialize()
{
	
	ChangeWindowMode(true);
	SetMainWindowText("game16");
	SetGraphMode(WindowInfo::WindowWidth, WindowInfo::WindowHeight, 16);
	SetBackgroundColor(0, 0, 0);
	if (DxLib_Init() == -1)	return false;
	Input::createInstance();
	Input::getInstance().init();
	//�e�N���X�̐����E������
	CWindow::createInstance();
	CWindow::getInstance().showConsole();
	GameManager::createInstance();
	GameManager::getInstance().initialize();
	GameTime::createInstance();
	
	return true;
}

//���[�v����
void gameUpdate()
{

	while (ProcessMessage() == 0)
	{
		
		if (Input::getInstance().isKeyDown(KEYCORD::ESCAPE))
			return;
		Input::getInstance().update();
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
}

//WinMain
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	if (!initialize()) return 0;
	gameUpdate();
	//����A�f�o�b�O�ɕK�v�Ȃ��̂�������
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	release();
	DxLib_End();
	return 0;
}
