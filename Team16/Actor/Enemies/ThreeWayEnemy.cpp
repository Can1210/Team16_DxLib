#include "ThreeWayEnemy.h"
#include <random>
#include <stdio.h>
#include <stdarg.h>

ThreeWayEnemy::ThreeWayEnemy(Vector2 pos, CharactorManager *c, float angle1, float angle2, float angle3,Vector2 end) : mTimer(new Timer())
{
	charaManager = c;
	b_mPosittion = pos;
	this->angle1 = angle1;
	this->angle2 = angle2;
	this->angle3 = angle3;
	this->start = pos;
	this->end = end;
}

ThreeWayEnemy::~ThreeWayEnemy()
{
	delete input;
	delete mTimer;
}

bool ThreeWayEnemy::SubNull()//自機の更新
{
	for (auto object : charaManager->getUseList())
	{
		if (object->getType() == Type::PLAYER)
		{
			return true;
		}
	}
	return false;
}

void ThreeWayEnemy::SubChange()
{
	b_mType = Type::PLAYER;
	KakoPos = b_mPosittion;
}






void ThreeWayEnemy::initialize()
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
	r = 0;
	b = 255;
}

void ThreeWayEnemy::update(float deltaTime)
{
	mTimer->update(deltaTime);

	input->update();
	b_mVelocity = Vector2(0, 0);

	if (b_mType == Type::SUB_PLAYER)
	{
		b_mPosittion = charaManager->searchPlayer();
		if (input->isKeyState(KEYCORD::SPACE))
		{
			SubShot(Vector2(b_mPosittion.x, b_mPosittion.y),0.0f);
		}
		if (input->isKeyDown(KEYCORD::C))
		{
			Jibaku(Vector2(b_mPosittion.x, b_mPosittion.y));
		}
		if (SubNull())
		{
			b_mType = Type::PLAYER;
		}
		KakoPos = b_mPosittion;
	}

	if (b_mType == Type::ENEMY)
	{	
		b_mVelocity += Traking() * 2.0f;
		//b_mVelocity.y += 2;
		if (mTimer->timerSet(2))
		{
			SubShot(Vector2(b_mPosittion.x, b_mPosittion.y),0.0f);
		}
		if (b_mPosittion.y > WindowInfo::WindowHeight
			|| b_mPosittion.x > WindowInfo::WindowWidth
			|| b_mPosittion.x < 0
			|| b_mHp <= 0)
		{
			b_mIsDeath = true;
		}
	}

	//乗っ取り後
	if (b_mType == Type::PLAYER && !b_mEndFlag)
	{
		if (input->isKeyState(KEYCORD::ARROW_UP))
		{
			b_mVelocity.y -= 4;
		}
		if (input->isKeyState(KEYCORD::ARROW_DOWN))
		{
			b_mVelocity.y += 4;
		}
		if (input->isKeyState(KEYCORD::ARROW_RIGHT))
		{
			b_mVelocity.x += 4;
		}
		if (input->isKeyState(KEYCORD::ARROW_LEFT))
		{
			b_mVelocity.x -= 4;
		}
		if (input->isKeyDown(KEYCORD::SPACE))
		{
			Shot(Vector2(b_mPosittion.x, b_mPosittion.y),180.0f);
		}
		if (input->isKeyState(KEYCORD::SPACE))
		{
			SubShot(Vector2(b_mPosittion.x, b_mPosittion.y), 180.0f);
		}

		if (input->isKeyState(KEYCORD::V))
		{
			shotcnt++;
			if (shotcnt > 100)
			{
				shotcnt = 100;
			}
		}

		if (shotcnt == 100 && input->isKeyUp(KEYCORD::V))
		{
			CShot(Vector2(b_mPosittion.x, b_mPosittion.y));
		}
		if (input->isKeyDown(KEYCORD::C))
		{
			Jibaku(Vector2(b_mPosittion.x, b_mPosittion.y));
		}
		if (b_mHp <= 0)
		{
			b_mEndFlag = true;
		}
		b_mPosittion += b_mVelocity;
	}
	b_mPosittion += b_mVelocity;
}

void ThreeWayEnemy::draw(Renderer * renderer, Renderer3D* renderer3D)
{
	if (b_mType == Type::ENEMY)
	{
		DrawCircle(b_mPosittion.x + 64 / 2, b_mPosittion.y + 64 / 2, b_mCircleSize, GetColor(255, 0, 0), FALSE);
		renderer->draw2D("enemy", Vector2(b_mPosittion.x, b_mPosittion.y), Vector2(0, 0), Vector2(64, 64), Vector2(32, 32), Vector2(1.0f, 1.0f), b_mAngle, 255);
	}
	else if (!b_mEndFlag)
	{
		if (DamgeFlag)
		{
			b_mArpha = 155;
		}
		else
		{
			b_mArpha = 255;
		}

		//ゲージ
		DrawBox(0, 0, shotcnt, 100, GetColor(r, 0, b), TRUE);
		if (shotcnt == 100)
		{
			r = 255;
			b = 0;
		}

		DrawCircle(b_mPosittion.x + 64 / 2, b_mPosittion.y + 64 / 2, b_mCircleSize, GetColor(0, 0, 255), FALSE);
		b_mAngle = 0.0f;
		renderer->draw2D("enemy", Vector2(b_mPosittion.x, b_mPosittion.y), Vector2(0, 0), Vector2(64, 64), Vector2(32, 32), Vector2(1.0f, 1.0f), b_mAngle, b_mArpha);
		if (b_mType == Type::PLAYER)
		{
			renderer->drawNumber("hpNumber", Vector2(150, 10), b_mHp, 0, Vector2(0, 0), Vector2(1, 1), 0.0f, 255);
		}

	}

	if (b_mEndFlag)
	{
		renderer->drawText("Font", "GAMEOVER", Vector2(100, 450), Vector2(0, 0), Vector2(1, 1), 0.0f, 255);
	}
	
}

void ThreeWayEnemy::hit(BaseObject & other)
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
		mTimer->initialize();
		DamgeFlag = TRUE;
	}

	if (other.getType() == Type::ENEMY&&b_mType == Type::PLAYER)
	{
		b_mHp -= 1;
		DrawCircle(b_mPosittion.x + 64 / 2, b_mPosittion.y + 64 / 2, b_mCircleSize, GetColor(255, 255, 0), TRUE);
		mTimer->initialize();
		DamgeFlag = TRUE;
	}


	if (other.getType() == Type::CHANGE_BULLET&&b_mType == Type::ENEMY)
	{
		//最初は控えに
		b_mType = Type::SUB_PLAYER;
	}
}

void ThreeWayEnemy::Shot(Vector2 pos, float angle)
{
	charaManager->add(new Bullet(pos, charaManager, b_mType, 0.0f));
}

void ThreeWayEnemy::SubShot(Vector2 pos, float angle)
{
	if (b_mType == Type::ENEMY)
	{
		charaManager->add(new AngleBullet(pos, charaManager, b_mType, angle1 + angle));
		charaManager->add(new AngleBullet(pos, charaManager, b_mType, angle2 + angle));
		charaManager->add(new AngleBullet(pos, charaManager, b_mType, angle3 + angle));
	}
	else
	{
		angle = 0;
		charaManager->add(new AngleBullet(pos, charaManager, b_mType, angle1 + angle));
		charaManager->add(new AngleBullet(pos, charaManager, b_mType, angle2 + angle));
		charaManager->add(new AngleBullet(pos, charaManager, b_mType, angle3 + angle));
	}
}

void ThreeWayEnemy::CShot(Vector2 pos)
{
	charaManager->add(new ChangeBullet(pos, charaManager));
	shotcnt = 0;
	r = 0;
	b = 255;
}

void ThreeWayEnemy::Jibaku(Vector2 pos)
{
	charaManager->add(new Bom(pos, charaManager));
	b_mIsDeath = true;
}

Vector2 ThreeWayEnemy::getPpstion() const
{
	return b_mPosittion;
}

Vector2 ThreeWayEnemy::Traking()
{
	Vector2 v = Vector2(0, 0);
	v = start - end;
	v = -v.normalize();
	return v;
}

