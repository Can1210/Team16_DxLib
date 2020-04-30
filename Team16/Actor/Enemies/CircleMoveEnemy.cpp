#include "CircleMoveEnemy.h"
#include <random>


CirecleMoveEnemy::CirecleMoveEnemy(Vector2 pos, CharactorManager * c) :mTimer(new Timer())
{
	charaManager = c;
	b_mPosittion = pos;
}

CirecleMoveEnemy::~CirecleMoveEnemy()
{
	delete input;
	delete rend;
	delete mTimer;
}

void CirecleMoveEnemy::initialize()
{
	b_mHp = 100;
	MoveFlag = FALSE;
	input = new Input;
	input->init();
	rend = new Renderer;
	b_mCircleSize = 16.0f;
	b_mType = Type::ENEMY;
	b_mAngle = 180.0f;
	mTimer->initialize();
}

void CirecleMoveEnemy::update(float deltaTime)
{

	input->update();
	mTimer->update(deltaTime);
	b_mVelocity = Vector2(0, 0);

	if (b_mType == Type::ENEMY)
	{
		b_mVelocity.y += 2;
		if (mTimer->timerSet(2))
		{
			Shot(Vector2(b_mPosittion.x, b_mPosittion.y));
		}
		if (b_mHp <= 0)
		{
			b_mIsDeath = true;
		}

	}




	//æ‚ÁŽæ‚èŒã
	if (b_mType == Type::PLAYER && !b_mEndFlag)
	{

		if (input->isKeyState(KEYCORD::ARROW_UP))
		{
			b_mVelocity.y -= 3;
		}
		if (input->isKeyState(KEYCORD::ARROW_DOWN))
		{
			b_mVelocity.y += 3;
		}
		if (input->isKeyState(KEYCORD::ARROW_RIGHT))
		{
			b_mVelocity.x += 3;
		}
		if (input->isKeyState(KEYCORD::ARROW_LEFT))
		{
			b_mVelocity.x -= 3;
		}
		if (input->isKeyDown(KEYCORD::SPACE))
		{
			Shot(Vector2(b_mPosittion.x, b_mPosittion.y));
		}
		if (input->isKeyDown(KEYCORD::X))
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

void CirecleMoveEnemy::draw(Renderer * renderer)
{
	if (b_mType == Type::ENEMY)
	{
		DrawCircle(b_mPosittion.x + 64 / 2, b_mPosittion.y + 64 / 2, b_mCircleSize, GetColor(255, 0, 0), FALSE);
		rend->draw2D("enemy2", Vector2(b_mPosittion.x, b_mPosittion.y), Vector2(0, 0), Vector2(64, 64), Vector2(32, 32), Vector2(1.0f, 1.0f), b_mAngle, 255);
	}
	else if (!b_mEndFlag)
	{
		DrawCircle(b_mPosittion.x + 64 / 2, b_mPosittion.y + 64 / 2, b_mCircleSize, GetColor(0, 0, 255), FALSE);
		b_mAngle = 0.0f;
		rend->draw2D("enemy2", Vector2(b_mPosittion.x, b_mPosittion.y), Vector2(0, 0), Vector2(64, 64), Vector2(32, 32), Vector2(1.0f, 1.0f), b_mAngle, 255);
		rend->drawNumber("hpNumber", Vector2(150, 10), b_mHp, 0, Vector2(0, 0), Vector2(1, 1), 0.0f, 255);
	}
	if (b_mEndFlag)
	{
		rend->drawText("Font", "GAMEOVER", Vector2(100, 450), Vector2(0, 0), Vector2(1, 1), 0.0f, 255);
	}

}

void CirecleMoveEnemy::hit(BaseObject & other)
{
	if (other.getType() == Type::PLAYER_BULLET&&b_mType == Type::ENEMY)
	{
		b_mHp -= 20;
		DrawCircle(b_mPosittion.x + 64 / 2, b_mPosittion.y + 64 / 2, b_mCircleSize, GetColor(255, 255, 0), TRUE);
	}
	if (other.getType() == Type::ENEMY_BULLET&&b_mType == Type::PLAYER)
	{
		b_mHp -= 20;
		DrawCircle(b_mPosittion.x + 64 / 2, b_mPosittion.y + 64 / 2, b_mCircleSize, GetColor(255, 255, 0), TRUE);
	}
	if (other.getType() == Type::ENEMY&&b_mType == Type::PLAYER)
	{
		b_mHp -= 1;
		DrawCircle(b_mPosittion.x + 64 / 2, b_mPosittion.y + 64 / 2, b_mCircleSize, GetColor(255, 255, 0), TRUE);
	}




}

void CirecleMoveEnemy::Shot(Vector2 pos)
{
	charaManager->add(new Bullet(Vector2(b_mPosittion.x + 20, b_mPosittion.y), charaManager, b_mType));
	charaManager->add(new Bullet(Vector2(b_mPosittion.x - 20, b_mPosittion.y), charaManager, b_mType));
}


void CirecleMoveEnemy::CShot(Vector2 pos)
{
	charaManager->add(new ChangeBullet(pos, charaManager));
}

void CirecleMoveEnemy::Jibaku(Vector2 pos)
{
	charaManager->add(new Bom(pos, charaManager));
	b_mIsDeath = true;
	charaManager->add(new Player(pos, charaManager));
}

bool CirecleMoveEnemy::getIsDeath() const
{
	return b_mIsDeath;
}

Type CirecleMoveEnemy::getType() const
{
	return b_mType;
}

Vector2 CirecleMoveEnemy::getPpstion() const
{
	return b_mPosittion;
}

float CirecleMoveEnemy::getCircleSize() const
{
	return b_mCircleSize;
}

Type CirecleMoveEnemy::ChangeType()
{
	b_mType = Type::PLAYER;
	return b_mType;
}
