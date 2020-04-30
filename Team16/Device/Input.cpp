#include "Input.h"
// コンストラクタ
Input::Input(void)
{
}
// デストラクタ
Input::~Input(void)
{
}

#pragma region キーボード関連


//キーが押された瞬間
bool Input::isKeyDown(enum KEYCORD key)
{
	return (mCurrentKey[key] & inputNum) && !(mPreviousKey[key] & inputNum);
}
//キーが押されている間
bool Input::isKeyState(enum KEYCORD key)
{
	return (mCurrentKey[key] & inputNum) && (mPreviousKey[key] & inputNum);
}
//キーが離された瞬間   なぜか機能しない
bool Input::isKeyUp(enum KEYCORD key)
{
	return !(mCurrentKey[key] & inputNum) && (mPreviousKey[key] & inputNum);
}

#pragma endregion

#pragma region ゲームパッド関係


//ボタンが押された瞬間
bool Input::isGamePadBottonDown(enum GAMEPAD_KEYCORD button, int padNum)
{
	return (((m_CurrentJoyInfoExs[padNum].dwButtons & button) != 0) && !((m_PreviousJoyInfoExs[padNum].dwButtons & button) != 0));
}
//ボタンが押されている間
bool Input::isGamePadBottonState(enum GAMEPAD_KEYCORD button, int padNum)
{
	return ((m_CurrentJoyInfoExs[padNum].dwButtons & button) != 0);
}
//ボタンが離されて瞬間
bool Input::isGamePadBottonUp(enum GAMEPAD_KEYCORD button, int padNum)
{
	return (!((m_CurrentJoyInfoExs[padNum].dwButtons & button) != 0) && ((m_PreviousJoyInfoExs[padNum].dwButtons & button) != 0));
}


//十字キーが押された瞬間
bool Input::isGamePadCrossPadDown(enum GAMEPAD_KEYCORD button, int padNum)
{
	return ((m_CurrentJoyInfoExs[padNum].dwPOV == button) && !(m_PreviousJoyInfoExs[padNum].dwPOV == button));
}
//十字キーが押ている間
bool Input::isGamePadCrossPadState(enum GAMEPAD_KEYCORD button, int padNum)
{
	return m_CurrentJoyInfoExs[padNum].dwPOV == button;
}
//十字キーが離された瞬間
bool Input::isGamePadCrossPadUp(enum GAMEPAD_KEYCORD button, int padNum)
{
	return (!(m_CurrentJoyInfoExs[padNum].dwPOV == button) && (m_PreviousJoyInfoExs[padNum].dwPOV == button));
}


//左アナログスティックの傾き X軸
float Input::getGamePad_L_SticNum_X(int padNum)
{
	return (m_CurrentJoyInfoExs[padNum].dwXpos) / (65535 / 10);
}
//左アナログスティックの傾き Y軸
float Input::getGamePad_L_SticNum_Y(int padNum)
{
	return m_CurrentJoyInfoExs[padNum].dwYpos / (65535 / 10);
}
//右アナログスティックの傾き X軸
float Input::getGamePad_R_SticNum_X(int padNum)
{
	return m_CurrentJoyInfoExs[padNum].dwZpos / (65535 / 10);
}
//右アナログスティックの傾き Y軸
float Input::getGamePad_R_SticNum_Y(int padNum)
{
	return m_CurrentJoyInfoExs[padNum].dwRpos / (65535 / 10);
}

#pragma endregion



//更新
void Input::update()
{
	key_update();     //キー情報更新
	gamePad_update(); //ゲームパッド情報更新
}

void Input::init()
{
	//初期設定
	for (int i = 0; i < 4; i++)
	{
		//現在の入力
		m_CurrentJoyInfoExs[i].dwSize = sizeof(JOYINFOEX);
		m_CurrentJoyInfoExs[i].dwFlags = JOY_RETURNALL;
		//1フレーム前のにゅりょく
		m_PreviousJoyInfoExs[i].dwSize = sizeof(JOYINFOEX);
		m_PreviousJoyInfoExs[i].dwFlags = JOY_RETURNALL;
		//接続にエラーがないかどうか
		if (JOYERR_NOERROR == joyGetPosEx(i, &m_CurrentJoyInfoExs[i])) {}
	}
}
//キー関係update
void Input::key_update()
{
	//1フレーム前のキーを更新
	for (int i = 0; i < 256; i++)
	{
		mPreviousKey[i] = mCurrentKey[i];
	}
	//すべての仮想キーの状態を保持する 256 バイトの配列へのポインタを指定する。
	GetKeyboardState(mCurrentKey);
}
//ゲームパッド関係update
void Input::gamePad_update()
{
	//1フレーム前の情報を更新
	for (int i = 0; i < 4; i++)
	{
		m_PreviousJoyInfoExs[i] = m_CurrentJoyInfoExs[i];
	}

	//接続されている分更新     joyGetNumDevs()　がなぜか16になっていしまうので使えず仕方なく4の最大数にする
	for (int i = 0; i < 4; i++)
	{
		//接続にエラーがないかどうか+更新の役割 1フレーム前の物は
		if (JOYERR_NOERROR == joyGetPosEx(i, &m_CurrentJoyInfoExs[i])) {}
	}
}