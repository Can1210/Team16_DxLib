#include "SoldierEnemy.h"
#include <random>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h> // rand, srandä÷êî
#include <time.h>   // timeä÷êî
#include "../Bulletes/AngleBullet.h"
#include "../Item/Item.h"

SoldierEnemy::SoldierEnemy(Vector2 pos, CharactorManager *c) : mTimer(new Timer()), mTimerDamege(new Timer())
{
	charaManager = c;
	b_mPosittion = pos;
}

SoldierEnemy::~SoldierEnemy()
{
	delete mTimer;
	delete mTimerDamege;
}

void SoldierEnemy::initialize()
{
	b_mHp = 3;
	b_mCircleSize = 16.0f;
	b_mType = Type::ENEMY;
	b_mAngle = 180.0f;
	b_mArpha = 255;
	b_mVelocity = Vector2(0, -2.0f);
	b_mSpeed = 70.0f;
	mTimer->initialize();
	mTimerDamege->initialize();
	mDamageHit = 255;
}

void SoldierEnemy::update(float deltaTime)
{
	mTimer->update(deltaTime);
	mTimerDamege->update(deltaTime);
	if (mTimerDamege->timerSet_Self(0.2f))
	{
		mDamageHit = 255;
	}
	if (mTimer->timerSet(2))
	{
		Shot(Vector2(b_mPosittion.x, b_mPosittion.y));
	}

	if (b_mHp <= 0)
	{
		Score::getInstance().addScore(100);
		charaManager->add(new Item(b_mPosittion, BulletType::T_Bullet, "enemy"));   //ÉAÉCÉeÉÄê∂ê¨
		b_mIsDeath = true;
	}
	
	b_mPosittion -= b_mVelocity * b_mSpeed * deltaTime;
}

void SoldierEnemy::draw(Renderer * renderer, Renderer3D* renderer3D)
{
	//renderer->draw2D("enemy", Vector2(b_mPosittion.x, b_mPosittion.y), Vector2(0, 0), Vector2(64, 64), Vector2(32, 32), Vector2(1.0f, 1.0f), b_mAngle, 255);
	renderer3D->draw3DTexture("enemy", Vector3(b_mPosittion.x, b_mPosittion.y, 0.0f), Vector2(0.0f, 0.0f), Vector2(64.0f, 64.0f), 96.0f, b_mAngle, 255, Vector2(0.5f, 0.5f), Vector3((float)255, (float)mDamageHit, (float)mDamageHit));
}

void SoldierEnemy::hit(BaseObject & other)
{
	if (other.getType() == Type::PLAYER_BULLET)
	{
		mDamageHit = 0;
		mTimerDamege->initialize();
		b_mHp -= charaManager->getPlayerBulletDamage();
	}
}

void SoldierEnemy::SetParentPos(Vector2 v)
{
	b_mPosittion = v;
}

void SoldierEnemy::Shot(Vector2 pos)
{
	charaManager->add(new AngleBullet(pos, charaManager, b_mType,270));
}