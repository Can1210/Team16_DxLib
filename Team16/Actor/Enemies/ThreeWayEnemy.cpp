#include "ThreeWayEnemy.h"
#include <random>
#include <stdio.h>
#include <stdarg.h>
#include "../Bulletes/AngleBullet.h"
#include "../Bulletes/Bullet.h"
#include "../Item/Item.h"

ThreeWayEnemy::ThreeWayEnemy(Vector2 pos, CharactorManager *c, float angle1, float angle2, float angle3,Vector2 end) : mTimer(new Timer()), mTimerDamege(new Timer())
{
	charaManager = c;
	b_mPosittion = pos;
	this->angle1 = angle1;
	this->angle2 = angle2;
	this->angle3 = angle3;
	this->start = pos;
	this->end = end;
}

ThreeWayEnemy::~ThreeWayEnemy()
{
	delete mTimer;
	delete mTimerDamege;
}
void ThreeWayEnemy::initialize()
{
	b_mHp = 3;
	b_mCircleSize = 16.0f;
	b_mType = Type::ENEMY;
	b_mAngle = 180.0f;
	b_mArpha = 255;
	b_mSpeed = 70.0f;
	mTimer->initialize();
	mTimerDamege->initialize();
	mDamageHit = 255;
	b_animCnt = 0.0f;
	isBom = false;    //ボムで死んだか
}

void ThreeWayEnemy::update(float deltaTime)
{
	mTimer->update(deltaTime);
	mTimerDamege->update(deltaTime);
	if (mTimerDamege->timerSet_Self(0.2f))
	{
		mDamageHit = 255;
	}
	b_mVelocity = Vector2(0, 0);
	b_mVelocity += Traking() * 2.0f;
	if (mTimer->timerSet(2))
	{
		shot(Vector2(b_mPosittion.x, b_mPosittion.y), 0.0f);
	}

	if (b_mHp <= 0)
	{
		Score::getInstance().addScore(100);
		charaManager->add(new Item(b_mPosittion, BulletType::T_Bullet, "enemy"));   //ƒAƒCƒeƒ€¶¬
		b_mIsDeath = true;
	}
	b_mPosittion -= b_mVelocity * b_mSpeed * deltaTime;
}

void ThreeWayEnemy::draw(Renderer * renderer, Renderer3D* renderer3D)
{
	//renderer->draw2D("enemy", Vector2(b_mPosittion.x, b_mPosittion.y), Vector2(0, 0), Vector2(64, 64), Vector2(32, 32), Vector2(1.0f, 1.0f), b_mAngle, 255);
	renderer3D->draw3DTexture("enemyG2", Vector3(b_mPosittion.x, b_mPosittion.y, 0.0f), Vector2(0.0f, 0.0f), Vector2(64.0f, 64.0f), 96.0f, b_mAngle, 255, Vector2(0.5f, 0.5f), Vector3((float)255, (float)mDamageHit, (float)mDamageHit));
	if (b_mHp <= 0)
	{
		b_animCnt += 64.0f;
	
		if (b_animCnt >= 1022.0f)
		{
			Score::getInstance().addScore(100);

			charaManager->add(new Item(b_mPosittion, BulletType::T_AngleBullet, "enemy"));  
			b_mIsDeath = true;
		}
		renderer3D->draw3DTexture("deathBurst", Vector3(b_mPosittion.x, b_mPosittion.y, 0.0f), Vector2(b_animCnt, 0.0f), Vector2(64.0f, 64.0f), 140.0f, b_mAngle);
	}
	//ボムに触れたら死亡
	if (isBom)
	{
		b_animCnt += 64.0f;

		if (b_animCnt >= 1022.0f)
		{
			Score::getInstance().addScore(100);

			b_mIsDeath = true;
		}
		renderer3D->draw3DTexture("deathBurst", Vector3(b_mPosittion.x, b_mPosittion.y, 0.0f), Vector2(b_animCnt, 0.0f), Vector2(64.0f, 64.0f), 140.0f, b_mAngle);
	}
}

void ThreeWayEnemy::hit(BaseObject & other)
{
	if (other.getType() == Type::PLAYER_BULLET)
	{
		mDamageHit = 0;
		mTimerDamege->initialize();
		b_mHp -= charaManager->getPlayerBulletDamage();
	}
	//相手がボムなら
	if (other.getType() == Type::BOM)
	{
		isBom = true;
	}
}

void ThreeWayEnemy::shot(Vector2 pos, float angle)
{
	charaManager->add(new AngleBullet(pos, charaManager, b_mType, angle1 + angle));
	charaManager->add(new AngleBullet(pos, charaManager, b_mType, angle2 + angle));
	charaManager->add(new AngleBullet(pos, charaManager, b_mType, angle3 + angle));
}

Vector2 ThreeWayEnemy::Traking()
{
	Vector2 v = Vector2(0, 0);
	v = start - end;
	v = -v.normalize();
	return v;
}

