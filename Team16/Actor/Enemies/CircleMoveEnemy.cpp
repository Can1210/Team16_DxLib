#include "CircleMoveEnemy.h"
#include <random>
#include "../Bulletes/Bullet.h"
#include "../Bulletes/AngleBullet.h"
#include "../Item/Item.h"

CirecleMoveEnemy::CirecleMoveEnemy(Vector2 pos, CharactorManager * c) :m_pTimer(new Timer()), mTimerDamege(new Timer())
{
	charaManager = c;
	b_mPosittion = pos;
}

CirecleMoveEnemy::~CirecleMoveEnemy()
{
	delete m_pTimer;
	delete mTimerDamege;
}
//初期化
void CirecleMoveEnemy::initialize()
{
	b_mVelocity = checkPlayerPos(b_mVelocity);
	b_mHp = 2;
	b_mCircleSize = 16.0f;
	b_mType = Type::ENEMY;
	b_mAngle = 180.0f;
	b_mSpeed = 30.0f;
	b_mArpha = 255;
	m_pTimer->initialize();
	mTimerDamege->initialize();
	rotateSpeed = 0.5;//1周にかかる時間
	radius = 2.0f;   //半径10
	b_animCnt = 0.0f;
	mDamageHit = 255;
	isBom = false;    //ボムで死んだか
}
//更新
void CirecleMoveEnemy::update(float deltaTime)
{
	m_pTimer->update(deltaTime);
	mTimerDamege->update(deltaTime);
	if (mTimerDamege->timerSet_Self(0.2f))
	{
		mDamageHit = 255;
	}
	move(deltaTime);
	b_mPosittion += b_mVelocity * b_mSpeed * deltaTime;
}

void CirecleMoveEnemy::draw(Renderer * renderer, Renderer3D* renderer3D)
{
	renderer3D->draw3DTexture("enemyR2", Vector3(b_mPosittion.x, b_mPosittion.y, 0.0f), Vector2(0.0f, 0.0f), Vector2(64.0f, 64.0f), 96.0f, moveAngle+180.0f, 255, Vector2(0.5f, 0.5f), Vector3((float)255, (float)mDamageHit, (float)mDamageHit));
	if (b_mHp <= 0)
	{
		b_animCnt += 64.0f;
		if (b_animCnt >= 1022.0f)
		{
			Score::getInstance().addScore(200);
			if (GetRand(2) == 2)
			{
				charaManager->add(new Item(b_mPosittion, BulletType::T_AngleBullet, "enemy2"));   //アイテム生成
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
			Score::getInstance().addScore(200);
			b_mIsDeath = true;
		}
		renderer3D->draw3DTexture("deathBurst", Vector3(b_mPosittion.x, b_mPosittion.y, 0.0f), Vector2(b_animCnt, 0.0f), Vector2(64.0f, 64.0f), 140.0f, b_mAngle);
	}
}

void CirecleMoveEnemy::hit(BaseObject & other)
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

void CirecleMoveEnemy::Shot(Vector2 pos)
{
	Vector2 angleVec = Vector2(0,0);
	angleVec = checkPlayerPos(angleVec);  //角度を代入
	//角度に変換
	float angle = atan2(-angleVec.y, angleVec.x)* 180.0f / DX_PI_F;
	charaManager->add(new AngleBullet(Vector2(b_mPosittion.x , b_mPosittion.y) + Vector2(32, 32), charaManager, b_mType, angle));
}

void CirecleMoveEnemy::move(float deltaTime)
{
	moveTime += deltaTime * 4.0f;
	x = 2 * radius* cos(moveTime* rotateSpeed);
	y = radius * sin(moveTime* rotateSpeed);
	b_mPosittion +=  Vector2(x,y);

	moveAngle = x + y;
	if (m_pTimer->timerSet(2.0f)) Shot(b_mPosittion);

}
//プレイヤーの位置を調べる
Vector2 CirecleMoveEnemy::checkPlayerPos(Vector2 vec)
{
	//プレイヤーの位置を入れる
	Vector2 playerPos = charaManager->getPlayerPosition();
	Vector2 playerVec = playerPos - b_mPosittion;  //プレイヤーとの差分
	return playerVec.normalize();
}
