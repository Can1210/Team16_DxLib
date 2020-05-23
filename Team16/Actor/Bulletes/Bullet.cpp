#include "Bullet.h"
#include"../../GameBase/WindowInfo.h"
#include"../../Device/Sound.h"

Bullet::Bullet(Vector2 pos, CharactorManager* c, Type t,float angle)
{
	b_mPosittion = Vector2(pos);
	b_mVelocity = Vector2(0, 0);
	b_SetType = t;
	b_mCircleSize = 4.0f;
	b_mAngle = angle;
	b_mSpeed = 7.0f;
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
	case SUB_PLAYER1:
		b_mType = Type::PLAYER_BULLET;
		break;
	case SUB_PLAYER2:
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

	//弾の回転

	Vector2 MoveAngle;//進む方向

	float Sin = sin(b_mAngle);
	float Cos = cos(b_mAngle);

	MoveAngle.x = b_mVelocity.x*Cos - b_mVelocity.y*Sin;
	MoveAngle.y = b_mVelocity.x*Sin + b_mVelocity.y*Cos;
	b_mPosittion = b_mPosittion + MoveAngle * (deltaTime*b_mSpeed);
}

void Bullet::draw(Renderer * renderer, Renderer3D* renderer3D)
{
	
	if (b_SetType == Type::BOSS)
	{
		renderer->draw2D("bossBullet", Vector2(b_mPosittion.x, b_mPosittion.y), Vector2(0, 0), Vector2(10, 12), Vector2(5, 5), Vector2(4.0f, 4.0f), b_mAngle, 255);
	}
	else
	{
		renderer->draw2D("bullet", Vector2(b_mPosittion.x, b_mPosittion.y), Vector2(0, 0), Vector2(64, 64), Vector2(32, 32), Vector2(1.0f, 1.5f), b_mAngle, 255);
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
		Sound::getInstance().playSE("burst02");
	}
	if (b_mType == PLAYER_BULLET && other.getType() == Type::BOSS)
	{
		b_mIsDeath = true;
		Sound::getInstance().playSE("burst02");
	}
	if (b_mType == PLAYER_BULLET && other.getType() == Type::ENEMY_BULLET || b_mType == ENEMY_BULLET && other.getType() == Type::PLAYER_BULLET)
	{
		b_mIsDeath = true;
	}
	
	DrawCircle((int)(b_mPosittion.x + 64 / 2), (int)(b_mPosittion.y + 64 / 2), (int)b_mCircleSize, GetColor(255, 255, 0), TRUE);
	
	
}
