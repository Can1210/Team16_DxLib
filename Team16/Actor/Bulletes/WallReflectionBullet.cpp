#include"WallReflectionBullet.h"
#include"../../GameBase/WindowInfo.h"
#include<math.h>
#include"../../Device/Sound.h"

WallReflectionBullet::WallReflectionBullet(Vector2 pos, CharactorManager * c, Type t, float angle)
{
	b_mPosittion = Vector2(pos);
	b_mVelocity = Vector2(0, 0);
	b_SetType = t;
	b_mCircleSize = 4.0f;

	bulletAngle = angle;
	playerPos = pos;
	b_mSpeed = 250.0f;
}

WallReflectionBullet::~WallReflectionBullet()
{
}

void WallReflectionBullet::setBulletType()
{
	switch (b_SetType)
	{
	case PLAYER:
		b_mType = Type::PLAYER_BULLET;
		break;
	case SUB_PLAYER1:
		b_mType = Type::PLAYER_BULLET;
		break;
	case ENEMY:
		b_mType = Type::ENEMY_BULLET;
		break;
	case BOSS:
		b_mType = Type::ENEMY_BULLET;
		break;
	default:
		break;
	}
}

void WallReflectionBullet::initialize()
{
	setBulletType();
	b_mVelocity = Vector2(0, 0);
	if (angle < 270 && angle >= 180)//enemy—p
	{
		type = L;
	}
	else if (angle >= 270)
	{
		type = R;
	}
	
	if (angle < 180 && angle >= 90)//player—p
	{
		type = L;
	}
	else if (angle >= 0)
	{
		type = R;
	}
}

void WallReflectionBullet::update(float deltaTime)
{
	if (b_mType == Type::PLAYER_BULLET)
	{
		if (b_mPosittion.x < 0.0f)
		{
			bulletAngle = 90 - (bulletAngle - 90);
			b_mVelocity = RotationZ(bulletAngle);
			type = R;
		}
		else if (b_mPosittion.x >= WindowInfo::WindowWidth)
		{
			bulletAngle = 90 + (90 - bulletAngle);
			b_mVelocity = RotationZ(bulletAngle);
			type = L;
		}

		switch (type)
		{
		case WallReflectionBullet::R:
			b_mVelocity = RotationZ(bulletAngle);
			break;
		case WallReflectionBullet::L:
			b_mVelocity = RotationZ(bulletAngle);
			break;
		case WallReflectionBullet::None:
			break;
		default:
			break;
		}
		b_mPosittion += b_mVelocity * deltaTime* b_mSpeed;
	}
	else if (b_mType == Type::ENEMY_BULLET)
	{
		if (b_mPosittion.x < 0.0f)
		{
			bulletAngle = 270 + (270 - bulletAngle);
			b_mVelocity = RotationZ(bulletAngle);
			type = R;
		}
		else if (b_mPosittion.x >= WindowInfo::WindowWidth)
		{
			bulletAngle = 270 - (bulletAngle - 270);
			b_mVelocity = RotationZ(bulletAngle);
			type = L;
		}

		switch (type)
		{
		case WallReflectionBullet::R:
			b_mVelocity = RotationZ(bulletAngle);
			break;
		case WallReflectionBullet::L:
			b_mVelocity = RotationZ(bulletAngle);
			break;
		case WallReflectionBullet::None:
			break;
		default:
			break;
		}
		b_mPosittion += b_mVelocity * deltaTime  * b_mSpeed;
	}

	if(b_mVelocity.x == 0.0f && b_mVelocity.y == 0.0f)
		b_mIsDeath = true;

	if (b_mPosittion.y > WindowInfo::WindowHeight + 64.0f
		|| b_mPosittion.y<0 - 64.0f
		|| b_mPosittion.x>WindowInfo::WindowWidth + 64.0f
		|| b_mPosittion.x < 0 - 64.0f)
	{
		b_mIsDeath = true;
	}
}

void WallReflectionBullet::draw(Renderer * renderer, Renderer3D * renderer3D)
{
	Vector2 a = RotationZ(bulletAngle);


	float angle = atan2(a.y, a.x)* 180.0f / DX_PI_F;

	renderer->draw2D("WallReflectionBullet", Vector2(b_mPosittion.x, b_mPosittion.y), Vector2(0, 0), Vector2(10, 12), Vector2(5, 5), Vector2(3.0f, 3.0f), b_mAngle, 255);

	if (b_mType == Type::ENEMY_BULLET)
	{
		b_mAngle = 180.0f;
	}
	else
	{
		b_mAngle = 0.0f;
	}
}

void WallReflectionBullet::hit(BaseObject & other)
{
	if (b_mType == ENEMY_BULLET && other.getType() == Type::PLAYER)
	{
		b_mIsDeath = true;

	}
	if (b_mType == PLAYER_BULLET && other.getType() == Type::ENEMY || other.getType() == Type::BOSS)
	{
		b_mIsDeath = true;
		Sound::getInstance().playSE("burst02");
	}
	if (b_mType == PLAYER_BULLET && other.getType() == Type::ENEMY_BULLET || b_mType == ENEMY_BULLET && other.getType() == Type::PLAYER_BULLET)
	{
		b_mIsDeath = true;
		Sound::getInstance().playSE("burst02");
	}

	DrawCircle(b_mPosittion.x + 12 / 2, b_mPosittion.y + 16 / 2, b_mCircleSize, GetColor(255, 255, 0), TRUE);
}

Vector2 WallReflectionBullet::RotationZ(float ang)
{
	Vector2 v;
	ang = ang + 45.0f;
	ang = ang * PI / 180.0;

	float sin = sinf(ang);
	float cos = cosf(ang);

	float x = cos + sin;
	float y = -(sin)+cos;
	v = Vector2(x, y);
	return v;
}
