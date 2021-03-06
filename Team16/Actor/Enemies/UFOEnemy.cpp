#include "UFOEnemy.h"
#include <random>
#include <stdio.h>
#include <stdarg.h>
#include "../Bulletes/AngleBullet.h"
#include "../Item/Item.h"

UFOEnemy::UFOEnemy(Vector2 pos, CharactorManager *c) : mTimer(new Timer()), mTimerDamege(new Timer())
{
	charaManager = c;
	b_mPosittion = pos;
}

UFOEnemy::~UFOEnemy()
{
	delete mTimer;
	delete mTimerDamege;
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
	mTimerDamege->initialize();
	mDamageHit = 255;
	time = 0.0f;
	down = false;
	subShotcnt = 20;
	b_animCnt = 0.0f;
	isBom = false;    //ボムで死んだか
}

void UFOEnemy::update(float deltaTime)
{
	mTimer->update(deltaTime);
	mTimerDamege->update(deltaTime);
	if (mTimerDamege->timerSet_Self(0.2f))
	{
		mDamageHit = 255;
	}
	b_mVelocity = Vector2(0, 0);
	time++;

	float x = sin(time / 40.0f) * 2.0f;
	b_mVelocity = Vector2(x, 0.7f);
	if (mTimer->timerSet(1))
	{
		Shot(Vector2(b_mPosittion.x, b_mPosittion.y-64.0f), -90.0f+b_mAngle);
	}
	if (b_mHp <= 0)
	{
		Score::getInstance().addScore(100);
		charaManager->add(new Item(b_mPosittion, BulletType::T_Bullet, "enemy"));   //ƒAƒCƒeƒ€¶¬
		b_mIsDeath = true;
	}
	b_mPosittion -= b_mVelocity * b_mSpeed * deltaTime;
}

void UFOEnemy::draw(Renderer * renderer, Renderer3D* renderer3D)
{
	//renderer->draw2D("enemy", Vector2(b_mPosittion.x, b_mPosittion.y), Vector2(0, 0), Vector2(64, 64), Vector2(32, 32), Vector2(2.0f, 2.0f), b_mAngle, 255);
	renderer3D->draw3DTexture("enemyG", Vector3(b_mPosittion.x, b_mPosittion.y, 0.0f), Vector2(0.0f, 0.0f), Vector2(64.0f, 64.0f), 96.0f, b_mAngle, 255, Vector2(0.5f, 0.5f), Vector3((float)255, (float)mDamageHit, (float)mDamageHit));
	if (b_animCnt <= 0)
	{
		b_animCnt += 64.0f;
		renderer3D->draw3DTexture("1000", Vector3(b_mPosittion.x, b_mPosittion.y + 50.0f, 0.0f), Vector2(0.0f, 0.0f), Vector2(64.0f, 64.0f), 96.0f, 0.0f);
		if (b_animCnt >= 1022.0f)
		{
			Score::getInstance().addScore(1000);
			charaManager->add(new Item(b_mPosittion, BulletType::T_AngleBullet, "enemy"));
			b_mIsDeath = true;
		}
		renderer3D->draw3DTexture("deathBurst", Vector3(b_mPosittion.x, b_mPosittion.y, 0.0f), Vector2(b_animCnt, 0.0f), Vector2(64.0f, 64.0f), 140.0f, b_mAngle);
	}
	//ボムに触れたら死亡
	if (isBom)
	{
		b_animCnt += 64.0f;
    renderer3D->draw3DTexture("1000", Vector3(b_mPosittion.x, b_mPosittion.y + 50.0f, 0.0f), Vector2(0.0f, 0.0f), Vector2(64.0f, 64.0f), 96.0f, 0.0f);
		if (b_animCnt >= 1022.0f)
		{
			Score::getInstance().addScore(1000);
			b_mIsDeath = true;
		}
		renderer3D->draw3DTexture("deathBurst", Vector3(b_mPosittion.x, b_mPosittion.y, 0.0f), Vector2(b_animCnt, 0.0f), Vector2(64.0f, 64.0f), 140.0f, b_mAngle);
	}
}

void UFOEnemy::hit(BaseObject & other)
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

void UFOEnemy::Shot(Vector2 pos, float angle)
{	
	Vector2 vv = Vector2(pos.x + 25.0f,pos.y + 55.0f);
	Vector2 v = Vector2(pos.x + 25.0f - 20.0f, pos.y + 55.0f); Vector2 v1 = Vector2(pos.x + 25.0f + 20.0f, pos.y + 55.0f);
	charaManager->add(new AngleBullet(v, charaManager, b_mType,  angle));
	charaManager->add(new AngleBullet(vv, charaManager, b_mType,  angle));
	charaManager->add(new AngleBullet(v1, charaManager, b_mType,  angle));
}