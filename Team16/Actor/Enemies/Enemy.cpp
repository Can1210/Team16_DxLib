#include "Enemy.h"
#include <random>
#include "../Bulletes/Bullet.h"
#include "../Bulletes/AngleBullet.h"
#include "../Item/Item.h"

Enemy::Enemy(Vector2 pos, CharactorManager *c) :mTimer(new Timer())
{
	charaManager = c;
	b_mPosittion = pos;
}

Enemy::~Enemy()
{
	delete mTimer;
}
void Enemy::initialize()
{
	b_mVelocity = checkPlayerPos(b_mVelocity);
	b_mHp = 3;
	b_mCircleSize = 16.0f;
	b_mType = Type::ENEMY;
	b_mAngle = 180.0f;
	b_mSpeed = 70.0f;
	b_mArpha = 255;
	mTimer->initialize();
	b_animCnt = 0.0f;
}

void Enemy::update(float deltaTime)
{
	mTimer->update(deltaTime);
	b_mVelocity = Vector2(0, 0);

	b_mVelocity.y += 2;
	
	if (mTimer->timerSet(2))
	{
		Shot(Vector2(b_mPosittion.x, b_mPosittion.y));
	}
	if (b_mHp <= 0)
	{
		Score::getInstance().addScore(100);
		charaManager->add(new Item(b_mPosittion, BulletType::T_Bullet, "enemy")); 
		b_mIsDeath = true;
	}

	b_mPosittion -= b_mVelocity * b_mSpeed * deltaTime;
}

void Enemy::draw(Renderer * renderer, Renderer3D* renderer3D)
{
	renderer3D->draw3DTexture("enemy", Vector3(b_mPosittion.x, b_mPosittion.y, 0.0f), Vector2(0.0f, 0.0f), Vector2(64.0f, 64.0f), 96.0f, b_mAngle);
	if (b_mHp<=0)
	{
		b_animCnt +=64.0f;
		if (b_animCnt>=1022.0f)
		{
			Score::getInstance().addScore(100);
			charaManager->add(new Item(b_mPosittion, BulletType::T_Bullet, "enemy"));   //�A�C�e������
			b_mIsDeath = true;
		}
 		renderer3D->draw3DTexture("deathBurst", Vector3(b_mPosittion.x, b_mPosittion.y, 0.0f), Vector2(b_animCnt, 0.0f), Vector2(64.0f, 64.0f), 160.0f, b_mAngle);
	}
	//renderer->draw2D("enemy", Vector2(b_mPosittion.x, b_mPosittion.y), Vector2(0, 0), Vector2(64, 64), Vector2(32, 32), Vector2(1.3f, 1.3f), b_mAngle, 255);
	
}

void Enemy::hit(BaseObject & other)
{
	if (other.getType() == Type::PLAYER_BULLET&&b_mType == Type::ENEMY)
	{
		b_mHp -= charaManager->getPlayerBulletDamage();
	}
}

void Enemy::Shot(Vector2 pos)
{
	Vector2 angleVec = Vector2(0, 0);
	angleVec = checkPlayerPos(angleVec);  //角度を代入
	//角度に変換
	float angle = atan2(-angleVec.y, angleVec.x)* 180.0f / DX_PI_F;
	charaManager->add(new AngleBullet(Vector2(b_mPosittion.x, b_mPosittion.y) + Vector2(32, 32), charaManager, b_mType, angle));
}

Vector2 Enemy::checkPlayerPos(Vector2 vec)
{
	//プレイヤーの位置を入れる
	Vector2 playerPos = charaManager->getPlayerPosition();
	Vector2 playerVec = playerPos - b_mPosittion;  //プレイヤーとの差分
	return playerVec.normalize();
}
