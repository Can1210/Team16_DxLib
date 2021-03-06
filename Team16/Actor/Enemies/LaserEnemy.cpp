#include "LaserEnemy.h"
#include <random>
#include <stdio.h>
#include <stdarg.h>
#include "../Bulletes/LaserBullet.h"
#include "../Item/Item.h"

LaserEnemy::LaserEnemy(Vector2 pos, CharactorManager *c, Vector2 end) : mTimer(new Timer()), mTimerDamege(new Timer())
{
	charaManager = c;
	b_mPosittion = pos;
	this->start = pos;
	this->end = end;
}

LaserEnemy::~LaserEnemy()
{
	delete mTimer;
	delete mTimerDamege;
}

void LaserEnemy::initialize()
{
	b_mHp = 3;
	b_mCircleSize = 16.0f;
	b_mType = Type::ENEMY;
	b_mAngle = 180.0f;
	b_mArpha = 255;
	b_mSpeed = 100.0f;
	mTimer->initialize();
	mTimerDamege->initialize();
	mDamageHit = 255;
	laserY = 30.0f;
	b_animCnt = 0.0f;
	hitSoundTime = 20;
	isBom = false;    //ボムで死んだか
}

void LaserEnemy::update(float deltaTime)
{
	mTimer->update(deltaTime);
	b_mVelocity = Vector2(0, 0);
	
	b_mVelocity += Traking() * 1.0f;
	if (laserY > 60.0f * 1.0f)
	{
		shot(Vector2(b_mPosittion.x, b_mPosittion.y), 0.0f);
		if (laserY > 60.0f * 2.0f)
			laserY = 0.0f;
	}
	hitSoundTime++;
	laserY++;
	b_mPosittion += b_mVelocity * b_mSpeed * deltaTime;
}

void LaserEnemy::draw(Renderer * renderer, Renderer3D* renderer3D)
{
	//renderer->draw2D("enemy", Vector2(b_mPosittion.x, b_mPosittion.y), Vector2(0, 0), Vector2(64, 64), Vector2(32, 32), Vector2(1.0f, 1.0f), b_mAngle, 255);
	renderer3D->draw3DTexture("enemyG", Vector3(b_mPosittion.x, b_mPosittion.y, 0.0f), Vector2(0.0f, 0.0f), Vector2(64.0f, 64.0f), 96.0f, b_mAngle, 255, Vector2(0.5f, 0.5f), Vector3((float)255, (float)mDamageHit, (float)mDamageHit));
	if (b_mHp <= 0)
	{
		b_animCnt += 64.0f;
		if (b_animCnt >= 1022.0f)
		{
			Score::getInstance().addScore(100);
			if (GetRand(2) == 2)
			{
				charaManager->add(new Item(b_mPosittion, BulletType::T_LaserBullet, "enemy"));   //アイテム生成
				b_mIsDeath = true;
			}
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

void LaserEnemy::hit(BaseObject & other)
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
void LaserEnemy::shot(Vector2 pos, float angle)
{
	if (hitSoundTime > 20)
	{
		charaManager->add(new LaserBullet(b_mPosittion, charaManager, b_mType, -90.0f + angle));
		hitSoundTime = 0;
	}
	else 
	{
		charaManager->add(new LaserBullet(b_mPosittion, charaManager, b_mType, -90.0f + angle,false));
	}
}
Vector2 LaserEnemy::Traking()
{
	Vector2 v = Vector2(0, 0);
	v = start - end;
	v = -v.normalize();
	return v;
}