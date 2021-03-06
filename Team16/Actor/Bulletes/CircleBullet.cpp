#include "CircleBullet.h"

CircleBullet::CircleBullet(Vector2 pos, CharactorManager* c, Type t, float angle)
{
	b_mPosittion = Vector2(pos);
	b_mVelocity = Vector2(0, 0);
	b_SetType = t;
	b_mCircleSize = 30.0f;
	b_mAngle = angle;
	b_mSpeed = 700.0f;
	b_mBulletDamage = 0.22f;
	rotateSpeed = 2.0f;//1周にかかる時間
	radius = 3.0f;   //半径10
}

CircleBullet::~CircleBullet()
{

}

void CircleBullet::setBulletType()
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

void CircleBullet::initialize()
{
	setBulletType();
	preHit = false;
	curHit = false;
}

void CircleBullet::update(float deltaTime)
{
	b_mVelocity = Vector2(0, 0);

	if (b_mType == Type::PLAYER_BULLET)
	{
		//moveTime += deltaTime * 4.0f;//回転用
		//x = 2.0f * radius* cos(moveTime* rotateSpeed);
		//y = 3.0f * radius * sin(moveTime* rotateSpeed);
		// 	b_mVelocity = Vector2(x, y);
		//b_mVelocity.y += 4.0f;
		//
		//b_mPosittion += b_mVelocity;//回転用

		b_mVelocity = Vector2(0.0f, 1.0f);//真っ直ぐ用
		b_mPosittion += b_mVelocity * deltaTime * b_mSpeed;//真っ直ぐ用
	}
	if (b_mType == Type::ENEMY_BULLET)
	{
		b_mVelocity.y += 12.0f;
		b_mPosittion -= b_mVelocity;
	}

	//弾の回転

	Vector2 MoveAngle;//進む方向

	//float Sin = sin(b_mAngle);
	//float Cos = cos(b_mAngle);

	//MoveAngle.x = b_mVelocity.x*Cos - b_mVelocity.y*Sin;
	//MoveAngle.y = b_mVelocity.x*Sin + b_mVelocity.y*Cos;
	//b_mPosittion += MoveAngle * (deltaTime*b_mSpeed);
}

void CircleBullet::draw(Renderer * renderer, Renderer3D* renderer3D)
{

	if (b_SetType == Type::BOSS)
	{
		renderer3D->draw3DTexture("bossBullet", Vector3(b_mPosittion.x, b_mPosittion.y, 0.1f), Vector2(0.0f, 0.0f), Vector2(10.0f, 12.0f), 96.0f, b_mAngle);
		//renderer->draw2D("bossBullet", Vector2(b_mPosittion.x, b_mPosittion.y), Vector2(0, 0), Vector2(10, 12), Vector2(5, 5), Vector2(4.0f, 4.0f), b_mAngle, 255);
	}
	else
	{
		//renderer->draw2D("bullet", Vector2(b_mPosittion.x, b_mPosittion.y), Vector2(0, 0), Vector2(64, 64), Vector2(32, 32), Vector2(1.0f, 1.5f), b_mAngle, 255);
		renderer3D->draw3DTexture("bullet", Vector3(b_mPosittion.x, b_mPosittion.y, 0.0f), Vector2(0.0f, 0.0f), Vector2(64.0f, 64.0f), 64.0f * 5.0f, b_mAngle);

	}
}

void CircleBullet::hit(BaseObject & other)
{
	curHit = false;
	if (b_mType == PLAYER_BULLET && (other.getType() == Type::ENEMY || other.getType() == Type::BOSS))
	{

		if(!preHit)
			Sound::getInstance().playSE("burst02");

		curHit = true;
	}

	preHit = curHit;


	if (b_mType == ENEMY_BULLET && (other.getType() == Type::PLAYER || other.getType() == Type::BOM))
	{
		b_mIsDeath = true;
		Sound::getInstance().playSE("burst02");
	}
	//DrawCircle((int)(b_mPosittion.x + 64 / 2), (int)(b_mPosittion.y + 64 / 2), (int)b_mCircleSize, GetColor(255, 255, 0), TRUE);
}
