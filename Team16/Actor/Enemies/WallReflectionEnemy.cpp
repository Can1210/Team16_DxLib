#include "WallReflectionEnemy.h"
#include <random>
#include "../Bulletes/WallReflectionBullet.h"
#include "../CharaManager/DeathPoint.h"
#include"../Item/Item.h"

WallReflectionEnemy::WallReflectionEnemy(Vector2 pos, CharactorManager * c) :m_pTimer(new Timer())
{
	charaManager = c;
	b_mPosittion = pos;
}

WallReflectionEnemy::~WallReflectionEnemy()
{
	delete m_pTimer;
}

//初期化
void WallReflectionEnemy::initialize()
{
	b_mVelocity = Vector2(0, 0);
	b_mHp = 2;
	b_mCircleSize = 16.0f;
	b_mType = Type::ENEMY;
	b_mAngle = 180.0f;
	m_pTimer->initialize();
	rotateSpeed = 0.5;//1周にかかる時間
	radius = 2;   //半径10
	b_mSpeed = 60.0f;
	b_mArpha = 255;

	startPos = Vector2(0.0f,DeathPoint::getInstance().getUp() + -300.0f);
	startEnd = false;
	shottime = 0;
	b_animCnt = 0.0f;
}
//更新
void WallReflectionEnemy::update(float deltaTime)
{
	m_pTimer->update(deltaTime);

	if (!startEnd)
	{
		Vector2 v = (b_mPosittion - startPos);
		float length = Vector2((b_mPosittion - startPos)).length();
		if (length < 2.0f)
		{
			startEnd = true;
		}
		v = v.normalize();
		b_mPosittion += -v * deltaTime * 120.0f;
		
		return;
	}
	move(deltaTime);

	shottime++;
}

void WallReflectionEnemy::draw(Renderer * renderer, Renderer3D* renderer3D)
{
	//renderer->draw2D("enemy2", Vector2(b_mPosittion.x, b_mPosittion.y), Vector2(0, 0), Vector2(64, 64), Vector2(32, 32), Vector2(1.3f, 1.3f), b_mAngle, 255);
	renderer3D->draw3DTexture("enemy2", Vector3(b_mPosittion.x, b_mPosittion.y, 0.0f), Vector2(0.0f, 0.0f), Vector2(64.0f, 64.0f), 96.0f, b_mAngle);
	if (b_mHp <= 0)
	{
		b_animCnt += 64.0f;
		renderer3D->draw3DTexture("deathBurst", Vector3(b_mPosittion.x, b_mPosittion.y, 0.0f), Vector2(b_animCnt, 0.0f), Vector2(64.0f, 64.0f), 96.0f, b_mAngle);
		if (b_animCnt >= 1022.0f)
		{
			Score::getInstance().addScore(200);
			charaManager->add(new Item(b_mPosittion, BulletType::T_LaserBullet, "enemy2"));   //アイテム生成 enumでバレットタイプを追加
			b_mIsDeath = true;
		}

	}
}

void WallReflectionEnemy::hit(BaseObject & other)
{
	if (other.getType() == Type::PLAYER_BULLET)
	{
		b_mHp -= charaManager->getPlayerBulletDamage();
	}
}

void WallReflectionEnemy::Shot(Vector2 pos)
{

	//Vector2 angleVec = Vector2(0, 0);
	//angleVec = checkPlayerPos(angleVec);  //角度を代入
	////角度に変換
	//float angle = atan2(-angleVec.y, angleVec.x)* 180.0f / DX_PI_F;

#if 0

	switch (shottime)
	{
	case 12:
		charaManager->add(new WallReflectionBullet(Vector2(b_mPosittion.x, b_mPosittion.y) + Vector2(32, 32), charaManager, b_mType, angle - 70 - 4));
		break;
	case 12 * 2:
		charaManager->add(new WallReflectionBullet(Vector2(b_mPosittion.x, b_mPosittion.y) + Vector2(32, 32), charaManager, b_mType, angle - 72 - 4));
		break;
	case 12 * 3:
		charaManager->add(new WallReflectionBullet(Vector2(b_mPosittion.x, b_mPosittion.y) + Vector2(32, 32), charaManager, b_mType, angle - 74 - 4));
		break;
	case 12 * 4:
		charaManager->add(new WallReflectionBullet(Vector2(b_mPosittion.x, b_mPosittion.y) + Vector2(32, 32), charaManager, b_mType, angle - 76 - 4));
		break;
	case 12 * 5:
		charaManager->add(new WallReflectionBullet(Vector2(b_mPosittion.x, b_mPosittion.y) + Vector2(32, 32), charaManager, b_mType, angle - 78 - 4));
		break;
	case 12 * 5 * 2:
		shottime = 0;
		break;
	}

#elif 1

	if (shottime % 60 * 2 == 0)
	{
		charaManager->add(new WallReflectionBullet(Vector2(b_mPosittion.x, b_mPosittion.y) + Vector2(32.0f, 32.0f), charaManager, b_mType, angle - 60));
		charaManager->add(new WallReflectionBullet(Vector2(b_mPosittion.x, b_mPosittion.y) + Vector2(32.0f, 32.0f), charaManager, b_mType, angle + 60));
	}

	if (shottime % 60 * 3 == 0)
	{
		charaManager->add(new WallReflectionBullet(Vector2(b_mPosittion.x, b_mPosittion.y) + Vector2(32.0f, 32.0f), charaManager, b_mType, angle - 40));
		charaManager->add(new WallReflectionBullet(Vector2(b_mPosittion.x, b_mPosittion.y) + Vector2(32.0f, 32.0f), charaManager, b_mType, angle + 40));
	}

	if (shottime % 60 * 4 == 0)
	{
		shottime = 0;
	}

#endif // 0

}

void WallReflectionEnemy::move(float deltaTime)
{
	moveTime += deltaTime * 1.0f;
	x = radius * cos(moveTime * rotateSpeed);
	y = radius * cos(moveTime * rotateSpeed * 2.0f);
	b_mPosittion += Vector2(x, y + 1.955f) * 1.0f;
	//b_mPosittion -= b_mVelocity * deltaTime*b_mSpeed;

	if (b_mHp <= 0)
	{
		//b_mType = Type::ITEM;
		Score::getInstance().addScore(200);
		charaManager->add(new Item(b_mPosittion, BulletType::T_LaserBullet, "enemy2"));   //アイテム生成 enumでバレットタイプを追加
		b_mIsDeath = true;
	}

	Shot(b_mPosittion);
}