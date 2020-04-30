#pragma once
#ifndef _TIMER_H_
#define _TIMER_H_

//時間経過判断
class Timer
{
public:
	Timer();
	~Timer();
	//初期化
	void initialize();
	//更新
	void update(float deltaTime);
	//タイマーセット：何秒待つか　経過するまでfalse
	bool timerSet(float setTime);
private:
	float mCurrentTime;   //現在の時間
};

#endif // !_TIMER_H_