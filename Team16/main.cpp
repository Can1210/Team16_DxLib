#include "GameBase/WindowInfo.h"
#include "GameBase/GameManager.h"
#include "GameBase/GameTime.h"
#include "Support/CWindow.h"
#include "Device/Input.h"




//関数プロトタイプ宣言
bool initialize();  //初期化
void gameUpdate();	//ループ処理
void release();		//解放

//初期化
bool initialize()
{
	
	ChangeWindowMode(true);
	SetMainWindowText("game16");
	SetGraphMode(WindowInfo::WindowWidth, WindowInfo::WindowHeight, 16);
	SetBackgroundColor(0, 0, 0);
	if (DxLib_Init() == -1)	return false;
	Input::createInstance();
	Input::getInstance().init();
	//各クラスの生成・初期化
	CWindow::createInstance();
	CWindow::getInstance().showConsole();
	GameManager::createInstance();
	GameManager::getInstance().initialize();
	GameTime::createInstance();
	
	return true;
}

//ループ処理
void gameUpdate()
{

	while (ProcessMessage() == 0)
	{
		
		if (Input::getInstance().isKeyDown(KEYCORD::ESCAPE))
			return;
		Input::getInstance().update();
		//背景をクリアに
		ClearDrawScreen();
		GameTime::getInstance().update();
		GameManager::getInstance().update();
		ScreenFlip();
		
	}
}
//解放
void release()
{
}

//WinMain
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	if (!initialize()) return 0;
	gameUpdate();
	//動作、デバッグに必要なものを初期化
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	release();
	DxLib_End();
	return 0;
}
