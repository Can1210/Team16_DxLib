#include "UFOEnemy.h"
#include <random>
#include <stdio.h>
#include <stdarg.h>
#include "../Bulletes/AngleBullet.h"
#include "../Item/Item.h"

UFOEnemy::UFOEnemy(Vector2 pos, CharactorManager *c, float angle1, float angle2, float angle3, Vector2 end) : mTimer(new Timer())
{
	charaManager = c;
	b_mPosittion = pos;
	this->angle1 = angle1;
	this->angle2 = angle2;
	this->angle3 = angle3;
	this->start = pos;
	this->end = end;
}

UFOEnemy::~UFOEnemy()
{
	delete mTimer;
}
void UFOEnemy::initialize()
{
	b_mHp = 3;
	b_mCircleSize = 16.0f;
	b_mType = Type::ENEMY;
	b_mArpha = 255;
	b_mAngle = 180.0f;
	b_mSpeed = 100.0f;
	mTimer->initialize();
	time = 0.0f;
	down = false;
	subShotcnt = 20;
}

void UFOEnemy::update(float deltaTime)
{
	mTimer->update(deltaTime);
	b_mVelocity = Vector2(0, 0);
	/*b_mVelocity += Traking() * 2.0f;*/
		//b_mVelocity = Vector2(sin(300.0f), -1.0f);
	time++;

	float x = sin(time / 40.0f) * 2.0f;
	b_mVelocity = Vector2(x, 0.7f);
	if (mTimer->timerSet(1))
	{
		Shot(Vector2(b_mPosittion.x, b_mPosittion.y), 0.0f);
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
		charaManager->add(new Item(b_mPosittion, BulletType::T_AngleBullet, "enemy"));   //アイテム生成
		b_mIsDeath = true;
	}
	b_mPosittion += b_mVelocity * b_mSpeed * deltaTime;
}

void UFOEnemy::draw(Renderer * renderer, Renderer3D* renderer3D)
{
	DrawCircle((int)(b_mPosittion.x + 64 / 2),(int)( b_mPosittion.y + 64 / 2), (int)b_mCircleSize, GetColor(255, 0, 0), FALSE);
	renderer->draw2D("enemy", Vector2(b_mPosittion.x, b_mPosittion.y), Vector2(0, 0), Vector2(64, 64), Vector2(32, 32), Vector2(2.0f, 2.0f), b_mAngle, 255);
}

void UFOEnemy::hit(BaseObject & other)
{
	if (other.getType() == Type::PLAYER_BULLET)
	{
		b_mHp -= 1;
		DrawCircle((int)(b_mPosittion.x + 64 / 2), (int)(b_mPosittion.y + 64 / 2),(int)b_mCircleSize, GetColor(255, 255, 0), TRUE);
	}
}

void UFOEnemy::Shot(Vector2 pos, float angle)
{	//左
	//charaManager->add(new AngleBullet(pos, charaManager, b_mType, angle1 + angle));
	//真ん中
	Vector2 vv = Vector2(pos.x + 25.0f,pos.y + 55.0f);
	Vector2 v = Vector2(pos.x + 25.0f - 20.0f, pos.y + 55.0f); Vector2 v1 = Vector2(pos.x + 25.0f + 20.0f, pos.y + 55.0f);
	charaManager->add(new AngleBullet(v, charaManager, b_mType, angle2 + angle));
	charaManager->add(new AngleBullet(vv, charaManager, b_mType, angle2 + angle));
	charaManager->add(new AngleBullet(v1, charaManager, b_mType, angle2 + angle));
	//右
	//charaManager->add(new AngleBullet(pos, charaManager, b_mType, angle3 + angle));
}

Vector2 UFOEnemy::Traking()
{
	Vector2 v = Vector2(0, 0);
	v = start - end;
	v = -v.normalize();
	return v;
}

