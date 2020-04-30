#include "CWindow.h"

//コンストラクタ
CWindow::CWindow()
	:pFile(NULL)
{
}


//デスストラクタ
CWindow::~CWindow()
{
}

void CWindow::showConsole()
{
	//コンソールの表示
	AllocConsole();
	//標準入出力に割り当てる
	freopen_s(&pFile, "CONOUT$", "w", stdout);
	freopen_s(&pFile, "CONIN$", "r", stdin);
}

void CWindow::log(const char * format, ...)
{
	va_list va;
	va_start(va, format);
	vprintf(format, va);
	va_end(va);
}
