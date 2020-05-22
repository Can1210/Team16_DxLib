#include "UFOEnemy.h"
#include <random>
#include <stdio.h>
#include <stdarg.h>
#include"../../Device/Sound.h"

UFOEnemy::UFOEnemy(Vector2 pos, CharactorManager *c, float angle1, float angle2, float angle3, Vector2 end) : mTimer(new Timer())
{
	charaManager = c;
	b_mPosittion = pos;
	this->angle1 = angle1;
	this->angle2 = angle2;
	this->angle3 = angle3;
	this->start = pos;
	this->end = end;
}

UFOEnemy::~UFOEnemy()
{
	delete input;
	delete mTimer;
}


void UFOEnemy::initialize()
{
	b_mHp = 3;
	MoveFlag = FALSE;
	input = new Input;
	input->init();
	b_mCircleSize = 16.0f;
	b_mType = Type::ENEMY;
	b_mAngle = 180.0f;
	mTimer->initialize();
	time = 0.0f;
	down = false;
	subShotcnt = 20;
	b_mArpha = 255;
	itemCnt = 0;
	itemDesthCnt = 50.0f;
}

void UFOEnemy::update(float deltaTime)
{
	mTimer->update(deltaTime);

	input->update();
	b_mVelocity = Vector2(0, 0);
	//ドロップ後処理
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
			subShotcnt++;
				if (subShotcnt > 20)
				{
					SubShot(Vector2(b_mPosittion.x+31.5f, b_mPosittion.y), 180.0f);
					subShotcnt = 0;
				}
			
		}
		if (input->isKeyDown(KEYCORD::C))
		{
			Jibaku(Vector2(b_mPosittion.x, b_mPosittion.y));
		}
		
	}

	if (b_mType == Type::ENEMY)
	{
		/*b_mVelocity += Traking() * 2.0f;*/
		//b_mVelocity = Vector2(sin(300.0f), -1.0f);
		time ++;

		float x = sin(time / 40.0f) * 3.0f;
		//if (down)		//続き
		//{
		//	b_mVelocity += Vector2(0, 1.5f);
		//}
		b_mVelocity += Vector2(x, 1.5f);
		if (mTimer->timerSet(1))
		{
			Shot(Vector2(b_mPosittion.x, b_mPosittion.y), 0.0f);
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

	
	b_mPosittion += b_mVelocity * deltaTime*b_mSpeed;
}

void UFOEnemy::draw(Renderer * renderer, Renderer3D* renderer3D)
{

	if (b_mType == Type::ENEMY)
	{
		DrawCircle(b_mPosittion.x + 64 / 2, b_mPosittion.y + 64 / 2, b_mCircleSize, GetColor(255, 0, 0), FALSE);
		renderer->draw2D("enemy", Vector2(b_mPosittion.x, b_mPosittion.y), Vector2(0, 0), Vector2(64, 64), Vector2(32, 32), Vector2(1.0f, 1.0f), b_mAngle, 255);
	}
	if(b_mType == Type::SUB_PLAYER1)
	{
		b_mAngle = 0.0f;
		renderer->draw2D("enemy", Vector2(b_mPosittion.x, b_mPosittion.y), Vector2(0, 0), Vector2(64, 64), Vector2(32, 32), Vector2(1.0f, 1.0f), b_mAngle, 255);
	}
	if (b_mType == Type::ITEM)
	{
		DrawCircle(b_mPosittion.x + 64 / 2, b_mPosittion.y + 64 / 2, itemDesthCnt, GetColor(0, 255, 0), FALSE);
		renderer->draw2D("enemy", Vector2(b_mPosittion.x, b_mPosittion.y), Vector2(0, 0), Vector2(64, 64), Vector2(32, 32), Vector2(1.0f, 1.0f), b_mAngle, b_mArpha);
	}

}

void UFOEnemy::hit(BaseObject & other)
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

	if (other.getType() == Type::PLAYER&&b_mType == Type::ITEM)
	{
		b_mType = Type::SUB_PLAYER1;
	}
}

void UFOEnemy::Shot(Vector2 pos, float angle)
{	//左
	//charaManager->add(new AngleBullet(pos, charaManager, b_mType, angle1 + angle));
	//真ん中
	Vector2 v = Vector2(pos.x - 8.0f, pos.y); Vector2 v1 = Vector2(pos.x + 8.0f, pos.y);
	charaManager->add(new AngleBullet(v, charaManager, b_mType, angle2 + angle));
	charaManager->add(new AngleBullet(pos, charaManager, b_mType, angle2 + angle));
	charaManager->add(new AngleBullet(v1, charaManager, b_mType, angle2 + angle));
	//右
	//charaManager->add(new AngleBullet(pos, charaManager, b_mType, angle3 + angle));
}
void UFOEnemy::SubShot(Vector2 pos, float angle)
{
	Vector2 v = Vector2(pos.x - 8.0f, pos.y); Vector2 v1 = Vector2(pos.x + 8.0f, pos.y);
	charaManager->add(new AngleBullet(v, charaManager, b_mType, angle2 + angle));
	charaManager->add(new AngleBullet(pos, charaManager, b_mType, angle2 + angle));
	charaManager->add(new AngleBullet(v1, charaManager, b_mType, angle2 + angle));

	
}
void UFOEnemy::PlayerShot(Vector2 pos, float angle) {
	charaManager->add(new AngleBullet(pos, charaManager, b_mType, angle2 + angle));
}


void UFOEnemy::Jibaku(Vector2 pos)
{
	Sound::getInstance().playSE("burst02");
	charaManager->add(new Bom(pos, charaManager));
	b_mIsDeath = true;
}


Vector2 UFOEnemy::Traking()
{
	Vector2 v = Vector2(0, 0);
	v = start - end;
	v = -v.normalize();
	return v;
}

