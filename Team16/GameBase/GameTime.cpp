#include "GameTime.h"



GameTime::GameTime()
{
}


GameTime::~GameTime()
{
}
//更新
void GameTime::update()
{
	clock_t mCurrentTime = clock();//現在の時間
	//1フレームにかかる時間　＝　（現在の時間　ー1フレーム前の時間）/秒に変換
	deltaTime = (float)(mCurrentTime - mPreviousTime) / 1000.0;
	mPreviousTime = mCurrentTime;  //1フレーム前を更新
}
//1フレームにかかる時間
float GameTime::getDeltaTime() const
{
	return deltaTime;
}
