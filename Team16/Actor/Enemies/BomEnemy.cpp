#include <random>
#include"BomEnemy.h"

BomEnemy::BomEnemy(Vector2 pos, CharactorManager *c) :mTimer(new Timer())
{
	charaManager = c;
	b_mPosittion = pos;
	input = new Input;
}

BomEnemy::~BomEnemy()
{
	delete input;
	delete mTimer;
}

bool BomEnemy::PlayerNull()
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

void BomEnemy::SubChange()
{
	b_mPosittion = KakoPos;
	b_mType = Type::PLAYER;
}



void BomEnemy::initialize()
{
	b_mHp = 4;

	
	input->init();
	b_mCircleSize = 16.0f;
	b_mType = Type::ENEMY;
	b_mAngle = 180.0f;
	mTimer->initialize();
	b_mSpeed = 20.0f;
	shotcnt = 0;
	subShotCnt = 20;
	r = 0;
	b = 255;
}

void BomEnemy::update(float deltaTime)
{
	mTimer->update(deltaTime);

	input->update();
	b_mVelocity = Vector2(0, 0);

	//無敵時間
	if (DamgeFlag&&mTimer->timerSet(2))
	{
		DamgeFlag = FALSE;
	}


	
	if (b_mType == Type::SUB_PLAYER)
	{
		b_mPosittion = charaManager->searchPlayer();
		if (input->isKeyState(KEYCORD::SPACE))
		{
			subShotCnt++;
			if (subShotCnt > 20)
			{
				SubShot(Vector2(b_mPosittion.x, b_mPosittion.y));
				subShotCnt = 0;
			}
			
		}
		else
		{
			subShotCnt = 0;
		}
		if (input->isKeyDown(KEYCORD::C))
		{
			Jibaku(Vector2(b_mPosittion.x, b_mPosittion.y));
		}
		if (!PlayerNull())
		{
			SubChange();
		}
		KakoPos = b_mPosittion;
	}


	if (b_mType == Type::ENEMY)
	{
		b_mVelocity.y += 1;
		if (mTimer->timerSet(6))
		{
			SubShot(Vector2(b_mPosittion.x, b_mPosittion.y));
		}
		if (b_mHp <= 0)
		{
			b_mIsDeath = true;
		}
		if (b_mPosittion.y > WindowInfo::WindowHeight
			|| b_mPosittion.x>WindowInfo::WindowWidth
			|| b_mPosittion.x < 0
			||b_mHp<=0)
		{
			b_mIsDeath = true;
		}
		b_mPosittion += b_mVelocity;
	}



	//乗っ取り後
	if (b_mType == Type::PLAYER && !b_mEndFlag)
	{
		if (input->isKeyState(KEYCORD::ARROW_UP))
		{
			b_mVelocity.y -= 6;
		}
		if (input->isKeyState(KEYCORD::ARROW_DOWN))
		{
			b_mVelocity.y += 6;
		}
		if (input->isKeyState(KEYCORD::ARROW_RIGHT))
		{
			b_mVelocity.x += 6;
		}
		if (input->isKeyState(KEYCORD::ARROW_LEFT))
		{
			b_mVelocity.x -= 6;
		}
		if (input->isKeyDown(KEYCORD::SPACE))
		{
			Shot(Vector2(b_mPosittion.x, b_mPosittion.y));
		}
		if (input->isKeyState(KEYCORD::SPACE))
		{
			subShotCnt++;
			if (subShotCnt>20)
			{
				SubShot(Vector2(b_mPosittion.x, b_mPosittion.y));
				subShotCnt = 0;
			}
			b_mSpeed = 10.0f;
			
		}
		else
		{
			b_mSpeed = 20.0f;
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

		if (b_mHp <= 0)
		{
			b_mEndFlag = true;
		}

		b_mPosittion += b_mVelocity * deltaTime*b_mSpeed;
	}
}

void BomEnemy::draw(Renderer * renderer, Renderer3D* renderer3D)
{
	if (b_mType == Type::ENEMY)
	{
		DrawCircle(b_mPosittion.x + 64 / 2, b_mPosittion.y + 64 / 2, b_mCircleSize, GetColor(255, 0, 0), FALSE);
		renderer->draw2D("enemy3", Vector2(b_mPosittion.x, b_mPosittion.y), Vector2(0, 0), Vector2(64, 64), Vector2(32, 32), Vector2(1.0f, 1.0f), b_mAngle, 255);
	}
	else  if (!b_mEndFlag)
	{
		if (DamgeFlag)
		{
			b_mArpha = 155;
		}
		else
		{
			b_mArpha = 255;
		}


		DrawBox(0, 0, shotcnt, 100, GetColor(r, 0, b), TRUE);
		if (shotcnt == 100)
		{
			r = 255;
			b = 0;
		}

		DrawCircle(b_mPosittion.x + 64 / 2, b_mPosittion.y + 64 / 2, b_mCircleSize, GetColor(0, 0, 255), FALSE);
		b_mAngle = 0.0f;
		renderer->draw2D("enemy3", Vector2(b_mPosittion.x, b_mPosittion.y), Vector2(0, 0), Vector2(64, 64), Vector2(32, 32), Vector2(1.0f, 1.0f), b_mAngle, 255);
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

void BomEnemy::hit(BaseObject & other)
{
	
	if (other.getType() == Type::PLAYER_BULLET&&b_mType == Type::ENEMY)
	{
		b_mHp -= 1;
		DrawCircle(b_mPosittion.x + 64 / 2, b_mPosittion.y + 64 / 2, b_mCircleSize, GetColor(255, 255, 0), TRUE);
	}

	if (mTimer->timerSet(2))
	{
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

	}


	if (other.getType() == Type::CHANGE_BULLET&&b_mType == Type::ENEMY)
	{
		//最初は控えに
		b_mType = Type::SUB_PLAYER;
	}

}

void BomEnemy::Shot(Vector2 pos)
{
	charaManager->add(new Bullet(pos, charaManager, b_mType,0.0));
}

void BomEnemy::SubShot(Vector2 pos)
{
	charaManager->add(new BomBullet(pos, charaManager, b_mType));
}

void BomEnemy::CShot(Vector2 pos)
{
	charaManager->add(new ChangeBullet(pos, charaManager));
	shotcnt = 0;
	r = 0;
	b = 255;
}

void BomEnemy::Jibaku(Vector2 pos)
{
	charaManager->add(new Bom(pos, charaManager));
	b_mIsDeath = true;
}

