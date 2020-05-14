#include "SoldierEnemy.h"
#include <random>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h> // rand, srandä÷êî
#include <time.h>   // timeä÷êî

SoldierEnemy::SoldierEnemy(Vector2 pos, CharactorManager *c) : mTimer(new Timer())
{
	charaManager = c;
	b_mPosittion = pos;
}

SoldierEnemy::~SoldierEnemy()
{
	delete input;
	delete mTimer;
}

void SoldierEnemy::initialize()
{
	b_mHp = 3;
	MoveFlag = FALSE;
	input = new Input;
	input->init();
	b_mCircleSize = 16.0f;
	b_mType = Type::ENEMY;
	b_mAngle = 180.0f;
	mTimer->initialize();
	int shotcnt = 0;
	b_mArpha = 255;

	b_mVelocity = Vector2(0, -2.0f);
	shotcnt = 0;
	subShotCnt = 10;
	b_mSpeed = 70.0f;
	itemCnt = 0;
}

void SoldierEnemy::update(float deltaTime)
{
	mTimer->update(deltaTime);

	input->update();
	//b_mVelocity = Vector2(0, 0);
	if (b_mType == Type::SUB_PLAYER)
	{
		b_mPosittion = charaManager->searchPlayer();
		if (input->isKeyState(KEYCORD::SPACE))
		{
			if (subShotCnt > 10)
			{
				Shot(Vector2(b_mPosittion.x, b_mPosittion.y));
				subShotCnt = 0;
			}
			
		}
		if (input->isKeyDown(KEYCORD::C))
		{
			Jibaku(Vector2(b_mPosittion.x, b_mPosittion.y));
		}
		
	}

	if (b_mType == Type::ENEMY)
	{
		//b_mVelocity.y = -2.0f;
		//b_mPosittion = b_mVelocity;
		if (mTimer->timerSet(2))
		{
			Shot(Vector2(b_mPosittion.x, b_mPosittion.y));
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

	
	b_mPosittion += b_mVelocity;

	//ÉhÉçÉbÉvå„èàóù
	if (b_mType == Type::ITEM)
	{
		itemCnt++;
		if (itemCnt > 150)
		{
			b_mIsDeath = true;
		}
	}

}

void SoldierEnemy::draw(Renderer * renderer, Renderer3D* renderer3D)
{

	if (b_mType == Type::ENEMY)
	{
		DrawCircle(b_mPosittion.x + 64 / 2, b_mPosittion.y + 64 / 2, b_mCircleSize, GetColor(255, 0, 0), FALSE);
		renderer->draw2D("enemy", Vector2(b_mPosittion.x, b_mPosittion.y), Vector2(0, 0), Vector2(64, 64), Vector2(32, 32), Vector2(1.0f, 1.0f), b_mAngle, 255);
	}
	if (b_mType == Type::SUB_PLAYER)
	{
		b_mAngle = 0.0f;
		renderer->draw2D("enemy", Vector2(b_mPosittion.x, b_mPosittion.y), Vector2(0, 0), Vector2(64, 64), Vector2(32, 32), Vector2(1.0f, 1.0f), b_mAngle, b_mArpha);
	}
	if (b_mType == Type::ITEM)
	{
		DrawCircle(b_mPosittion.x + 64 / 2, b_mPosittion.y + 64 / 2, b_mCircleSize, GetColor(0, 255, 0), FALSE);
		renderer->draw2D("enemy", Vector2(b_mPosittion.x, b_mPosittion.y), Vector2(0, 0), Vector2(64, 64), Vector2(32, 32), Vector2(1.0f, 1.0f), b_mAngle, b_mArpha);
	}
	
}

void SoldierEnemy::hit(BaseObject & other)
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
		//ç≈èâÇÕçTÇ¶Ç…
		b_mType = Type::SUB_PLAYER;
	}
}

void SoldierEnemy::SetParentPos(Vector2 v)
{
	b_mPosittion = v;
}

void SoldierEnemy::Shot(Vector2 pos)
{
	//charaManager->add(new AngleBullet(pos, charaManager, b_mType, angle1 + angle));
	charaManager->add(new AngleBullet(pos, charaManager, b_mType,270));
	//charaManager->add(new AngleBullet(pos, charaManager, b_mType, angle3 + angle));
}

void SoldierEnemy::Jibaku(Vector2 pos)
{
	charaManager->add(new Bom(pos, charaManager));
	b_mIsDeath = true;
}
