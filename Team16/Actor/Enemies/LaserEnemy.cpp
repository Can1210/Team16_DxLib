#include "LaserEnemy.h"
#include <random>
#include <stdio.h>
#include <stdarg.h>
#include"../../Device/Sound.h"

LaserEnemy::LaserEnemy(Vector2 pos, CharactorManager *c, float angle1, float angle2, float angle3, Vector2 end) : mTimer(new Timer())
{
	charaManager = c;
	b_mPosittion = pos;
	this->angle1 = angle1;
	this->angle2 = angle2;
	this->angle3 = angle3;
	this->start = pos;
	this->end = end;
}

LaserEnemy::~LaserEnemy()
{
	delete input;
	delete mTimer;
}

void LaserEnemy::initialize()
{
	b_mHp = 3;
	MoveFlag = FALSE;
	input = new Input;
	input->init();
	b_mCircleSize = 16.0f;
	b_mType = Type::ENEMY;
	b_mAngle = 180.0f;
	mTimer->initialize();

	b_mArpha = 255;
	b_mSpeed = 70.0f;
	itemCnt = 0;
	itemDesthCnt = 50.0f;

	laserY = 0.0f;
}

void LaserEnemy::update(float deltaTime)
{
	mTimer->update(deltaTime);

	input->update();
	b_mVelocity = Vector2(0, 0);
	//ƒhƒƒbƒvŒãˆ—
	if (b_mType == Type::ITEM)
	{
		itemCnt++;
		itemDesthCnt -= 0.25f;
		if (itemCnt > 150)
		{
			Sound::getInstance().playSE("burst02");
			b_mIsDeath = true;
		}
	}

	if (b_mType == Type::SUB_PLAYER1)
	{
		b_mPosittion = charaManager->searchPlayer();
		if (input->isKeyState(KEYCORD::SPACE))
		{
			SubShot(Vector2(b_mPosittion.x + 31.5f, b_mPosittion.y), 180.0f);
		}
		if (input->isKeyDown(KEYCORD::C))
		{
			Jibaku(Vector2(b_mPosittion.x, b_mPosittion.y));
		}
	}

	if (b_mType == Type::ENEMY)
	{
		b_mVelocity += Traking() * 1.0f;
		if (laserY > 60.0f * 2.0f)
		{
			SubShot(Vector2(b_mPosittion.x, b_mPosittion.y), 0.0f);
			if (laserY > 60.0f * 3.0f)
				laserY = 0.0f;
		}
		if (b_mPosittion.y > WindowInfo::WindowHeight
			|| b_mPosittion.x > WindowInfo::WindowWidth
			|| b_mPosittion.x < 0)
		{
			b_mIsDeath = true;
		}
		if (b_mHp <= 0)
		{
			Score::getInstance().addScore(100);
			b_mType = Type::ITEM;
		}
	}
	laserY++;
	b_mPosittion += b_mVelocity * deltaTime*b_mSpeed;
}

void LaserEnemy::draw(Renderer * renderer, Renderer3D* renderer3D)
{
	if (b_mType == Type::ENEMY)
	{
		DrawCircle(b_mPosittion.x + 64 / 2, b_mPosittion.y + 64 / 2, b_mCircleSize, GetColor(255, 0, 0), FALSE);
		renderer->draw2D("enemy", Vector2(b_mPosittion.x, b_mPosittion.y), Vector2(0, 0), Vector2(64, 64), Vector2(32, 32), Vector2(1.0f, 1.0f), b_mAngle, 255);
	}
	if (b_mType == Type::SUB_PLAYER1)
	{
		b_mAngle = 0.0f;
		renderer->draw2D("enemy", Vector2(b_mPosittion.x, b_mPosittion.y), Vector2(0, 0), Vector2(64, 64), Vector2(32, 32), Vector2(1.0f, 1.0f), b_mAngle, b_mArpha);
	}

	if (b_mType == Type::ITEM)
	{
		DrawCircle(b_mPosittion.x + 64 / 2, b_mPosittion.y + 64 / 2, itemDesthCnt, GetColor(0, 255, 0), FALSE);
		renderer->draw2D("enemy", Vector2(b_mPosittion.x, b_mPosittion.y), Vector2(0, 0), Vector2(64, 64), Vector2(32, 32), Vector2(1.0f, 1.0f), b_mAngle, b_mArpha);
	}

}

void LaserEnemy::hit(BaseObject & other)
{
	if (other.getType() == Type::PLAYER_BULLET&&b_mType == Type::ENEMY)
	{
		b_mHp -= 1;
		DrawCircle(b_mPosittion.x + 64 / 2, b_mPosittion.y + 64 / 2, b_mCircleSize, GetColor(255, 255, 0), TRUE);
	}


	if (other.getType() == Type::ENEMY_BULLET&&b_mType == Type::PLAYER)
	{
		b_mHp -= 1;
		DrawCircle(b_mPosittion.x + 64 / 2, b_mPosittion.y + 64 / 2, b_mCircleSize, GetColor(255, 255, 0), TRUE);

	}

	if (other.getType() == Type::ENEMY&&b_mType == Type::PLAYER)
	{
		b_mHp -= 1;
		DrawCircle(b_mPosittion.x + 64 / 2, b_mPosittion.y + 64 / 2, b_mCircleSize, GetColor(255, 255, 0), TRUE);

	}
	if (other.getType() == Type::PLAYER&&b_mType == Type::ITEM)
	{
		//Å‰‚ÍT‚¦‚É
		b_mType = Type::SUB_PLAYER1;
	}
}

void LaserEnemy::Shot(Vector2 pos, float angle)
{
	charaManager->add(new LaserBullet(b_mPosittion, charaManager, b_mType, angle2 + angle,&b_mPosittion));
}

void LaserEnemy::SubShot(Vector2 pos, float angle)
{
	if (b_mType == Type::ENEMY)
	{
		charaManager->add(new LaserBullet(b_mPosittion, charaManager, b_mType, angle2 + angle, &b_mPosittion));
	}
	else
	{
		charaManager->add(new LaserBullet(b_mPosittion, charaManager, b_mType, angle2 + angle, &b_mPosittion));
	}
}


void LaserEnemy::Jibaku(Vector2 pos)
{
	Sound::getInstance().playSE("burst02");
	charaManager->add(new Bom(pos, charaManager));
	b_mIsDeath = true;
}

Vector2 LaserEnemy::Traking()
{
	Vector2 v = Vector2(0, 0);
	v = start - end;
	v = -v.normalize();
	return v;
}