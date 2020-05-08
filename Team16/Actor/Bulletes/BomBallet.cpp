#include "BomBallet.h"

BomBullet::BomBullet(Vector2 pos, CharactorManager * c, Type t) :mTimer(new Timer())
{
	b_mPosittion = Vector2(pos);
	b_mVelocity = Vector2(0, 0);
	b_SetType = t;
	b_mCircleSize = 12.0f;
}

BomBullet::~BomBullet()
{
	delete mTimer;
}

void BomBullet::setBulletType()
{
	switch (b_SetType)
	{
	case PLAYER:
		b_mType = Type::PLAYER_BULLET;
		break;
	case SUB_PLAYER:
		b_mType = Type::PLAYER_BULLET;
		break;
	case ENEMY:
		b_mType = Type::ENEMY_BULLET;
		break;
	default:
		break;
	}
}

void BomBullet::initialize()
{
	setBulletType();
	mTimer->initialize();
}

void BomBullet::update(float deltaTime)
{
	b_mVelocity = Vector2(0, 0);
	mTimer->update(deltaTime);
	if (mTimer->timerSet(1))
	{
		BomFlag = TRUE;
	}
	if (BomFlag)
	{
		b_mCircleSize += 10;
		if (b_mCircleSize > 150)
		{
			BomFlag = FALSE;
			b_mIsDeath = true;
		}
	}
	if (b_mType == Type::PLAYER_BULLET)
	{
		b_mVelocity.y -= 6.0f;
		b_mPosittion += b_mVelocity;
	}
	if (b_mType == Type::ENEMY_BULLET)
	{
		b_mVelocity.y += 6.0f;
		b_mPosittion += b_mVelocity;
	}


	if (b_mPosittion.y > WindowInfo::WindowHeight
		|| b_mPosittion.y<0
		|| b_mPosittion.x>WindowInfo::WindowWidth
		|| b_mPosittion.x < 0)
	{
		b_mIsDeath = true;
	}
}

void BomBullet::draw(Renderer * renderer, Renderer3D* renderer3D)
{
	DrawCircle(b_mPosittion.x + 64 / 2, b_mPosittion.y + 32, b_mCircleSize, GetColor(255, 100, 0), TRUE);
}

void BomBullet::hit(BaseObject & other)
{

}

