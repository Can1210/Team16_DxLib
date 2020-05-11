#pragma once
#ifndef _SCORE_H_
#define _SCORE_H_
#include "../Support/Singleton.h"

//スコアクラス（どのファイルに置けばいいかわからない）
class Score : public Singleton<Score>
{
protected:
	Score();
	virtual ~Score();
public:
	friend class Singleton<Score>;   //Singletonでのインスタンス作成は許可
	//初期化
	void initialize();
	//スコア加算
	void addScore(int score);
	//現在のスコアを取得
	int getScore();
private:
	unsigned int mScore;        //得点
};

#endif // !_SCORE_H_

