#include "Bullet.h"
#include"../../GameBase/WindowInfo.h"

Bullet::Bullet(Vector2 pos, CharactorManager* c, Type t)
{
	b_mPosittion = Vector2(pos);
	b_mVelocity = Vector2(0, 0);
	b_SetType = t;
	b_mCircleSize = 4.0f;
}

Bullet::~Bullet()
{
	delete rend;
}

void Bullet::setBulletType()
{
	switch (b_SetType)
	{
	case PLAYER:
		b_mType = Type::PLAYER_BULLET;
		break;
	case ENEMY:
		b_mType = Type::ENEMY_BULLET;
		break;
	default:
		break;
	}
}

void Bullet::initialize()
{
	setBulletType();
}

void Bullet::update(float deltaTime)
{
	b_mVelocity = Vector2(0, 0);

	if (b_mType == Type::PLAYER_BULLET)
	{
		b_mVelocity.y -= 12.0f;
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

void Bullet::draw(Renderer * renderer)
{
	rend->draw2D("bullet", Vector2(b_mPosittion.x, b_mPosittion.y), Vector2(0, 0), Vector2(64, 64), Vector2(32, 32), Vector2(1.0f, 1.0f), b_mAngle, 255);

	if (b_mType == Type::ENEMY_BULLET)
	{
		b_mAngle = 180.0f;
	}
}

void Bullet::hit(BaseObject & other)
{
	if (b_mType == ENEMY_BULLET && other.getType() == Type::PLAYER)
	{
		b_mIsDeath = true;

	}
	if (b_mType == PLAYER_BULLET && other.getType() == Type::ENEMY)
	{
		b_mIsDeath = true;

	}
	if (b_mType == PLAYER_BULLET && other.getType() == Type::ENEMY_BULLET || b_mType == ENEMY_BULLET && other.getType() == Type::PLAYER_BULLET)
	{
		b_mIsDeath = true;

	}

	DrawCircle(b_mPosittion.x + 64 / 2, b_mPosittion.y + 64 / 2, b_mCircleSize, GetColor(255, 255, 0), TRUE);
}

bool Bullet::getIsDeath() const
{
	return b_mIsDeath;
}

Type Bullet::getType() const
{
	return b_mType;
}

Vector2 Bullet::getPpstion() const
{
	return b_mPosittion;
}

float Bullet::getCircleSize() const
{
	return b_mCircleSize;
}

Type Bullet::ChangeType()
{
	return Type();
}

