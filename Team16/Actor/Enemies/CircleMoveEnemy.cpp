#include "CircleMoveEnemy.h"
#include <random>
#include "../Bulletes/Bullet.h"
#include "../Bulletes/AngleBullet.h"
#include "../Item/Item.h"

CirecleMoveEnemy::CirecleMoveEnemy(Vector2 pos, CharactorManager * c) :m_pTimer(new Timer())
{
	charaManager = c;
	b_mPosittion = pos;
}

CirecleMoveEnemy::~CirecleMoveEnemy()
{
	delete m_pTimer;
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
	rotateSpeed = 0.5;//1周にかかる時間
	radius = 2;   //半径10
}
//更新
void CirecleMoveEnemy::update(float deltaTime)
{
	m_pTimer->update(deltaTime);
	move(deltaTime);
	b_mPosittion += b_mVelocity * b_mSpeed * deltaTime;
}

void CirecleMoveEnemy::draw(Renderer * renderer, Renderer3D* renderer3D)
{
	//renderer->draw2D("enemy2", Vector2(b_mPosittion.x, b_mPosittion.y), Vector2(0, 0), Vector2(64, 64), Vector2(32, 32), Vector2(1.3f, 1.3f), b_mAngle, 255);
	renderer3D->draw3DTexture("enemy2", Vector3(b_mPosittion.x, b_mPosittion.y, 0.0f), Vector2(0.0f, 0.0f), Vector2(64.0f, 64.0f), 96.0f, b_mAngle);
}

void CirecleMoveEnemy::hit(BaseObject & other)
{
	if (other.getType() == Type::PLAYER_BULLET)
	{
		b_mHp -= charaManager->getPlayerBulletDamage();
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

	if (b_mHp <= 0)
	{
		charaManager->add(new Item(b_mPosittion, BulletType::T_Bullet, "enemy2"));   //アイテム生成
 		Score::getInstance().addScore(200);
		b_mIsDeath = true;
	}
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
