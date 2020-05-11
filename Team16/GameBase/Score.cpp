#include "Score.h"



Score::Score()
{
}


Score::~Score()
{
}
//初期化
void Score::initialize()
{
	mScore = 0;   //得点を0で初期化
}
//スコア加算
void Score::addScore(int score)
{
	mScore += score;
}
//現在のスコアそ受け取る
int Score::getScore()
{
	return mScore;
}
