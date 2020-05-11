#include "CircleMoveEnemy.h"
#include <random>


CirecleMoveEnemy::CirecleMoveEnemy(Vector2 pos, CharactorManager * c) :m_pTimer(new Timer())
{
	charaManager = c;
	b_mPosittion = pos;
	m_pInput = new Input;
}

CirecleMoveEnemy::~CirecleMoveEnemy()
{
	delete m_pInput;
	delete m_pTimer;
}
bool CirecleMoveEnemy::PlayerNull()
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
void CirecleMoveEnemy::SubChange()
{
	b_mPosittion = KakoPos;
	b_mType = Type::PLAYER;
}
//初期化
void CirecleMoveEnemy::initialize()
{
	checkPlayerPos();
	b_mHp = 3;
	mMoveFlag = FALSE;

	m_pInput->init();
	b_mCircleSize = 16.0f;
	b_mType = Type::ENEMY;
	b_mAngle = 180.0f;
	m_pTimer->initialize();
	rotateSpeed = 0.5;//1周にかかる時間
	radius = 2;   //半径10
	b_mSpeed = 30.0f;
	shotcnt = 0;
	subShotCnt = 10;
	r = 0;
	b = 255;
}
//更新
void CirecleMoveEnemy::update(float deltaTime)
{
	m_pInput->update();
	m_pTimer->update(deltaTime);
	if (b_mType == Type::ENEMY)
	{
		move(deltaTime);
	}


	if (b_mType != Type::ENEMY)
	{
		playerMove(deltaTime);
	}
	
	

	b_mPosittion += b_mVelocity;
}

void CirecleMoveEnemy::draw(Renderer * renderer, Renderer3D* renderer3D)
{
	if (b_mType == Type::ENEMY)
	{
		DrawCircle(b_mPosittion.x + 64 / 2, b_mPosittion.y + 64 / 2, b_mCircleSize, GetColor(255, 0, 0), FALSE);
		renderer->draw2D("enemy2", Vector2(b_mPosittion.x, b_mPosittion.y), Vector2(0, 0), Vector2(64, 64), Vector2(32, 32), Vector2(1.0f, 1.0f), b_mAngle, 255);
	}
	else if(!b_mEndFlag)
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
		renderer->draw2D("enemy2", Vector2(b_mPosittion.x, b_mPosittion.y), Vector2(0, 0), Vector2(64, 64), Vector2(32, 32), Vector2(1.0f, 1.0f), b_mAngle, b_mArpha);
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

void CirecleMoveEnemy::hit(BaseObject & other)
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
		m_pTimer->initialize();
		DamgeFlag = TRUE;
	}
	if (other.getType() == Type::ENEMY&&b_mType == Type::PLAYER)
	{
		b_mHp -= 1;
		DrawCircle(b_mPosittion.x + 64 / 2, b_mPosittion.y + 64 / 2, b_mCircleSize, GetColor(255, 255, 0), TRUE);
		m_pTimer->initialize();
		DamgeFlag = TRUE;
	}

	if (other.getType() == Type::CHANGE_BULLET&&b_mType == Type::ENEMY)
	{
		//最初は控えに
		b_mType = Type::SUB_PLAYER;
	}
}

void CirecleMoveEnemy::Shot(Vector2 pos)
{
	charaManager->add(new Bullet(Vector2(b_mPosittion.x , b_mPosittion.y), charaManager, b_mType, 0.0f));
}

void CirecleMoveEnemy::SubShot(Vector2 pos)
{
	if (b_mType == Type::SUB_PLAYER||b_mType == Type::PLAYER)
	{
		charaManager->add(new Bullet(Vector2(b_mPosittion.x + 20, b_mPosittion.y), charaManager, b_mType, -30.0f));
		charaManager->add(new Bullet(Vector2(b_mPosittion.x - 20, b_mPosittion.y), charaManager, b_mType, 30.0f));
	}
	else
	{
		charaManager->add(new Bullet(Vector2(b_mPosittion.x + 20, b_mPosittion.y), charaManager, b_mType, 30.0f));
		charaManager->add(new Bullet(Vector2(b_mPosittion.x - 20, b_mPosittion.y), charaManager, b_mType, -30.0f));
	}
}


void CirecleMoveEnemy::CShot(Vector2 pos)
{
	charaManager->add(new ChangeBullet(pos, charaManager));
	shotcnt = 0;
	r = 0;
	b = 255;
}

void CirecleMoveEnemy::Jibaku(Vector2 pos)
{
	charaManager->add(new Bom(pos, charaManager));
	b_mIsDeath = true;
}

void CirecleMoveEnemy::move(float deltaTime)
{
	//敵以外ならリターン
	if (!b_mType == Type::ENEMY)return;
	moveTime += deltaTime * 4;
	x = 2 * radius* cos(moveTime* rotateSpeed);
	y = radius * sin(moveTime* rotateSpeed);
	b_mPosittion +=  Vector2(x,y);
	
	//画面外なら死ぬ
	deathArea();
}
//自分がプレイヤーの時の動き
void CirecleMoveEnemy::playerMove(float deltaTime)
{
	b_mVelocity = Vector2(0, 0);
	
	if (b_mType == Type::SUB_PLAYER)
	{
		b_mPosittion = charaManager->searchPlayer();
		if (m_pInput->isKeyState(KEYCORD::SPACE))
		{
			subShotCnt++;
			if (subShotCnt > 10)
			{
				SubShot(Vector2(b_mPosittion.x, b_mPosittion.y));
				subShotCnt = 0;
			}
			
		}
		else
		{
			subShotCnt = 0;
		}
		if (m_pInput->isKeyDown(KEYCORD::C))
		{
			Jibaku(Vector2(b_mPosittion.x, b_mPosittion.y));
		}

		if (!PlayerNull())
		{
			SubChange();
		}
		KakoPos = b_mPosittion;
	}
	

	if (b_mType == Type::PLAYER && !b_mEndFlag)
	{

		if (m_pInput->isKeyState(KEYCORD::ARROW_UP))
		{
			b_mVelocity.y -= 6;
		}
		if (m_pInput->isKeyState(KEYCORD::ARROW_DOWN))
		{
			b_mVelocity.y += 6;
		}
		if (m_pInput->isKeyState(KEYCORD::ARROW_RIGHT))
		{
			b_mVelocity.x += 6;
		}
		if (m_pInput->isKeyState(KEYCORD::ARROW_LEFT))
		{
			b_mVelocity.x -= 6;
		}
		if (m_pInput->isKeyDown(KEYCORD::SPACE))
		{
			Shot(Vector2(b_mPosittion.x, b_mPosittion.y));
		}
		if (m_pInput->isKeyState(KEYCORD::SPACE))
		{
			subShotCnt++;
			if (subShotCnt > 10)
			{
				SubShot(Vector2(b_mPosittion.x, b_mPosittion.y));
				subShotCnt = 0;
			}
			b_mSpeed = 15.0f;
		}
		else
		{
			b_mSpeed = 30.0f;
		}

		if (m_pInput->isKeyState(KEYCORD::V))
		{
			shotcnt++;
			if (shotcnt > 100)
			{
				shotcnt = 100;
			}
		}

		if (shotcnt == 100 && m_pInput->isKeyUp(KEYCORD::V))
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
//死亡処理
void CirecleMoveEnemy::deathArea()
{
	if (b_mPosittion.y > WindowInfo::WindowHeight
		|| b_mPosittion.x > WindowInfo::WindowWidth
		|| b_mPosittion.x < 0
		|| b_mHp <= 0)
	{
		b_mIsDeath = true;
	}
}
//プレイヤーの位置を調べる
void CirecleMoveEnemy::checkPlayerPos()
{
	//プレイヤーの位置を入れる
	mPlayerPos = charaManager->getPlayerPosition();
	Vector2 playerVec = mPlayerPos - b_mPosittion;  //プレイヤーとの差分
	b_mVelocity = playerVec.normalize();

}
