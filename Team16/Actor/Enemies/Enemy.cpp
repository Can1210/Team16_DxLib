#include "Enemy.h"
#include <random>
#include "../Bulletes/Bullet.h"
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
	b_mHp = 3;
	b_mCircleSize = 16.0f;
	b_mType = Type::ENEMY;
	b_mAngle = 180.0f;
	b_mSpeed = 70.0f;
	b_mArpha = 255;
	mTimer->initialize();
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
		charaManager->add(new Item(b_mPosittion, BulletType::T_Bullet, "enemy"));   //�A�C�e������
		b_mIsDeath = true;
	}
	if (b_mPosittion.y > WindowInfo::WindowHeight
		|| b_mPosittion.x > WindowInfo::WindowWidth
		|| b_mPosittion.x < 0)
	{
		b_mIsDeath = true;
	}
	b_mPosittion += b_mVelocity * b_mSpeed * deltaTime;
}

void Enemy::draw(Renderer * renderer, Renderer3D* renderer3D)
{
	DrawCircle((int)(b_mPosittion.x + 64 / 2), (int)(b_mPosittion.y + 64 / 2), (int)b_mCircleSize, GetColor(255, 0, 0), FALSE);
	renderer->draw2D("enemy", Vector2(b_mPosittion.x, b_mPosittion.y), Vector2(0, 0), Vector2(64, 64), Vector2(32, 32), Vector2(1.3f, 1.3f), b_mAngle, 255);
}

void Enemy::hit(BaseObject & other)
{
	if (other.getType() == Type::PLAYER_BULLET&&b_mType == Type::ENEMY)
	{
		b_mHp -= 1;
		DrawCircle((int)(b_mPosittion.x + 64 / 2), (int)(b_mPosittion.y + 64 / 2), (int)b_mCircleSize, GetColor(255, 255, 0), TRUE);
	}
}

void Enemy::Shot(Vector2 pos)
{
	charaManager->add(new Bullet(pos, charaManager, b_mType,0.0f));
}
