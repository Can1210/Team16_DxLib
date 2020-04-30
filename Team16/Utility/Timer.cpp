#include "Timer.h"


//コンストラクタ
Timer::Timer()
	:mCurrentTime(0)
{
}

//デスストラクタ
Timer::~Timer()
{
}
//初期化
void Timer::initialize()
{
	mCurrentTime = 0;//0で初期化
}
void Timer::update(float deltaTime)
{
	mCurrentTime += deltaTime;         //現在の時間に加算する
}
//タイマーセット
bool Timer::timerSet(float setTime)
{
	//現在の時間が最大になったらtrue
	if (mCurrentTime >= setTime)
	{
		initialize();    //初期化
		return true;
	}
	return false;
}
