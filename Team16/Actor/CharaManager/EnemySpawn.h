#pragma once
#ifndef _ENEMYSPAWN_H_
#define _ENEMYSPAWN_H_
#include "CharactorManager.h"
#include "../../Utility/Timer.h"

//�G�����N���X
class EnemySpawn
{
public:
	EnemySpawn(CharactorManager& charactorManager);
	~EnemySpawn();
	//������
	void initialize();
	//�X�V
	void update(float deltaTime);
	//����
	void spawn();
	
private:
	CharactorManager* mCharactorManager;   //�L�����N�^�[�}�l�W���[
	Timer* mTimer;                         //�^�C�}�[
	int spawnTime;

	float sizeX = 64.0f;
	float sizeY = 64.0f;

	float middleX = 600.0f / 2.0f - 32.0f;
};

#endif // !_ENEMYSPAWN_H_
