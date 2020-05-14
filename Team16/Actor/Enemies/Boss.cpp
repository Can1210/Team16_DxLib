#include "Boss.h"
#include"../../Scene/GamePlay.h"
#include "../Bulletes/AngleBullet.h"
#include"../../Device/Sound.h"

Boss::Boss(Vector2 pos, CharactorManager * c) :
	mTimer(new Timer()),
	m_pCirecleTimer(new Timer()),
	m_pCirecleEndTimer(new Timer())
{
	charaManager = c;
	b_mPosittion = pos;
}

Boss::~Boss()
{
	delete input;
	delete mTimer;
	delete m_pCirecleTimer;
	delete m_pCirecleEndTimer;
}

void Boss::initialize()
{
	b_mHp = 30;

	input = new Input;
	input->init();
	b_mCircleSize = 64.0f;
	b_mType = Type::BOSS;
	b_mAngle = 180.0f;
	mTimer->initialize();
    m_pCirecleTimer->initialize();
    m_pCirecleEndTimer->initialize();

	b_mSpeed = 20.0f;
	shotcnt = 0;
	r = 0;
	b = 255;
}

void Boss::update(float deltaTime)
{
	input->update();
	mTimer->update(deltaTime);
	m_pCirecleTimer->update(deltaTime);
	b_mVelocity = Vector2(0, 0);


	//無敵時間
	if (DamgeFlag&&mTimer->timerSet(2))
	{
		DamgeFlag = FALSE;
	}


	

	if (b_mType == Type::SUB_PLAYER)
	{
		b_mPosittion = charaManager->searchPlayer();
		if (input->isKeyDown(KEYCORD::SPACE))
		{
			Shot(Vector2(b_mPosittion.x, b_mPosittion.y));
		}
		if (input->isKeyDown(KEYCORD::C))
		{
			Jibaku(Vector2(b_mPosittion.x, b_mPosittion.y));
		}
		if (!SubNull())
		{
			SubChange();
		}
		KakoPos = b_mPosittion;
	}


	if (b_mType == Type::BOSS)
	{
		b_mVelocity.y += 2;

		if (b_mPosittion.y > 150)
		{
			b_mVelocity = Vector2(0, 0);
		}


		if (mTimer->timerSet(2))
		{
			Shot(Vector2(b_mPosittion.x, b_mPosittion.y));
		}

		////円状の攻撃
		if (m_pCirecleTimer->timerSet_Self(10.0f))
		{
 			circleShot(deltaTime);
		}
		else
			shotAngle = 0.0f;


		if (b_mHp <= 0)
		{
			Sound::getInstance().playSE("burst01");
			b_mIsDeath = true;
			Score::getInstance().addScore(66666);
			GamePlay::BossEnd = true;
		}
		
		if (b_mPosittion.y > WindowInfo::WindowHeight
			|| b_mPosittion.x > WindowInfo::WindowWidth
			|| b_mPosittion.x < 0)
		{
			b_mIsDeath = true;
		}
		b_mPosittion += b_mVelocity;
	}




	
}

void Boss::draw(Renderer * renderer, Renderer3D * renderer3D)
{
	if (b_mType == Type::BOSS)
	{
		DrawCircle(b_mPosittion.x + 64 / 2, b_mPosittion.y + 64 / 2, b_mCircleSize, GetColor(255, 0, 0), FALSE);

		renderer->draw2D("enemy2", Vector2(b_mPosittion.x, b_mPosittion.y), Vector2(0, 0), Vector2(64, 64), Vector2(32, 32), Vector2(3.0f, 3.0f), b_mAngle, 255);
		renderer->draw2D("enemy3", Vector2(b_mPosittion.x, b_mPosittion.y), Vector2(0, 0), Vector2(64, 64), Vector2(32, 32), Vector2(3.0f, 3.0f), b_mAngle, 255);
		
	}
	else if (!b_mEndFlag)
	{


		DrawCircle(b_mPosittion.x + 64 / 2, b_mPosittion.y + 64 / 2, b_mCircleSize, GetColor(0, 0, 255), FALSE);
		b_mAngle = 0.0f;

		renderer->draw2D("enemy2", Vector2(b_mPosittion.x, b_mPosittion.y), Vector2(0, 0), Vector2(64, 64), Vector2(32, 32), Vector2(3.0f, 3.0f), b_mAngle, 255);
		renderer->draw2D("enemy3", Vector2(b_mPosittion.x, b_mPosittion.y), Vector2(0, 0), Vector2(64, 64), Vector2(32, 32), Vector2(3.0f, 3.0f), b_mAngle, 255);
	
	}
	

}

void Boss::hit(BaseObject & other)
{
	if (other.getType() == Type::PLAYER_BULLET&&b_mType == Type::BOSS)
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




	//if (other.getType() == Type::CHANGE_BULLET&&b_mType == Type::ENEMY)
	//{
	//	//最初は控えに
	//	b_mType = Type::SUB_PLAYER;
	//}
}

void Boss::Shot(Vector2 pos)
{
	if (b_mType == Type::PLAYER|| b_mType == Type::SUB_PLAYER)
	{
		charaManager->add(new Bullet(Vector2(b_mPosittion.x + 20, b_mPosittion.y), charaManager, b_mType, -30.0f));
		charaManager->add(new Bullet(Vector2(b_mPosittion.x - 20, b_mPosittion.y), charaManager, b_mType, 30.0f));

		charaManager->add(new Bullet(Vector2(b_mPosittion.x + 40, b_mPosittion.y), charaManager, b_mType, -30.0f));
		charaManager->add(new Bullet(Vector2(b_mPosittion.x - 40, b_mPosittion.y), charaManager, b_mType, 30.0f));
		charaManager->add(new BomBullet(pos, charaManager, b_mType));
	}
	else
	{
		charaManager->add(new Bullet(Vector2(b_mPosittion.x + 20, b_mPosittion.y), charaManager, b_mType, 30.0f));
		charaManager->add(new Bullet(Vector2(b_mPosittion.x - 20, b_mPosittion.y), charaManager, b_mType, -30.0f));

		charaManager->add(new Bullet(Vector2(b_mPosittion.x + 40, b_mPosittion.y), charaManager, b_mType, 30.0f));
		charaManager->add(new Bullet(Vector2(b_mPosittion.x - 40, b_mPosittion.y), charaManager, b_mType, -30.0f));

		charaManager->add(new BomBullet(pos, charaManager, b_mType));
	}
}

void Boss::CShot(Vector2 pos)
{
	charaManager->add(new ChangeBullet(pos, charaManager));
	shotcnt = 0;
	r = 0;
	b = 255;
}

void Boss::Jibaku(Vector2 pos)
{
	
	charaManager->add(new Bom(pos, charaManager));
	b_mIsDeath = true;
}

//円攻撃
void Boss::circleShot(float deltaTime)
{
	
	m_pCirecleEndTimer->update(deltaTime);
	//円攻撃時間の設定
	if (m_pCirecleEndTimer->timerSet(2.0f))
		m_pCirecleTimer->initialize();

	charaManager->add(new AngleBullet(Vector2(b_mPosittion.x+32, b_mPosittion.y + 64), charaManager, b_mType, shotAngle));
	shotAngle += 10.0f;
}

bool Boss::getIsDeath() const
{
	return b_mIsDeath;
}

Type Boss::getType() const
{
	return b_mType;
}


float Boss::getCircleSize() const
{
	return b_mCircleSize;
}

void Boss::setIsDeath(bool isDeath)
{
	b_mIsDeath = isDeath;
}

bool Boss::SubNull()
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

void Boss::SubChange()
{
	b_mPosittion = KakoPos;
	b_mType = Type::PLAYER;
}
