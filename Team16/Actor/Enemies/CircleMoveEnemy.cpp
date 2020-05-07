#include "CircleMoveEnemy.h"
#include <random>


CirecleMoveEnemy::CirecleMoveEnemy(Vector2 pos, CharactorManager * c) :m_pTimer(new Timer())
{
	m_pCharaManager = c;
	b_mPosittion = pos;
}

CirecleMoveEnemy::~CirecleMoveEnemy()
{
	delete m_pInput;
	delete m_pTimer;
}
//初期化
void CirecleMoveEnemy::initialize()
{
	checkPlayerPos();
	b_mHp = 100;
	mMoveFlag = FALSE;
	m_pInput = new Input;
	m_pInput->init();
	b_mCircleSize = 16.0f;
	b_mType = Type::ENEMY;
	b_mAngle = 180.0f;
	m_pTimer->initialize();
	rotateSpeed = 0.5;//1周にかかる時間
	radius = 2;   //半径10
}
//更新
void CirecleMoveEnemy::update(float deltaTime)
{
	m_pInput->update();
	m_pTimer->update(deltaTime);
	
	deathArea();
	move(deltaTime);
	playerMove(deltaTime);

	b_mPosittion += b_mVelocity;
}

void CirecleMoveEnemy::draw(Renderer * renderer, Renderer3D* renderer3D)
{
	if (b_mType == Type::ENEMY)
	{
		DrawCircle(b_mPosittion.x + 64 / 2, b_mPosittion.y + 64 / 2, b_mCircleSize, GetColor(255, 0, 0), FALSE);
		renderer->draw2D("enemy2", Vector2(b_mPosittion.x, b_mPosittion.y), Vector2(0, 0), Vector2(64, 64), Vector2(32, 32), Vector2(1.0f, 1.0f), b_mAngle, 255);
	}
	else if (!b_mEndFlag)
	{
		DrawCircle(b_mPosittion.x + 64 / 2, b_mPosittion.y + 64 / 2, b_mCircleSize, GetColor(0, 0, 255), FALSE);
		b_mAngle = 0.0f;
		renderer->draw2D("enemy2", Vector2(b_mPosittion.x, b_mPosittion.y), Vector2(0, 0), Vector2(64, 64), Vector2(32, 32), Vector2(1.0f, 1.0f), b_mAngle, 255);
		renderer->drawNumber("hpNumber", Vector2(150, 10), b_mHp, 0, Vector2(0, 0), Vector2(1, 1), 0.0f, 255);
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
	
	if (other.getType() == Type::CHANGE_BULLET&&b_mType == Type::ENEMY)
	{
		b_mType = Type::PLAYER;
	}

}

void CirecleMoveEnemy::Shot(Vector2 pos)
{
	m_pCharaManager->add(new Bullet(Vector2(b_mPosittion.x , b_mPosittion.y), m_pCharaManager, b_mType));
}


void CirecleMoveEnemy::CShot(Vector2 pos)
{
	m_pCharaManager->add(new ChangeBullet(pos, m_pCharaManager));
}

void CirecleMoveEnemy::Jibaku(Vector2 pos)
{
	m_pCharaManager->add(new Bom(pos, m_pCharaManager));
	b_mIsDeath = true;
	m_pCharaManager->add(new Player(pos, m_pCharaManager));
}

void CirecleMoveEnemy::move(float deltaTime)
{
	//敵以外ならリターン
	if (!b_mType == Type::ENEMY)return;
	moveTime += deltaTime * 4;
	x = 2 * radius* cos(moveTime* rotateSpeed);
	y = radius * sin(moveTime* rotateSpeed);
	b_mPosittion +=  Vector2(x,y);
	//b_mVelocity.y += 2;
	//画面外なら死ぬ
	deathArea();
}
//自分がプレイヤーの時の動き
void CirecleMoveEnemy::playerMove(float deltaTime)
{
	//乗っ取り後    プレイヤーじゃなければリターン
	if (!(b_mType == Type::PLAYER && !b_mEndFlag))return;
	b_mVelocity = Vector2(0, 0);
	if (m_pInput->isKeyState(KEYCORD::ARROW_UP))
	{
		b_mVelocity.y -= 3;
	}
	if (m_pInput->isKeyState(KEYCORD::ARROW_DOWN))
	{
		b_mVelocity.y += 3;
	}
	if (m_pInput->isKeyState(KEYCORD::ARROW_RIGHT))
	{
		b_mVelocity.x += 3;
	}
	if (m_pInput->isKeyState(KEYCORD::ARROW_LEFT))
	{
		b_mVelocity.x -= 3;
	}
	if (m_pInput->isKeyDown(KEYCORD::SPACE))
	{
		Shot(Vector2(b_mPosittion.x, b_mPosittion.y));
	}
	if (m_pInput->isKeyDown(KEYCORD::X))
	{
		CShot(Vector2(b_mPosittion.x, b_mPosittion.y));
	}
	if (m_pInput->isKeyDown(KEYCORD::C))
	{
		Jibaku(Vector2(b_mPosittion.x, b_mPosittion.y));
	}
	if (b_mHp <= 0)
	{
		b_mEndFlag = true;
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
	mPlayerPos = m_pCharaManager->getPlayerPosition();
	Vector2 playerVec = mPlayerPos - b_mPosittion;  //プレイヤーとの差分
	b_mVelocity = playerVec.normalize();

}
