#include "HomingEnemy.h"
#include <random>
#include <stdio.h>
#include <stdarg.h>
#include "../Bulletes/TrakingBullet.h"
#include "../Item/Item.h"


HomingEnemy::HomingEnemy(Vector2 pos, CharactorManager *c, float angle1, float angle2, float angle3, Vector2 end) : mTimer(new Timer())
{
	charaManager = c;
	b_mPosittion = pos;
	this->angle1 = angle1;
	this->angle2 = angle2;
	this->angle3 = angle3;
	this->start = pos;
	this->end = end;
}

HomingEnemy::~HomingEnemy()
{
	delete mTimer;
}

void HomingEnemy::initialize()
{
	b_mHp = 3;
	b_mCircleSize = 16.0f;
	b_mType = Type::ENEMY;
	b_mAngle = 180.0f;
	b_mArpha = 255;
	b_mSpeed = 70.0f;
	mTimer->initialize();
}

void HomingEnemy::update(float deltaTime)
{
	mTimer->update(deltaTime);
	b_mVelocity = Vector2(0, 0);
	b_mVelocity += Traking() * 2.0f;
	if (mTimer->timerSet(2)) shot(Vector2(b_mPosittion.x, b_mPosittion.y), 0.0f);

	if (b_mPosittion.y > WindowInfo::WindowHeight
		|| b_mPosittion.x > WindowInfo::WindowWidth
		|| b_mPosittion.x < 0
		)
	{
		b_mIsDeath = true;
	}
	if (b_mHp <= 0)
	{
		Score::getInstance().addScore(100);
		charaManager->add(new Item(b_mPosittion, BulletType::T_TrakingBullet, "enemy"));   //ƒAƒCƒeƒ€¶¬
		b_mIsDeath = true;
	}
	b_mPosittion += b_mVelocity * b_mSpeed * deltaTime;
}

void HomingEnemy::draw(Renderer * renderer, Renderer3D* renderer3D)
{
	DrawCircle((int)(b_mPosittion.x + 64 / 2), (int)(b_mPosittion.y + 64 / 2), (int)b_mCircleSize, GetColor(255, 0, 0), FALSE);
	renderer->draw2D("enemy", Vector2(b_mPosittion.x, b_mPosittion.y), Vector2(0, 0), Vector2(64, 64), Vector2(32, 32), Vector2(1.0f, 1.0f), b_mAngle, 255);
}

void HomingEnemy::hit(BaseObject & other)
{
	if (other.getType() == Type::PLAYER_BULLET)
	{
		b_mHp -= 1;
		DrawCircle((int)(b_mPosittion.x + 64 / 2), (int)(b_mPosittion.y + 64 / 2), (int)b_mCircleSize, GetColor(255, 255, 0), TRUE);
	}
}

void HomingEnemy::shot(Vector2 pos, float angle)
{
	charaManager->add(new TrakingBullet(pos, charaManager, b_mType, angle2 + angle));
}

Vector2 HomingEnemy::Traking()
{
	Vector2 v = Vector2(0, 0);
	v = start - end;
	v = -v.normalize();
	return v;
}

