#include"TrakingBullet.h"
#include"../../GameBase/WindowInfo.h"
#include<math.h>

TrakingBullet::TrakingBullet(Vector2 pos, CharactorManager * c, Type t, float angle)
{
	b_mPosittion = Vector2(pos);
	b_mVelocity = Vector2(0, 0);
	b_SetType = t;
	b_mCircleSize = 4.0f;

	bulletAngle = angle;
	charaManager = c;
}

TrakingBullet::~TrakingBullet()
{
}

void TrakingBullet::setBulletType()
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

void TrakingBullet::initialize()
{
	setBulletType();
}

void TrakingBullet::update(float deltaTime)
{
	b_mVelocity = Vector2(0, 0);

	if (b_mType == Type::PLAYER_BULLET)
	{
		//objs = charaManager->getUseList();
		//for (int i = 0; i < objs.size; i++)
		//{
		//	objs[i]->getPpstion;
		//}
		//b_mVelocity.y -= 12.0f;
		b_mPosittion += RotationZ(bulletAngle) * 5.0f;
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

void TrakingBullet::draw(Renderer * renderer, Renderer3D * renderer3D)
{
	renderer->draw2D("bullet", Vector2(b_mPosittion.x, b_mPosittion.y), Vector2(0, 0), Vector2(64, 64), Vector2(32, 32), Vector2(1.0f, 1.0f), b_mAngle, 255);

	if (b_mType == Type::ENEMY_BULLET)
	{
		b_mAngle = 180.0f;
	}
}

void TrakingBullet::hit(BaseObject & other)
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

bool TrakingBullet::getIsDeath() const
{
	return b_mIsDeath;
}

Type TrakingBullet::getType() const
{
	return b_mType;
}

Vector2 TrakingBullet::getPpstion() const
{
	return b_mPosittion;
}

float TrakingBullet::getCircleSize() const
{
	return b_mCircleSize;
}

Type TrakingBullet::ChangeType()
{
	return Type();
}

Vector2 TrakingBullet::RotationZ(float ang)
{
	ang = ang + 45.0f;
	ang = ang * PI / 180.0;

	float sin = sinf(ang);
	float cos = cosf(ang);

	float x = cos + sin;
	float y = -(sin) + cos;

	return Vector2(x, y);
}
