#include "PlatoonEnemy.h"
#include <random>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h> // rand, srand関数
#include <time.h>   // time関数

PlatoonEnemy::PlatoonEnemy(Vector2 pos, CharactorManager *c, float angle1, float angle2, float angle3, Vector2 end) : mTimer(new Timer())
{
	charaManager = c;
	b_mPosittion = pos;
	this->angle1 = angle1;
	this->angle2 = angle2;
	this->angle3 = angle3;
	this->start = pos;
	this->end = end;
}

PlatoonEnemy::~PlatoonEnemy()
{
	delete input;
	delete mTimer;
}



void PlatoonEnemy::initialize()
{
	b_mHp =3;
	MoveFlag = FALSE;
	input = new Input;
	input->init();
	b_mCircleSize = 16.0f;
	b_mType = Type::ENEMY;
	b_mAngle = 180.0f;
	mTimer->initialize();
	enemyTime = 0;
	rnd = GetRandom(0,1);
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

	subShotCnt = 20;
	b_mArpha = 255;
	b_mSpeed = 70.0f;
	itemCnt = 0;
}

void PlatoonEnemy::update(float deltaTime)
{
	mTimer->update(deltaTime);

	input->update();
	b_mVelocity = Vector2(0, 0);
	

	if (b_mType == Type::SUB_PLAYER)
	{
		b_mPosittion = charaManager->searchPlayer();
		if (input->isKeyState(KEYCORD::SPACE))
		{
			subShotCnt++;
			if (subShotCnt > 20)
			{
				SubShot(Vector2(b_mPosittion.x, b_mPosittion.y), 180.0f);
				subShotCnt = 0;
			}
			
		}
		if (input->isKeyDown(KEYCORD::C))
		{
			Jibaku(Vector2(b_mPosittion.x, b_mPosittion.y));
		}
		
	}
	int frame20 = 20; int frame40 = 40; int frame60 = 60; int frame80 = 80; int frame100 = 100;

	if (b_mType == Type::ENEMY)
	{
		float x;
		float y;
		if (mtype == MoveType::Move1)
		{
			x = sin(enemyTime / 30.0f) * 2.0f;
			y = cos(enemyTime / 30.0f) * 2.0f;
			x = abs(x) * rnd; y = abs(y);
			if (rnd > 0){if (x < 0)x = 0;}
			else { if (x > 0)x = 0; }
			if (y < 0) { y = 0; };
		}
		vec_Array(enemyTime) = b_mPosittion;

		
		b_mVelocity = Vector2(x,y);

		if (mTimer->timerSet(2))
		{
			SubShot(Vector2(b_mPosittion.x, b_mPosittion.y), 0.0f);
		}
		if (b_mPosittion.y > WindowInfo::WindowHeight
			|| b_mPosittion.x > WindowInfo::WindowWidth
			|| b_mPosittion.x < 0)
		{
			b_mIsDeath = true;
		}
		if (b_mHp <= 0)
		{
			Score::getInstance().addScore(100);
			b_mType = Type::ITEM;
		}
	}
	enemyTime++;

	
	if (enemyTime > arraySize)
		enemyTime = 0.0f;
	
	b_mPosittion += b_mVelocity;

	//ドロップ後処理
	if (b_mType == Type::ITEM)
	{
		itemCnt++;
		if (itemCnt > 150)
		{
			b_mIsDeath = true;
		}
	}
}

void PlatoonEnemy::draw(Renderer * renderer, Renderer3D* renderer3D)
{
	if (b_mType == Type::ENEMY)
	{
		DrawCircle(b_mPosittion.x + 64 / 2, b_mPosittion.y + 64 / 2, b_mCircleSize, GetColor(255, 0, 0), FALSE);
		renderer->draw2D("enemy", Vector2(b_mPosittion.x, b_mPosittion.y), Vector2(0, 0), Vector2(64, 64), Vector2(32, 32), Vector2(1.0f, 1.0f), b_mAngle, 255);
	}
	if(b_mType == Type::SUB_PLAYER)
	{
	
		b_mAngle = 0.0f;
		renderer->draw2D("enemy", Vector2(b_mPosittion.x, b_mPosittion.y), Vector2(0, 0), Vector2(64, 64), Vector2(32, 32), Vector2(1.0f, 1.0f), b_mAngle, b_mArpha);
		
	}

	if (b_mType == Type::ITEM)
	{
		DrawCircle(b_mPosittion.x + 64 / 2, b_mPosittion.y + 64 / 2, b_mCircleSize, GetColor(0, 255, 0), FALSE);
		renderer->draw2D("enemy", Vector2(b_mPosittion.x, b_mPosittion.y), Vector2(0, 0), Vector2(64, 64), Vector2(32, 32), Vector2(1.0f, 1.0f), b_mAngle, b_mArpha);
	}

}

void PlatoonEnemy::hit(BaseObject & other)
{
	if (other.getType() == Type::PLAYER_BULLET&&b_mType == Type::ENEMY)
	{
		b_mHp -= 1;
		DrawCircle(b_mPosittion.x + 64 / 2, b_mPosittion.y + 64 / 2, b_mCircleSize, GetColor(255, 255, 0), TRUE);
	}


	if (other.getType() == Type::ENEMY_BULLET&&b_mType == Type::PLAYER)
	{
		b_mHp -= 1;
		DrawCircle(b_mPosittion.x + 64 / 2, b_mPosittion.y + 64 / 2, b_mCircleSize, GetColor(255, 255, 0), TRUE);
		
	}

	if (other.getType() == Type::ENEMY&&b_mType == Type::PLAYER)
	{
		b_mHp -= 1;
		DrawCircle(b_mPosittion.x + 64 / 2, b_mPosittion.y + 64 / 2, b_mCircleSize, GetColor(255, 255, 0), TRUE);
		
	}


	if (other.getType() == Type::PLAYER&&b_mType == Type::ITEM)
	{
		//最初は控えに
		b_mType = Type::SUB_PLAYER;
	}
}

void PlatoonEnemy::Shot(Vector2 pos, float angle)
{
	charaManager->add(new Bullet(pos, charaManager, b_mType,0.0f));
}

void PlatoonEnemy::SubShot(Vector2 pos, float angle)
{
	if (b_mType == Type::ENEMY)
	{
		charaManager->add(new AngleBullet(pos, charaManager, b_mType, angle1 + angle));
		charaManager->add(new AngleBullet(pos, charaManager, b_mType, angle2 + angle));
		charaManager->add(new AngleBullet(pos, charaManager, b_mType, angle3 + angle));
	}
	else
	{
		charaManager->add(new AngleBullet(pos, charaManager, b_mType, angle1 + angle));
		charaManager->add(new AngleBullet(pos, charaManager, b_mType, angle2 + angle));
		charaManager->add(new AngleBullet(pos, charaManager, b_mType, angle3 + angle));
	}
}


void PlatoonEnemy::Jibaku(Vector2 pos)
{
	charaManager->add(new Bom(pos, charaManager));
	b_mIsDeath = true;
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