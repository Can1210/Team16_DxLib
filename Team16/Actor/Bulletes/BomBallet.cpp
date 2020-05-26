#include "BomBallet.h"

BomBullet::BomBullet(Vector2 pos, CharactorManager * c, Type t,float angle) :mTimer(new Timer())
{
	b_mPosittion = Vector2(pos);
	b_mVelocity = Vector2(0, 0);
	b_SetType = t;
	b_mCircleSize = 9.0f;
	bulletAngle = angle;
	b_mBulletDamage = 0.1f;
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
	case ENEMY:
	case BOSS:
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
		if (b_mCircleSize > 100)
		{
			BomFlag = FALSE;
			b_mIsDeath = true;
		}
	}
	if (b_mType == Type::PLAYER_BULLET)
	{
		b_mVelocity.y -= 6.0f;
		b_mPosittion -= b_mVelocity;
	}
	if (b_mType == Type::ENEMY_BULLET)
	{
		//b_mVelocity.y += 6.0f;
		b_mVelocity = RotationZ(bulletAngle);
		b_mPosittion -= b_mVelocity*5.0f;
	}
}

void BomBullet::draw(Renderer * renderer, Renderer3D* renderer3D)
{
	//DrawCircle((int)(b_mPosittion.x + 64 / 2), (int)(b_mPosittion.y + 32), (int)b_mCircleSize, GetColor(255, 100, 0), TRUE);

	renderer3D->draw3DTexture("bullet_en6", Vector3(b_mPosittion.x, b_mPosittion.y, 0.0f), Vector2(0.0f, 0.0f), Vector2(10.0f, 12.0f), b_mCircleSize, 0.0f);
}

void BomBullet::hit(BaseObject & other)
{

}

Vector2 BomBullet::RotationZ(float ang)
{
	Vector2 v;
	ang = ang + 45.0f;
	ang = ang * PI / 180.0f;

	float sin = sinf(ang);
	float cos = cosf(ang);

	float x = cos + sin;
	float y = -(sin)+cos;
	v = Vector2(x, y);
	return v;
}

