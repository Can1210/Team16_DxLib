#pragma once
#ifndef _GAMETIME_H_
#define _GAMETIME_H_
#include <time.h>
#include "../Support/Singleton.h"

//1フレームの時間と取る
class GameTime : public Singleton<GameTime>
{
protected:
	GameTime();
	virtual ~GameTime();
public:
	friend class Singleton<GameTime>;  //Singletonでのインスタンス作成は許可
	//更新
	void update();
	//1フレームにかかる時間
	float getDeltaTime() const;
private:
	clock_t mPreviousTime = clock();   //1フレーム前の時間 最初に設定する
	float deltaTime;
};
#endif // !_GAMETIME_H_

