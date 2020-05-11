#include "Renderer.h"
#include <string>
#include <math.h>
//コンストラクタ
Renderer::Renderer()
{
}
//デスストラクタ
Renderer::~Renderer()
{
}
//2D描画
void Renderer::draw2D(std::string textureName, Vector2 position, Vector2 drawPos, Vector2 textureSize, bool isTransparency, bool isTurn)
{
	DrawRectGraph(
		(int)position.x, (int)position.y,
		(int)drawPos.x, (int)drawPos.y,
		(int)textureSize.x, (int)textureSize.y,
		TextureLoad::getInstance().set(textureName),
		isTransparency, isTurn
	);
}
void Renderer::draw2D(std::string textureName, Vector2 position, Vector2 drawPos, Vector2 textureSize, Vector2 angleCenter, Vector2 scale, float angle, int alpha, bool isTransparency, bool isTurn)
{
	//指定した画像を切り取って新しい画像を作成（指定した画像は切り取られてはいない）
	int cutTexture = DerivationGraph(
		(int)drawPos.x, (int)drawPos.y,
		(int)textureSize.x, (int)textureSize.y, TextureLoad::getInstance().set(textureName));

	//ラジアンを度に変換
	float deg = angle * (DX_PI_F / 180.0f);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);  //ブレンドモードをαに設定
	DrawRotaGraph3(
		(int)position.x + ((int)textureSize.x / 2), (int)position.y + ((int)textureSize.y / 2),       //ここ注意！！バグる可能性大
		(int)angleCenter.x, (int)angleCenter.y,
		(double)scale.x, (double)scale.y,
		(double)deg,
		cutTexture,
		isTransparency, isTurn);
	DeleteGraph(cutTexture);                      //作ったものを消去
}




//数字描画
void Renderer::drawNumber(std::string textureName, Vector2 position, double number, unsigned int digits, Vector2 scale, Vector2 angleCenter, float angle, int alpha)
{
	//数字を文字に変換
	std::string stringNum = std::to_string(number);
	int dot = stringNum.find('.');          //「.」を探す
	//変換した文字とドットの長さを比べて少ない方を調べてる＋桁数
	int numberLength = std::fminf(stringNum.length(), dot) + digits;
	Vector2 basePos = position - Vector2((float)numberLength* mNumTexture_Width, 0);

	for (int i = 0; i <= numberLength; i++)
	{
		//変換した数字を一つずつ調べる
		auto character = stringNum[i];
		//文字が「.」ではなかったら
		if (character != '.')
		{
			//型変換
			int num = character - '0';
			draw2D(textureName, basePos + Vector2(i* mNumTexture_Width, 0), Vector2(num* mNumTexture_Width, 0), Vector2(mNumTexture_Width, mNumTexture_Height), scale, angleCenter, angle, alpha);
		}
		else
		{
			//一番最後にあるから11
			draw2D(textureName, basePos + Vector2(i* mNumTexture_Width, 0), Vector2(10 * mNumTexture_Width, 0), Vector2(mNumTexture_Width, mNumTexture_Height), scale, angleCenter, angle, alpha);
		}
	}
}


void Renderer::drawScoreNumber(std::string textureName, Vector2 position, int number, unsigned int digits, Vector2 angleCenter, Vector2 scale, float angle, int alpha)
{
	//数字を文字に変換
	std::string stringNum = std::to_string(number);
	//変換した文字とドットの長さを比べて少ない方を調べてる＋桁数
	int numberLength = stringNum.length();
	Vector2 basePos = position - Vector2((float)numberLength* mNumTexture_Width, 0);

	for (int i = 0; i <= numberLength; i++)
	{
		//変換した数字を一つずつ調べる
		auto character = stringNum[i];
		//型変換
		int num = character - '0';
		draw2D(textureName, basePos + Vector2(i* mNumTexture_Width, 0), Vector2(num* mNumTexture_Width, 0), Vector2(mNumTexture_Width, mNumTexture_Height), scale, angleCenter, angle, alpha);

	}
}
//文字描画（挑戦中...）
void Renderer::drawText(std::string textureName, std::string writeString, Vector2 position, Vector2 angleCenter, Vector2 scale, float angle, int alpha)
{
	//文字列の長さを取得
	int s_Length = writeString.length();
	Vector2 basePos = Vector2(0, 0);   //改行用文字位置
	int charNum = 0;                   //改行用文字数保存
	for (int i = 0; i <= s_Length; i++)
	{
		//変換した数字を一つずつ調べる
		//改行されているかを調べる
		auto character = writeString[i];
		//改行されているかを調べるされていたら今は70下げるここ拡大に合わせないとおかしい
		if (character == '\n')
		{
			charNum = (i - (charNum - 1));
			basePos += Vector2(charNum * mFontTexture_Big_Width, -70);   //改行されたところの番号だけ記憶して足す
			charNum = i + 1;
		}

#pragma region 文字指定
		//めちゃくちゃ大量になるけど一応書く
		switch (character)
		{
#pragma region 大文字
		case 'A':
			draw2D(textureName, position + Vector2(i * mFontTexture_Big_Width, 0) - basePos, Vector2(0 * mFontTexture_Big_Width, 0), Vector2(mFontTexture_Big_Width, mFontTexture_Big_Height), angleCenter, scale, angle, alpha);
			break;
		case 'B':
			draw2D(textureName, position + Vector2(i * mFontTexture_Big_Width, 0) - basePos, Vector2(1 * mFontTexture_Big_Width, 0), Vector2(mFontTexture_Big_Width, mFontTexture_Big_Height), angleCenter, scale, angle, alpha);
			break;
		case 'C':
			draw2D(textureName, position + Vector2(i * mFontTexture_Big_Width, 0) - basePos, Vector2(2 * mFontTexture_Big_Width, 0), Vector2(mFontTexture_Big_Width, mFontTexture_Big_Height), angleCenter, scale, angle, alpha);
			break;
		case 'D':
			draw2D(textureName, position + Vector2(i * mFontTexture_Big_Width, 0) - basePos, Vector2(3 * mFontTexture_Big_Width, 0), Vector2(mFontTexture_Big_Width, mFontTexture_Big_Height), angleCenter, scale, angle, alpha);
			break;
		case 'E':
			draw2D(textureName, position + Vector2(i * mFontTexture_Big_Width, 0) - basePos, Vector2(4 * mFontTexture_Big_Width, 0), Vector2(mFontTexture_Big_Width, mFontTexture_Big_Height), angleCenter, scale, angle, alpha);
			break;
		case 'F':
			draw2D(textureName, position + Vector2(i * mFontTexture_Big_Width, 0) - basePos, Vector2(5 * mFontTexture_Big_Width, 0), Vector2(mFontTexture_Big_Width, mFontTexture_Big_Height), angleCenter, scale, angle, alpha);
			break;
		case 'G':
			draw2D(textureName, position + Vector2(i * mFontTexture_Big_Width, 0) - basePos, Vector2(6 * mFontTexture_Big_Width, 0), Vector2(mFontTexture_Big_Width, mFontTexture_Big_Height), angleCenter, scale, angle, alpha);
			break;
		case 'H':
			draw2D(textureName, position + Vector2(i * mFontTexture_Big_Width, 0) - basePos, Vector2(7 * mFontTexture_Big_Width, 0), Vector2(mFontTexture_Big_Width, mFontTexture_Big_Height), angleCenter, scale, angle, alpha);
			break;
		case 'I':
			draw2D(textureName, position + Vector2(i * mFontTexture_Big_Width, 0) - basePos, Vector2(8 * mFontTexture_Big_Width, 0), Vector2(mFontTexture_Big_Width, mFontTexture_Big_Height), angleCenter, scale, angle, alpha);
			break;
		case 'J':
			draw2D(textureName, position + Vector2(i * mFontTexture_Big_Width, 0) - basePos, Vector2(9 * mFontTexture_Big_Width, 0), Vector2(mFontTexture_Big_Width, mFontTexture_Big_Height), angleCenter, scale, angle, alpha);
			break;
		case 'K':
			draw2D(textureName, position + Vector2(i * mFontTexture_Big_Width, 0) - basePos, Vector2(10 * mFontTexture_Big_Width, 0), Vector2(mFontTexture_Big_Width, mFontTexture_Big_Height), angleCenter, scale, angle, alpha);
			break;
		case 'L':
			draw2D(textureName, position + Vector2(i * mFontTexture_Big_Width, 0) - basePos, Vector2(11 * mFontTexture_Big_Width, 0), Vector2(mFontTexture_Big_Width, mFontTexture_Big_Height), angleCenter, scale, angle, alpha);
			break;
		case 'M':
			draw2D(textureName, position + Vector2(i * mFontTexture_Big_Width, 0) - basePos, Vector2(12 * mFontTexture_Big_Width, 0), Vector2(mFontTexture_Big_Width, mFontTexture_Big_Height), angleCenter, scale, angle, alpha);
			break;
		case 'N':
			draw2D(textureName, position + Vector2(i * mFontTexture_Big_Width, 0) - basePos, Vector2(13 * mFontTexture_Big_Width, 0), Vector2(mFontTexture_Big_Width, mFontTexture_Big_Height), angleCenter, scale, angle, alpha);
			break;
		case 'O':
			draw2D(textureName, position + Vector2(i * mFontTexture_Big_Width, 0) - basePos, Vector2(14 * mFontTexture_Big_Width, 0), Vector2(mFontTexture_Big_Width, mFontTexture_Big_Height), angleCenter, scale, angle, alpha);
			break;
		case 'P':
			draw2D(textureName, position + Vector2(i * mFontTexture_Big_Width, 0) - basePos, Vector2(15 * mFontTexture_Big_Width, 0), Vector2(mFontTexture_Big_Width, mFontTexture_Big_Height), angleCenter, scale, angle, alpha);
			break;
		case 'Q':
			draw2D(textureName, position + Vector2(i * mFontTexture_Big_Width, 0) - basePos, Vector2(16 * mFontTexture_Big_Width, 0), Vector2(mFontTexture_Big_Width, mFontTexture_Big_Height), angleCenter, scale, angle, alpha);
			break;
		case 'R':
			draw2D(textureName, position + Vector2(i * mFontTexture_Big_Width, 0) - basePos, Vector2(17 * mFontTexture_Big_Width, 0), Vector2(mFontTexture_Big_Width, mFontTexture_Big_Height), angleCenter, scale, angle, alpha);
			break;
		case 'S':
			draw2D(textureName, position + Vector2(i * mFontTexture_Big_Width, 0) - basePos, Vector2(18 * mFontTexture_Big_Width, 0), Vector2(mFontTexture_Big_Width, mFontTexture_Big_Height), angleCenter, scale, angle, alpha);
			break;
		case 'T':
			draw2D(textureName, position + Vector2(i * mFontTexture_Big_Width, 0) - basePos, Vector2(19 * mFontTexture_Big_Width, 0), Vector2(mFontTexture_Big_Width, mFontTexture_Big_Height), angleCenter, scale, angle, alpha);
			break;
		case 'U':
			draw2D(textureName, position + Vector2(i * mFontTexture_Big_Width, 0) - basePos, Vector2(20 * mFontTexture_Big_Width, 0), Vector2(mFontTexture_Big_Width, mFontTexture_Big_Height), angleCenter, scale, angle, alpha);
			break;
		case 'V':
			draw2D(textureName, position + Vector2(i * mFontTexture_Big_Width, 0) - basePos, Vector2(21 * mFontTexture_Big_Width, 0), Vector2(mFontTexture_Big_Width, mFontTexture_Big_Height), angleCenter, scale, angle, alpha);
			break;
		case 'W':
			draw2D(textureName, position + Vector2(i * mFontTexture_Big_Width, 0) - basePos, Vector2(22 * mFontTexture_Big_Width, 0), Vector2(mFontTexture_Big_Width, mFontTexture_Big_Height), angleCenter, scale, angle, alpha);
			break;
		case 'X':
			draw2D(textureName, position + Vector2(i * mFontTexture_Big_Width, 0) - basePos, Vector2(23 * mFontTexture_Big_Width, 0), Vector2(mFontTexture_Big_Width, mFontTexture_Big_Height), angleCenter, scale, angle, alpha);
			break;
		case 'Y':
			draw2D(textureName, position + Vector2(i * mFontTexture_Big_Width, 0) - basePos, Vector2(24 * mFontTexture_Big_Width, 0), Vector2(mFontTexture_Big_Width, mFontTexture_Big_Height), angleCenter, scale, angle, alpha);
			break;
		case 'Z':
			draw2D(textureName, position + Vector2(i * mFontTexture_Big_Width, 0) - basePos, Vector2(25 * mFontTexture_Big_Width, 0), Vector2(mFontTexture_Big_Width, mFontTexture_Big_Height), angleCenter, scale, angle, alpha);
			break;

#pragma endregion

#pragma region 小文字



		case 'a':
			draw2D(textureName, position + Vector2(i * mFontTexture_Small_Width, -5) - basePos, Vector2(0 * mFontTexture_Small_Width, 50), Vector2(mFontTexture_Small_Width, mFontTexture_Small_Height), angleCenter, scale, angle, alpha);
			break;
		case 'b':
			draw2D(textureName, position + Vector2(i * mFontTexture_Small_Width, -5) - basePos, Vector2(1 * mFontTexture_Small_Width, 50), Vector2(mFontTexture_Small_Width, mFontTexture_Small_Height), angleCenter, scale, angle, alpha);
			break;
		case 'c':
			draw2D(textureName, position + Vector2(i * mFontTexture_Small_Width, -5) - basePos, Vector2(2 * mFontTexture_Small_Width, 50), Vector2(mFontTexture_Small_Width, mFontTexture_Small_Height), angleCenter, scale, angle, alpha);
			break;
		case 'd':
			draw2D(textureName, position + Vector2(i * mFontTexture_Small_Width, -5) - basePos, Vector2(3 * mFontTexture_Small_Width, 50), Vector2(mFontTexture_Small_Width, mFontTexture_Small_Height), angleCenter, scale, angle, alpha);
			break;
		case 'e':
			draw2D(textureName, position + Vector2(i * mFontTexture_Small_Width, -5) - basePos, Vector2(4 * mFontTexture_Small_Width, 50), Vector2(mFontTexture_Small_Width, mFontTexture_Small_Height), angleCenter, scale, angle, alpha);
			break;
		case 'f':
			draw2D(textureName, position + Vector2(i * mFontTexture_Small_Width, -5) - basePos, Vector2(5 * mFontTexture_Small_Width, 50), Vector2(mFontTexture_Small_Width, mFontTexture_Small_Height), angleCenter, scale, angle, alpha);
			break;
		case 'g':
			draw2D(textureName, position + Vector2(i * mFontTexture_Small_Width, -5) - basePos, Vector2(6 * mFontTexture_Small_Width, 50), Vector2(mFontTexture_Small_Width, mFontTexture_Small_Height), angleCenter, scale, angle, alpha);
			break;
		case 'h':
			draw2D(textureName, position + Vector2(i * mFontTexture_Small_Width, -5) - basePos, Vector2(7 * mFontTexture_Small_Width, 50), Vector2(mFontTexture_Small_Width, mFontTexture_Small_Height), angleCenter, scale, angle, alpha);
			break;
		case 'i':
			draw2D(textureName, position + Vector2(i * mFontTexture_Small_Width, -5) - basePos, Vector2(8 * mFontTexture_Small_Width, 50), Vector2(mFontTexture_Small_Width, mFontTexture_Small_Height), angleCenter, scale, angle, alpha);
			break;
		case 'j':
			draw2D(textureName, position + Vector2(i * mFontTexture_Small_Width, -5) - basePos, Vector2(9 * mFontTexture_Small_Width, 50), Vector2(mFontTexture_Small_Width, mFontTexture_Small_Height), angleCenter, scale, angle, alpha);
			break;
		case 'k':
			draw2D(textureName, position + Vector2(i * mFontTexture_Small_Width, -5) - basePos, Vector2(10 * mFontTexture_Small_Width, 50), Vector2(mFontTexture_Small_Width, mFontTexture_Small_Height), angleCenter, scale, angle, alpha);
			break;
		case 'l':
			draw2D(textureName, position + Vector2(i * mFontTexture_Small_Width, -5) - basePos, Vector2(11 * mFontTexture_Small_Width, 50), Vector2(mFontTexture_Small_Width, mFontTexture_Small_Height), angleCenter, scale, angle, alpha);
			break;
		case 'm':
			draw2D(textureName, position + Vector2(i * mFontTexture_Small_Width, -5) - basePos, Vector2(12 * mFontTexture_Small_Width, 50), Vector2(mFontTexture_Small_Width, mFontTexture_Small_Height), angleCenter, scale, angle, alpha);
			break;
		case 'n':
			draw2D(textureName, position + Vector2(i * mFontTexture_Small_Width, -5) - basePos, Vector2(13 * mFontTexture_Small_Width, 50), Vector2(mFontTexture_Small_Width, mFontTexture_Small_Height), angleCenter, scale, angle, alpha);
			break;
		case 'o':
			draw2D(textureName, position + Vector2(i * mFontTexture_Small_Width, -5) - basePos, Vector2(14 * mFontTexture_Small_Width, 50), Vector2(mFontTexture_Small_Width, mFontTexture_Small_Height), angleCenter, scale, angle, alpha);
			break;
		case 'p':
			draw2D(textureName, position + Vector2(i * mFontTexture_Small_Width, -5) - basePos, Vector2(15 * mFontTexture_Small_Width, 50), Vector2(mFontTexture_Small_Width, mFontTexture_Small_Height), angleCenter, scale, angle, alpha);
			break;
		case 'q':
			draw2D(textureName, position + Vector2(i * mFontTexture_Small_Width, -5) - basePos, Vector2(16 * mFontTexture_Small_Width, 50), Vector2(mFontTexture_Small_Width, mFontTexture_Small_Height), angleCenter, scale, angle, alpha);
			break;
		case 'r':
			draw2D(textureName, position + Vector2(i * mFontTexture_Small_Width, -5) - basePos, Vector2(17 * mFontTexture_Small_Width, 50), Vector2(mFontTexture_Small_Width, mFontTexture_Small_Height), angleCenter, scale, angle, alpha);
			break;
		case 's':
			draw2D(textureName, position + Vector2(i * mFontTexture_Small_Width, -5) - basePos, Vector2(18 * mFontTexture_Small_Width, 50), Vector2(mFontTexture_Small_Width, mFontTexture_Small_Height), angleCenter, scale, angle, alpha);
			break;
		case 't':
			draw2D(textureName, position + Vector2(i * mFontTexture_Small_Width, -5) - basePos, Vector2(19 * mFontTexture_Small_Width, 50), Vector2(mFontTexture_Small_Width, mFontTexture_Small_Height), angleCenter, scale, angle, alpha);
			break;
		case 'u':
			draw2D(textureName, position + Vector2(i * mFontTexture_Small_Width, -5) - basePos, Vector2(20 * mFontTexture_Small_Width, 50), Vector2(mFontTexture_Small_Width, mFontTexture_Small_Height), angleCenter, scale, angle, alpha);
			break;
		case 'v':
			draw2D(textureName, position + Vector2(i * mFontTexture_Small_Width, -5) - basePos, Vector2(21 * mFontTexture_Small_Width, 50), Vector2(mFontTexture_Small_Width, mFontTexture_Small_Height), angleCenter, scale, angle, alpha);
			break;
		case 'w':
			draw2D(textureName, position + Vector2(i * mFontTexture_Small_Width, -5) - basePos, Vector2(22 * mFontTexture_Small_Width, 50), Vector2(mFontTexture_Small_Width, mFontTexture_Small_Height), angleCenter, scale, angle, alpha);
			break;
		case 'x':
			draw2D(textureName, position + Vector2(i * mFontTexture_Small_Width, -5) - basePos, Vector2(23 * mFontTexture_Small_Width, 50), Vector2(mFontTexture_Small_Width, mFontTexture_Small_Height), angleCenter, scale, angle, alpha);
			break;
		case 'y':
			draw2D(textureName, position + Vector2(i * mFontTexture_Small_Width, -5) - basePos, Vector2(24 * mFontTexture_Small_Width, 50), Vector2(mFontTexture_Small_Width, mFontTexture_Small_Height), angleCenter, scale, angle, alpha);
			break;
		case 'z':
			draw2D(textureName, position + Vector2(i * mFontTexture_Small_Width, -5) - basePos, Vector2(25 * mFontTexture_Small_Width, 50), Vector2(mFontTexture_Small_Width, mFontTexture_Small_Height), angleCenter, scale, angle, alpha);
			break;
#pragma endregion
#pragma region 数字・記号

		case '0':
			draw2D(textureName, position + Vector2(i * mFontTexture_Big_Width, -5) - basePos, Vector2(0 * mFontTexture_Symbol_Width, 110), Vector2(mFontTexture_Symbol_Width, mFontTexture_Symbol_Height), angleCenter, scale, angle, alpha);
			break;
		case '1':
			draw2D(textureName, position + Vector2(i * mFontTexture_Big_Width, -5) - basePos, Vector2(1 * mFontTexture_Symbol_Width, 110), Vector2(mFontTexture_Symbol_Width, mFontTexture_Symbol_Height), angleCenter, scale, angle, alpha);
			break;
		case '2':
			draw2D(textureName, position + Vector2(i * mFontTexture_Big_Width, -5) - basePos, Vector2(2 * mFontTexture_Symbol_Width, 110), Vector2(mFontTexture_Symbol_Width, mFontTexture_Symbol_Height), angleCenter, scale, angle, alpha);
			break;
		case '3':
			draw2D(textureName, position + Vector2(i * mFontTexture_Big_Width, -5) - basePos, Vector2(3 * mFontTexture_Symbol_Width, 110), Vector2(mFontTexture_Symbol_Width, mFontTexture_Symbol_Height), angleCenter, scale, angle, alpha);
			break;
		case '4':
			draw2D(textureName, position + Vector2(i * mFontTexture_Big_Width, -5) - basePos, Vector2(4 * mFontTexture_Symbol_Width, 110), Vector2(mFontTexture_Symbol_Width, mFontTexture_Symbol_Height), angleCenter, scale, angle, alpha);
			break;
		case '5':
			draw2D(textureName, position + Vector2(i * mFontTexture_Big_Width, -5) - basePos, Vector2(5 * mFontTexture_Symbol_Width, 110), Vector2(mFontTexture_Symbol_Width, mFontTexture_Symbol_Height), angleCenter, scale, angle, alpha);
			break;
		case '6':
			draw2D(textureName, position + Vector2(i * mFontTexture_Big_Width, -5) - basePos, Vector2(6 * mFontTexture_Symbol_Width, 110), Vector2(mFontTexture_Symbol_Width, mFontTexture_Symbol_Height), angleCenter, scale, angle, alpha);
			break;
		case '7':
			draw2D(textureName, position + Vector2(i * mFontTexture_Big_Width, -5) - basePos, Vector2(7 * mFontTexture_Symbol_Width, 110), Vector2(mFontTexture_Symbol_Width, mFontTexture_Symbol_Height), angleCenter, scale, angle, alpha);
			break;
		case '8':
			draw2D(textureName, position + Vector2(i * mFontTexture_Big_Width, -5) - basePos, Vector2(8 * mFontTexture_Symbol_Width, 110), Vector2(mFontTexture_Symbol_Width, mFontTexture_Symbol_Height), angleCenter, scale, angle, alpha);
			break;
		case '9':
			draw2D(textureName, position + Vector2(i * mFontTexture_Big_Width, -5) - basePos, Vector2(9 * mFontTexture_Symbol_Width, 110), Vector2(mFontTexture_Symbol_Width, mFontTexture_Symbol_Height), angleCenter, scale, angle, alpha);
			break;
		case '.':
			draw2D(textureName, position + Vector2(i * mFontTexture_Big_Width, -5) - basePos, Vector2(10 * mFontTexture_Symbol_Width, 110), Vector2(mFontTexture_Symbol_Width, mFontTexture_Symbol_Height), angleCenter, scale, angle, alpha);
			break;
		case '+':
			draw2D(textureName, position + Vector2(i * mFontTexture_Big_Width, -5) - basePos, Vector2(11 * mFontTexture_Symbol_Width, 110), Vector2(mFontTexture_Symbol_Width, mFontTexture_Symbol_Height), angleCenter, scale, angle, alpha);
			break;
		case '-':
			draw2D(textureName, position + Vector2(i * mFontTexture_Big_Width, -5) - basePos, Vector2(12 * mFontTexture_Symbol_Width, 110), Vector2(mFontTexture_Symbol_Width, mFontTexture_Symbol_Height), angleCenter, scale, angle, alpha);
			break;
		case '/':
			draw2D(textureName, position + Vector2(i * mFontTexture_Big_Width, -5) - basePos, Vector2(13 * mFontTexture_Symbol_Width, 110), Vector2(mFontTexture_Symbol_Width, mFontTexture_Symbol_Height), angleCenter, scale, angle, alpha);
			break;
		case '×':
			draw2D(textureName, position + Vector2(i * mFontTexture_Big_Width, -5) - basePos, Vector2(14 * mFontTexture_Symbol_Width, 110), Vector2(mFontTexture_Symbol_Width, mFontTexture_Symbol_Height), angleCenter, scale, angle, alpha);
			break;
		case '÷':
			draw2D(textureName, position + Vector2(i * mFontTexture_Big_Width, -5) - basePos, Vector2(15 * mFontTexture_Symbol_Width, 110), Vector2(mFontTexture_Symbol_Width, mFontTexture_Symbol_Height), angleCenter, scale, angle, alpha);
			break;
		case '=':
			draw2D(textureName, position + Vector2(i * mFontTexture_Big_Width, -5) - basePos, Vector2(16 * mFontTexture_Symbol_Width, 110), Vector2(mFontTexture_Symbol_Width, mFontTexture_Symbol_Height), angleCenter, scale, angle, alpha);
			break;
		case '!':
			draw2D(textureName, position + Vector2(i * mFontTexture_Big_Width, -5) - basePos, Vector2(17 * mFontTexture_Symbol_Width, 110), Vector2(mFontTexture_Symbol_Width, mFontTexture_Symbol_Height), angleCenter, scale, angle, alpha);
			break;
		case '?':
			draw2D(textureName, position + Vector2(i * mFontTexture_Big_Width, -5) - basePos, Vector2(18 * mFontTexture_Symbol_Width, 110), Vector2(mFontTexture_Symbol_Width, mFontTexture_Symbol_Height), angleCenter, scale, angle, alpha);
			break;
		case '"':
			draw2D(textureName, position + Vector2(i * mFontTexture_Big_Width, -5) - basePos, Vector2(19 * mFontTexture_Symbol_Width, 110), Vector2(mFontTexture_Symbol_Width, mFontTexture_Symbol_Height), angleCenter, scale, angle, alpha);
			break;
		case '#':
			draw2D(textureName, position + Vector2(i * mFontTexture_Big_Width, -5) - basePos, Vector2(20 * mFontTexture_Symbol_Width, 110), Vector2(mFontTexture_Symbol_Width, mFontTexture_Symbol_Height), angleCenter, scale, angle, alpha);
			break;
		case ':':
			draw2D(textureName, position + Vector2(i * mFontTexture_Big_Width, -5) - basePos, Vector2(21 * mFontTexture_Symbol_Width, 110), Vector2(mFontTexture_Symbol_Width, mFontTexture_Symbol_Height), angleCenter, scale, angle, alpha);
			break;
		case ';':
			draw2D(textureName, position + Vector2(i * mFontTexture_Big_Width, -5) - basePos, Vector2(22 * mFontTexture_Symbol_Width, 110), Vector2(mFontTexture_Symbol_Width, mFontTexture_Symbol_Height), angleCenter, scale, angle, alpha);
			break;
		case '^':
			draw2D(textureName, position + Vector2(i * mFontTexture_Big_Width, -5) - basePos, Vector2(24 * mFontTexture_Symbol_Width, 110), Vector2(mFontTexture_Symbol_Width, mFontTexture_Symbol_Height), angleCenter, scale, angle, alpha);
			break;
		case '~':
			draw2D(textureName, position + Vector2(i * mFontTexture_Big_Width, -5) - basePos, Vector2(25 * mFontTexture_Symbol_Width, 110), Vector2(mFontTexture_Symbol_Width, mFontTexture_Symbol_Height), angleCenter, scale, angle, alpha);
			break;
		case ',':
			draw2D(textureName, position + Vector2(i * mFontTexture_Big_Width, -5) - basePos, Vector2(26 * mFontTexture_Symbol_Width, 110), Vector2(mFontTexture_Symbol_Width, mFontTexture_Symbol_Height), angleCenter, scale, angle, alpha);
			break;
		default:
			break;
		}
#pragma endregion

#pragma endregion

	}
}
