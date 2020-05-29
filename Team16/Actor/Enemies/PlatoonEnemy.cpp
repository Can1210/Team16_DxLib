#include "PlatoonEnemy.h"
#include <random>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h> // rand, srand関数
#include <time.h>   // time関数
#include "../Bulletes/Bullet.h"
#include "../Bulletes/AngleBullet.h"
#include "../Item/Item.h"


PlatoonEnemy::PlatoonEnemy(Vector2 pos, CharactorManager *c, Vector2 end) : mTimer(new Timer())
{
	charaManager = c;
	b_mPosittion = pos;
	this->angle1 = 260.0f; 
	this->angle2 = 270.0f;
	this->angle3 = 280.0f;
	this->start = pos;
	this->end = end;
}

PlatoonEnemy::~PlatoonEnemy()
{
	delete mTimer;
}

void PlatoonEnemy::initialize()
{
	b_mHp =3;
	b_mCircleSize = 16.0f;
	b_mType = Type::ENEMY;
	b_mAngle = 180.0f;
	b_mArpha = 255;
	b_mSpeed = 70.0f;
	mTimer->initialize();
	enemyTime = 0;
	rnd = (float)GetRandom(0,1);
	if (rnd == 0.0f){rnd = -1.0f;}
	rnd = -1.0f;//仮
	mtype = MoveType::Move1;
	arraySize = 800;
	vec_Array.setSize(arraySize);//00フレーム前の情報を取っておく
	for (int i = 0; i < arraySize; i++)
	{
		vec_Array(i) = b_mPosittion;
	}
	childCount = 0;
	childs = false;
	b_animCnt = 0.0f;
}

void PlatoonEnemy::update(float deltaTime)
{
	mTimer->update(deltaTime);
	b_mVelocity = Vector2(0, 0);
	int frame20 = 20; int frame40 = 40; int frame60 = 60; int frame80 = 80; int frame100 = 100;
	float x;
	float y;
	if (mtype == MoveType::Move1)
	{
		x = sin(enemyTime / 30.0f) * 2.0f;
		y = cos(enemyTime / 30.0f) * 2.0f;
		x = abs(x) * rnd; y = abs(y);
		if (rnd > 0) { if (x < 0)x = 0; }
		else { if (x > 0)x = 0; }
		if (y < 0) { y = 0; };
	}
	vec_Array(enemyTime) = b_mPosittion;
	b_mVelocity = Vector2(x, y);

	if (mTimer->timerSet(2))
	{
		shot(Vector2(b_mPosittion.x, b_mPosittion.y), 180.0f);
	}
	

	enemyTime++;

	if (enemyTime > arraySize)
		enemyTime = 0;
	
	b_mPosittion -= b_mVelocity * b_mSpeed * deltaTime;
}

void PlatoonEnemy::draw(Renderer * renderer, Renderer3D* renderer3D)
{
	//renderer->draw2D("enemy", Vector2(b_mPosittion.x, b_mPosittion.y), Vector2(0, 0), Vector2(64, 64), Vector2(32, 32), Vector2(1.0f, 1.0f), b_mAngle, 255);
	renderer3D->draw3DTexture("enemy", Vector3(b_mPosittion.x, b_mPosittion.y, 0.0f), Vector2(0.0f, 0.0f), Vector2(64.0f, 64.0f), 96.0f, b_mAngle);
	if (b_mHp <= 0)
	{
		b_animCnt += 64.0f;
		
		if (b_animCnt >= 1022.0f)
		{
			Score::getInstance().addScore(100);
			charaManager->add(new Item(b_mPosittion, BulletType::T_LaserBullet, "enemy"));   //アイテム生成
			b_mIsDeath = true;
		}
		renderer3D->draw3DTexture("deathBurst", Vector3(b_mPosittion.x, b_mPosittion.y, 0.0f), Vector2(b_animCnt, 0.0f), Vector2(64.0f, 64.0f), 140.0f, b_mAngle);
	}
}

void PlatoonEnemy::hit(BaseObject & other)
{
	if (other.getType() == Type::PLAYER_BULLET)
	{
		b_mHp -= charaManager->getPlayerBulletDamage();
	}
}

void PlatoonEnemy::shot(Vector2 pos, float angle)
{
	charaManager->add(new AngleBullet(pos, charaManager, b_mType, angle1 + angle));
	charaManager->add(new AngleBullet(pos, charaManager, b_mType, angle2 + angle));
	charaManager->add(new AngleBullet(pos, charaManager, b_mType, angle3 + angle));
}

Vector2 PlatoonEnemy::Traking()
{
	Vector2 v = Vector2(0, 0);
	v = start - end;
	v = -v.normalize();
	return v;
}

int PlatoonEnemy::GetRandom(int min, int max)
{
	unsigned int now = (unsigned int)time(0);
	srand(now);
	rand(); rand(); rand();  rand(); rand();
	return min + (int)(rand()*(max - min + 1.0) / (1.0 + RAND_MAX));
}