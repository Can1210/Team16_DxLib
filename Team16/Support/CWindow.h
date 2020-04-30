#pragma once
#ifndef _CWINDOW_H_
#define _CWINDOW_H_

#include "Singleton.h"
#include <windows.h>
#include <iostream>

//コンソールウィンドウの表示
class CWindow :public Singleton<CWindow>
{
protected:
	CWindow();
	virtual ~CWindow();
public:
	friend class Singleton<CWindow>;               //Singletonでのインスタンス作成は許可
	void showConsole();
	void log(const char *format, ...);
private:
	FILE* pFile;
};

#endif // !_CWINDOW_H_

//例）
//CWindow::getInstance().log("floatの引数%f: intの引数%d \n", 1.0,10);

//指定
/*
指定子	対応する型	説明
c	char	文字
s	char *	文字列
d	int, short	10進の整数
u	unsigned int, unsigned short	10進の符号なし整数
o	int, short,
unsigned int,
unsigned short	8進の整数
x	int, short,
unsigned int,
unsigned short	16進の整数
f	float	浮動小数点数
e	float	浮動小数点数の指数表示
g	float	%eもしくは%fのどちらか最適な形式の浮動小数点数
ld	long	10進の倍精度整数
lu	unsinged long	10進の符号なし倍精度整数
lo	long, unsinged long	8進の倍精度整数
lx	long, unsinged long	16進の倍精度整数
lf	double	倍精度浮動小数点数
a	double	16進の倍精度浮動小数点数
*/


