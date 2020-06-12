#include "BomBallet.h"

BomBullet::BomBullet(Vector2 pos, CharactorManager * c, Type t,float angle) :mTimer(new Timer())
{
	b_mPosittion = Vector2(pos);
	b_mVelocity = Vector2(0, 0);
	b_SetType = t;
	b_mCircleSize = 10.0f;
	mMaxSize = 100.0f;
	bulletAngle = angle;
	b_mAngle = 0;
	b_mBulletDamage = 10.0f;
	BomFlag = false;
	b_animCnt = 0.0f;
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
		b_mType = Type::BOM;
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
	//o‚Ä1•b‚Å”š”­‚·‚é
	if (mTimer->timerSet(1))
	{
		BomFlag = TRUE;
	}
	//”š”­‚ªŠJŽn‚³‚ê‚½‚ç
	if (BomFlag)
	{
		//b_mCircleSize += 10;

		mAnimCount += 10.0f;
		if (b_animCnt >= 30.0f)
			b_animCnt = 0.0f;
		b_mCircleSize =  Vector2().lerp(b_mCircleSize, mMaxSize, 0.2f);
		//b_mAngle += 50;
		if (b_mCircleSize >= mMaxSize -1)
		{
			BomFlag = FALSE;
			b_mIsDeath = true;
		}
	}
	if (b_mType == Type::BOM)
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
//•`‰æ
void BomBullet::draw(Renderer * renderer, Renderer3D* renderer3D)
{
	//DrawCircle(100, 100, b_mCircleSize,1,1);
	
	if (b_mType == Type::ENEMY_BULLET)
	{
		renderer3D->draw3DTexture("bossBullet", Vector3(b_mPosittion.x, b_mPosittion.y, 0.0f), Vector2(b_animCnt, 0.0f), Vector2(10.0f, 12.0f), b_mCircleSize*5.0f, b_mAngle);
	}
	else
	{
		renderer3D->draw3DTexture("bullet_en3", Vector3(b_mPosittion.x, b_mPosittion.y, 0.0f), Vector2(b_animCnt, 0.0f), Vector2(10.0f, 12.0f), b_mCircleSize*5.0f, b_mAngle);
	}
}

void BomBullet::hit(BaseObject & other)
{
	Sound::getInstance().playSE("burst02");
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

