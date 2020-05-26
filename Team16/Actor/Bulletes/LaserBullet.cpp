#include"LaserBullet.h"
#include<math.h>

LaserBullet::LaserBullet(Vector2 pos, CharactorManager * c, Type t, float angle)
{
	b_mPosittion = Vector2(pos);
	b_mVelocity = Vector2(0, 0);
	b_SetType = t;
	b_mCircleSize = 16.0f;
	bulletAngle = angle;
	b_mSpeed = 600.0f;
}

LaserBullet::~LaserBullet()
{
}

void LaserBullet::setBulletType()
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

void LaserBullet::initialize()
{
	setBulletType();
	b_mVelocity = Vector2(0, 0);
}

void LaserBullet::update(float deltaTime)
{
	if (b_mType == Type::PLAYER_BULLET)
	{
		b_mVelocity = RotationZ(bulletAngle);
		//b_mPosittion += Vector2(0, b_mVelocity.y) * deltaTime* b_mSpeed;
		//b_mPosittion.x = v->x;
		b_mPosittion -= b_mVelocity * deltaTime* b_mSpeed;
	}
	else if (b_mType == Type::ENEMY_BULLET)
	{
		b_mVelocity = RotationZ(bulletAngle);
		//b_mPosittion += Vector2(0,b_mVelocity.y) * deltaTime  * b_mSpeed;
		//b_mPosittion.x = v->x;
		b_mPosittion -= b_mVelocity * deltaTime* b_mSpeed;
	}
}

void LaserBullet::draw(Renderer * renderer, Renderer3D * renderer3D)
{
	Vector2 a = RotationZ(bulletAngle);
	float angle = atan2(a.y, a.x)* 180.0f / DX_PI_F;

	renderer3D->draw3DTexture("bullet1", Vector3(b_mPosittion.x, b_mPosittion.y, 0.0f), Vector2(0.0f, 0.0f), Vector2(12.0f, 16.0f), 32.0f, angle - 90.0f);
	//renderer->draw2D("bullet1", Vector2(b_mPosittion.x, b_mPosittion.y), Vector2(0, 0), Vector2(12, 16), Vector2(6, 8), Vector2(1.0f, 1.0f), angle - 90.0f, 255);
	//DrawCircle((int)(b_mPosittion.x + 64.0f / 2), (int)(b_mPosittion.y + 64.0f / 2), (int)b_mCircleSize, GetColor(255, 255, 0), TRUE);
}

void LaserBullet::hit(BaseObject & other)
{
	if (b_mType == PLAYER_BULLET && (other.getType() == Type::ENEMY || other.getType() == Type::BOSS))
	{
		b_mIsDeath = true;
		Sound::getInstance().playSE("burst02");
	}
	if (b_mType == ENEMY_BULLET && (other.getType() == Type::PLAYER || other.getType() == Type::BOM))
	{
		b_mIsDeath = true;
		Sound::getInstance().playSE("burst02");
	}
	//DrawCircle((int)(b_mPosittion.x + 64.0f / 2), (int)(b_mPosittion.y + 64.0f / 2), (int)b_mCircleSize, GetColor(255, 255, 0), TRUE);
}

Vector2 LaserBullet::RotationZ(float ang)
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
