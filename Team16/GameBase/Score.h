#pragma once
#ifndef _SCORE_H_
#define _SCORE_H_
#include "../Support/Singleton.h"

//�X�R�A�N���X�i�ǂ̃t�@�C���ɒu���΂������킩��Ȃ��j
class Score : public Singleton<Score>
{
protected:
	Score();
	virtual ~Score();
public:
	friend class Singleton<Score>;   //Singleton�ł̃C���X�^���X�쐬�͋���
	//������
	void initialize();
	//�X�R�A���Z
	void addScore(int score);
	//���݂̃X�R�A���擾
	int getScore();
private:
	unsigned int mScore;        //���_
};

#endif // !_SCORE_H_

