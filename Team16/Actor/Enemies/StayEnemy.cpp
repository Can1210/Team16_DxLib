#include <random>
#include"StayEnemy.h"
#include "../Bulletes/Bullet.h"
#include "../Bulletes/AngleBullet.h"
#include "../Item/Item.h"

StayEnemy::StayEnemy(Vector2 pos, CharactorManager *c) :mTimer(new Timer()),m_inTimer(new Timer())
{
	charaManager = c;
	b_mPosittion = pos;
}

StayEnemy::~StayEnemy()
{
	delete mTimer;
	delete m_inTimer;
}
void StayEnemy::initialize()
{
	b_mVelocity = checkPlayerPos(b_mVelocity);
	b_mHp = 30;
	b_mCircleSize = 32.0f;
	b_mType = Type::ENEMY;
	b_mAngle = 180.0f;
	b_mSpeed = 60.0f;
	b_mArpha = 255;
	ShotAngle = 180.0;
	mTimer->initialize();
	m_inTimer->initialize();
	b_animCnt = 0.0f;
	modeChange = false;
}

void StayEnemy::update(float deltaTime)
{
	mTimer->update(deltaTime);
	m_inTimer->update(deltaTime);
	b_mVelocity = Vector2(0, 0);
	Vector2 angleVec = Vector2(0, 0);
	angleVec = checkPlayerPos(angleVec);  //角度を代入
	//角度に変換

	float angle = atan2(-angleVec.y, angleVec.x)* 180.0f / DX_PI_F;
	ShotAngle = angle;
	if (m_inTimer->timerSet(2))
	{
		modeChange = true;
	}
	switch (modeChange)
	{
	case true:
		b_mVelocity.y -= 1.65f;
		break;
	case false:
		b_mVelocity.y += 2.0f;
		break;
	default:
		break;
	}
	

	if (mTimer->timerSet(2))
	{
		Shot(Vector2(b_mPosittion.x, b_mPosittion.y));
	}

	b_mPosittion -= b_mVelocity * b_mSpeed * deltaTime;
}

void StayEnemy::draw(Renderer * renderer, Renderer3D* renderer3D)
{
	renderer3D->draw3DTexture("enemyT", Vector3(b_mPosittion.x, b_mPosittion.y, 0.0f), Vector2(0.0f, 0.0f), Vector2(64.0f, 64.0f), 96.0f*2, b_mAngle);
	renderer3D->draw3DTexture("enemy", Vector3(b_mPosittion.x, b_mPosittion.y, 0.0f), Vector2(0.0f, 0.0f), Vector2(64.0f, 64.0f), 96.0f*2, ShotAngle+90.0f);
	if (b_mHp <= 0)
	{
		b_animCnt += 64.0f;
	
		if (b_animCnt >= 1022.0f)
		{
			Score::getInstance().addScore(10000);


			if (GetRand(2) == 2)
			{
				charaManager->add(new Item(b_mPosittion, BulletType::T_Bullet, "enemy"));   
				b_mIsDeath = true;
			}

			b_mIsDeath = true;
		}
		renderer3D->draw3DTexture("deathBurst", Vector3(b_mPosittion.x, b_mPosittion.y, 0.0f), Vector2(b_animCnt, 0.0f), Vector2(64.0f, 64.0f), 140.0f, b_mAngle);
		renderer3D->draw3DTexture("10000", Vector3(b_mPosittion.x, b_mPosittion.y + 50.0f, 0.0f), Vector2(0.0f, 0.0f), Vector2(64.0f, 64.0f), 96.0f, 0.0f);
	}
	//renderer->draw2D("enemy", Vector2(b_mPosittion.x, b_mPosittion.y), Vector2(0, 0), Vector2(64, 64), Vector2(32, 32), Vector2(1.3f, 1.3f), b_mAngle, 255);

}

void StayEnemy::hit(BaseObject & other)
{
	if (other.getType() == Type::PLAYER_BULLET&&b_mType == Type::ENEMY)
	{
		b_mHp -= charaManager->getPlayerBulletDamage();
	}
}

void StayEnemy::Shot(Vector2 pos)
{
	charaManager->add(new AngleBullet(Vector2(b_mPosittion.x, b_mPosittion.y) + Vector2(32, 32), charaManager, b_mType, ShotAngle));
}
Vector2 StayEnemy::checkPlayerPos(Vector2 vec)
{
	//プレイヤーの位置を入れる
	Vector2 playerPos = charaManager->getPlayerPosition();
	Vector2 playerVec = playerPos - b_mPosittion;  //プレイヤーとの差分
	return playerVec.normalize();
}
