#include "CWindow.h"

//�R���X�g���N�^
CWindow::CWindow()
	:pFile(NULL)
{
}


//�f�X�X�g���N�^
CWindow::~CWindow()
{
}

void CWindow::showConsole()
{
#ifdef _DEBUG
	//�R���\�[���̕\��
	AllocConsole();
	//�W�����o�͂Ɋ��蓖�Ă�
	freopen_s(&pFile, "CONOUT$", "w", stdout);
	freopen_s(&pFile, "CONIN$", "r", stdin);

#endif // DEBUG

	

	
}

void CWindow::log(const char * format, ...)
{
#ifdef _DEBUG
	va_list va;
	va_start(va, format);
	vprintf(format, va);
	va_end(va);
#endif // DEBUG
}
