#include"AngleBullet.h"
#include"../../GameBase/WindowInfo.h"
#include<math.h>
#include"../../Device/Sound.h"

AngleBullet::AngleBullet(Vector2 pos, CharactorManager * c, Type t, float angle)
{
	b_mPosittion = Vector2(pos);
	b_mVelocity = Vector2(0, 0);
	b_SetType = t;
	b_mCircleSize = 4.0f;

	bulletAngle = angle;
	playerPos = pos;
	b_mSpeed = 250.0f;
}

AngleBullet::~AngleBullet()
{
}

void AngleBullet::setBulletType()
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

void AngleBullet::initialize()
{
	setBulletType();
	b_mVelocity = Vector2(0, 0);
}

void AngleBullet::update(float deltaTime)
{
	if (b_mType == Type::PLAYER_BULLET)
	{
		b_mVelocity = RotationZ(bulletAngle);
		b_mPosittion += b_mVelocity *deltaTime* b_mSpeed;
	}
	else if (b_mType == Type::ENEMY_BULLET)
	{
		b_mVelocity = RotationZ(bulletAngle);
		b_mPosittion += b_mVelocity *deltaTime  * b_mSpeed;
	}

	if (b_mPosittion.y > WindowInfo::WindowHeight
		|| b_mPosittion.y<0
		|| b_mPosittion.x>WindowInfo::WindowWidth
		|| b_mPosittion.x < 0)
	{
		b_mIsDeath = true;
	}
}

void AngleBullet::draw(Renderer * renderer, Renderer3D * renderer3D)
{
	Vector2 a = RotationZ(bulletAngle);


	float angle = atan2(a.y, a.x)* 180.0f / DX_PI_F;
	
	renderer->draw2D("bullet1", Vector2(b_mPosittion.x, b_mPosittion.y), Vector2(0, 0), Vector2(12, 16), Vector2(6, 8), Vector2(2.0f, 4.0f),angle - 90.0f, 255);

	if (b_mType == Type::ENEMY_BULLET)
	{
		b_mAngle = 180.0f;
	}
	else
	{
		b_mAngle = 0.0f;
	}
}

void AngleBullet::hit(BaseObject & other)
{
	if (b_mType == ENEMY_BULLET && other.getType() == Type::PLAYER)
	{
		b_mIsDeath = true;

	}
	if (b_mType == PLAYER_BULLET && other.getType() == Type::ENEMY||other.getType() == Type::BOSS)
	{
		b_mIsDeath = true;
		Sound::getInstance().playSE("burst02");
	}
	if (b_mType == PLAYER_BULLET && other.getType() == Type::ENEMY_BULLET || b_mType == ENEMY_BULLET && other.getType() == Type::PLAYER_BULLET)
	{
		b_mIsDeath = true;
		Sound::getInstance().playSE("burst02");
	}

	DrawCircle((int)(b_mPosittion.x + 12 / 2), (int)(b_mPosittion.y + 16 / 2), (int)b_mCircleSize, GetColor(255, 255, 0), TRUE);
}

Vector2 AngleBullet::RotationZ(float ang)
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
