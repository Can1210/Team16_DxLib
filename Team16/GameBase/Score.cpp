#include "Score.h"



Score::Score()
{
}


Score::~Score()
{
}
//������
void Score::initialize()
{
	mScore = 0;   //���_��0�ŏ�����
}
//�X�R�A���Z
void Score::addScore(int score)
{
	mScore += score;
}
//���݂̃X�R�A���󂯎��
int Score::getScore()
{
	return mScore;
}
