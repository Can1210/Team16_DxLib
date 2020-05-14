#include "Bullet.h"
#include"../../GameBase/WindowInfo.h"

Bullet::Bullet(Vector2 pos, CharactorManager* c, Type t,float angle)
{
	b_mPosittion = Vector2(pos);
	b_mVelocity = Vector2(0, 0);
	b_SetType = t;
	b_mCircleSize = 4.0f;
	b_mAngle = angle;
	b_mSpeed = 7;
}

Bullet::~Bullet()
{
	
}

void Bullet::setBulletType()
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
	case BOSS:
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

	//’e‚Ì‰ñ“]

	Vector2 MoveAngle;//i‚Þ•ûŒü

	float Sin = sin(b_mAngle);
	float Cos = cos(b_mAngle);

	MoveAngle.x = b_mVelocity.x*Cos - b_mVelocity.y*Sin;
	MoveAngle.y = b_mVelocity.x*Sin + b_mVelocity.y*Cos;
	b_mPosittion = b_mPosittion + MoveAngle * (deltaTime*b_mSpeed);
}

void Bullet::draw(Renderer * renderer, Renderer3D* renderer3D)
{
	renderer->draw2D("bullet", Vector2(b_mPosittion.x, b_mPosittion.y), Vector2(0, 0), Vector2(64, 64), Vector2(32, 32), Vector2(1.0f, 1.0f), b_mAngle, 255);
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
	if (b_mType == PLAYER_BULLET && other.getType() == Type::BOSS)
	{
		b_mIsDeath = true;
	}
	if (b_mType == PLAYER_BULLET && other.getType() == Type::ENEMY_BULLET || b_mType == ENEMY_BULLET && other.getType() == Type::PLAYER_BULLET)
	{
		b_mIsDeath = true;
	}
	
	DrawCircle(b_mPosittion.x + 64 / 2, b_mPosittion.y + 64 / 2, b_mCircleSize, GetColor(255, 255, 0), TRUE);
	
	
}
