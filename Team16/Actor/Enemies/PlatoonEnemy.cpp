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

bool PlatoonEnemy::PlayerNull()//プレイヤーがいるか？
{
	for (auto object : charaManager->getUseList())
	{
		if (object->getType() == Type::PLAYER)
		{
			return true;
		}
	}
	return false;
}

void PlatoonEnemy::SubChange()
{
	b_mPosittion = KakoPos;
	b_mType = Type::PLAYER;
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
	shotcnt = 0;
	subShotCnt = 20;
	r = 0;
	b = 255;
	b_mSpeed = 70.0f;
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
		if (!PlayerNull())
		{
			SubChange();
		}
		KakoPos = b_mPosittion;
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

		//if (s1)
		//{
		//	int index = enemyTime - frame20 % 600;
		//	if (index < 0){index = 600 - index;}
		//	Vector2 v2 = vec_Array(index);
		//	s1->SetParentPos(v2);
		//}
		//if (s2)
		//{
		//	int index = enemyTime - frame40 % 600;
		//	if (index < 0) { index = 600 - index; }
		//	Vector2 v2 = vec_Array(index);
		//	s2->SetParentPos(v2);
		//}
		//if (s3)
		//{
		//	int index = enemyTime - frame60 % 600;
		//	if (index < 0) { index = 600 - index; }
		//	Vector2 v2 = vec_Array(index);
		//	s3->SetParentPos(v2);
		//}
		//if (s4)
		//{
		//	int index = enemyTime - frame80 % 600;
		//	if (index < 0) { index = 600 - index; }
		//	Vector2 v2 = vec_Array(index);
		//	s4->SetParentPos(v2);
		//}
		//if (s5)
		//{
		//	int index = enemyTime - frame100 % 600;
		//	if (index < 0) { index = 600 - index; }
		//	Vector2 v2 = vec_Array(index);
		//	s5->SetParentPos(v2);
		//}

		b_mVelocity = Vector2(x,y);

		if (mTimer->timerSet(2))
		{
			SubShot(Vector2(b_mPosittion.x, b_mPosittion.y), 0.0f);
		}
		if (b_mPosittion.y > WindowInfo::WindowHeight
			|| b_mPosittion.x > WindowInfo::WindowWidth
			|| b_mPosittion.x < 0
			|| b_mHp <= 0)
		{
			b_mIsDeath = true;
		}
	}
	enemyTime++;

	//if (enemyTime % frame20 == 0 && !childs)
	//{
	//	s1 = new SoldierEnemy(vec_Array(enemyTime), charaManager);
	//	charaManager->add(s1);
	//}
	//if (enemyTime % frame40 == 0 && !childs)
	//{
	//	s2 = new SoldierEnemy(vec_Array(enemyTime), charaManager);
	//	charaManager->add(s2);
	//}
	//if (enemyTime % frame60 == 0 && !childs)
	//{
	//	s3 = new SoldierEnemy(vec_Array(enemyTime), charaManager);
	//	charaManager->add(s3);
	//}
	//if (enemyTime % frame80 == 0 && !childs)
	//{
	//	s4 = new SoldierEnemy(vec_Array(enemyTime), charaManager);
	//	charaManager->add(s4);
	//}
	//if (enemyTime % frame100 == 0 && !childs)
	//{
	//	childs = true;
	//	s5 = new SoldierEnemy(vec_Array(enemyTime), charaManager);
	//	charaManager->add(s5);
	//}
	if (enemyTime > arraySize)
		enemyTime = 0.0f;
	//乗っ取り後
	if (b_mType == Type::PLAYER && !b_mEndFlag)
	{
		if (input->isKeyState(KEYCORD::ARROW_UP))
		{
			b_mVelocity.y -= 4;
		}
		if (input->isKeyState(KEYCORD::ARROW_DOWN))
		{
			b_mVelocity.y += 4;
		}
		if (input->isKeyState(KEYCORD::ARROW_RIGHT))
		{
			b_mVelocity.x += 4;
		}
		if (input->isKeyState(KEYCORD::ARROW_LEFT))
		{
			b_mVelocity.x -= 4;
		}
		if (input->isKeyDown(KEYCORD::SPACE))
		{
			Shot(Vector2(b_mPosittion.x, b_mPosittion.y), 180.0f);
		}
		if (input->isKeyState(KEYCORD::SPACE))
		{
			if (subShotCnt > 20)
			{
				SubShot(Vector2(b_mPosittion.x, b_mPosittion.y), 180.0f);
				subShotCnt = 0;
			}
			b_mSpeed = 35.0f;
		}
		else
		{
			b_mSpeed = 70.0f;
		}
		if (input->isKeyState(KEYCORD::V))
		{
			shotcnt++;
			if (shotcnt > 100)
			{
				shotcnt = 100;
			}
		}

		if (shotcnt == 100 && input->isKeyUp(KEYCORD::V))
		{
			CShot(Vector2(b_mPosittion.x, b_mPosittion.y));
			
		}
		if (input->isKeyDown(KEYCORD::C))
		{
			Jibaku(Vector2(b_mPosittion.x, b_mPosittion.y));
		}
		if (b_mHp <= 0)
		{
			b_mEndFlag = true;
		}
		b_mPosittion += b_mVelocity*deltaTime *b_mSpeed;
	}
	b_mPosittion += b_mVelocity;
}

void PlatoonEnemy::draw(Renderer * renderer, Renderer3D* renderer3D)
{
	if (b_mType == Type::ENEMY)
	{
		DrawCircle(b_mPosittion.x + 64 / 2, b_mPosittion.y + 64 / 2, b_mCircleSize, GetColor(255, 0, 0), FALSE);
		renderer->draw2D("enemy", Vector2(b_mPosittion.x, b_mPosittion.y), Vector2(0, 0), Vector2(64, 64), Vector2(32, 32), Vector2(1.0f, 1.0f), b_mAngle, 255);
	}
	else if (!b_mEndFlag)
	{
		if (DamgeFlag)
		{
			b_mArpha = 155;
		}
		else
		{
			b_mArpha = 255;
		}

		//ゲージ
		DrawBox(0, 0, shotcnt, 100, GetColor(r, 0, b), TRUE);
		if (shotcnt == 100)
		{
			r = 255;
			b = 0;
		}

		DrawCircle(b_mPosittion.x + 64 / 2, b_mPosittion.y + 64 / 2, b_mCircleSize, GetColor(0, 0, 255), FALSE);
		b_mAngle = 0.0f;
		renderer->draw2D("enemy", Vector2(b_mPosittion.x, b_mPosittion.y), Vector2(0, 0), Vector2(64, 64), Vector2(32, 32), Vector2(1.0f, 1.0f), b_mAngle, b_mArpha);
		if (b_mType == Type::PLAYER)
		{
			renderer->drawNumber("hpNumber", Vector2(150, 10), b_mHp, 0, Vector2(0, 0), Vector2(1, 1), 0.0f, 255);
		}

	}

	if (b_mEndFlag)
	{
		renderer->drawText("Font", "GAMEOVER", Vector2(100, 450), Vector2(0, 0), Vector2(1, 1), 0.0f, 255);
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
		mTimer->initialize();
		DamgeFlag = TRUE;
	}

	if (other.getType() == Type::ENEMY&&b_mType == Type::PLAYER)
	{
		b_mHp -= 1;
		DrawCircle(b_mPosittion.x + 64 / 2, b_mPosittion.y + 64 / 2, b_mCircleSize, GetColor(255, 255, 0), TRUE);
		mTimer->initialize();
		DamgeFlag = TRUE;
	}


	if (other.getType() == Type::CHANGE_BULLET&&b_mType == Type::ENEMY)
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

void PlatoonEnemy::CShot(Vector2 pos)
{
	charaManager->add(new ChangeBullet(pos, charaManager));
	shotcnt = 0;
	r = 0;
	b = 255;
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