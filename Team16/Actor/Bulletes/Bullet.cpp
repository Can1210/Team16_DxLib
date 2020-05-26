#include "Bullet.h"

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
	case ENEMY:
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

	//’e‚Ì‰ñ“]

	Vector2 MoveAngle;//i‚Þ•ûŒü

	float Sin = sin(b_mAngle);
	float Cos = cos(b_mAngle);

	MoveAngle.x = b_mVelocity.x*Cos - b_mVelocity.y*Sin;
	MoveAngle.y = b_mVelocity.x*Sin + b_mVelocity.y*Cos;
	b_mPosittion -=  MoveAngle * (deltaTime*b_mSpeed);
}

void Bullet::draw(Renderer * renderer, Renderer3D* renderer3D)
{
	
	if (b_SetType == Type::BOSS)
	{
		renderer3D->draw3DTexture("bossBullet", Vector3(b_mPosittion.x, b_mPosittion.y, 0.0f), Vector2(0.0f, 0.0f), Vector2(10.0f, 12.0f), 96.0f, b_mAngle);
		//renderer->draw2D("bossBullet", Vector2(b_mPosittion.x, b_mPosittion.y), Vector2(0, 0), Vector2(10, 12), Vector2(5, 5), Vector2(4.0f, 4.0f), b_mAngle, 255);
	}
	else
	{
		//renderer->draw2D("bullet", Vector2(b_mPosittion.x, b_mPosittion.y), Vector2(0, 0), Vector2(64, 64), Vector2(32, 32), Vector2(1.0f, 1.5f), b_mAngle, 255);
		renderer3D->draw3DTexture("bullet", Vector3(b_mPosittion.x, b_mPosittion.y, 0.0f), Vector2(0.0f, 0.0f), Vector2(64.0f, 64.0f), 32.0f, b_mAngle);

	}
}

void Bullet::hit(BaseObject & other)
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
	
	//DrawCircle((int)(b_mPosittion.x + 64 / 2), (int)(b_mPosittion.y + 64 / 2), (int)b_mCircleSize, GetColor(255, 255, 0), TRUE);
	
	
}
