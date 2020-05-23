#include "WallReflectionEnemy.h"
#include <random>
#include "../Bulletes/WallReflectionBullet.h"
#include"../../Device/Sound.h"

WallReflectionEnemy::WallReflectionEnemy(Vector2 pos, CharactorManager * c) :m_pTimer(new Timer())
{
	charaManager = c;
	b_mPosittion = pos;
	m_pInput = new Input;
}

WallReflectionEnemy::~WallReflectionEnemy()
{
	delete m_pInput;
	delete m_pTimer;
}

//初期化
void WallReflectionEnemy::initialize()
{
	b_mVelocity = checkPlayerPos(b_mVelocity);
	b_mHp = 2;
	mMoveFlag = FALSE;

	m_pInput->init();
	b_mCircleSize = 16.0f;
	b_mType = Type::ENEMY;
	b_mAngle = 180.0f;
	m_pTimer->initialize();
	rotateSpeed = 0.5;//1周にかかる時間
	radius = 2;   //半径10
	b_mSpeed = 30.0f;
	subShotCnt = 10;
	b_mArpha = 255;
	itemCnt = 0;
	itemDesthCnt = 50.0f;

	startPos = Vector2(300.0f - 64.0f, 200.0f);
	startEnd = false;
	shottime = 0;
}
//更新
void WallReflectionEnemy::update(float deltaTime)
{
	m_pInput->update();
	m_pTimer->update(deltaTime);

	if (b_mType == Type::ENEMY)
	{
		if (!startEnd)
		{
			Vector2 v = (b_mPosittion - startPos);
			float length = Vector2((b_mPosittion - startPos)).length();
			if (length < 2.0f)
			{
				startEnd = true;
			}
			v = v.normalize();
			b_mPosittion += -v * deltaTime * 120.0f;
			return;
		}
		move(deltaTime);

		shottime++;
	}


	if (b_mType == Type::SUB_PLAYER1 || b_mType == Type::SUB_PLAYER2)
	{
		playerMove(deltaTime);
		b_mPosittion += b_mVelocity;
	}
	//ドロップ後処理
	if (b_mType == Type::ITEM)
	{
		b_mVelocity = (Vector2(0, 1.0f));
		b_mSpeed = 120.0f;
		b_mPosittion += b_mVelocity * deltaTime * b_mSpeed;
		itemCnt++;
		itemDesthCnt -= 0.25f;
		if (itemCnt > 150)
		{
			Sound::getInstance().playSE("burst02");
			b_mIsDeath = true;
		}
	}
}

void WallReflectionEnemy::draw(Renderer * renderer, Renderer3D* renderer3D)
{
	if (b_mType == Type::ENEMY)
	{
		DrawCircle(b_mPosittion.x + 64 / 2, b_mPosittion.y + 64 / 2, b_mCircleSize, GetColor(255, 0, 0), FALSE);
		renderer->draw2D("enemy2", Vector2(b_mPosittion.x, b_mPosittion.y), Vector2(0, 0), Vector2(64, 64), Vector2(32, 32), Vector2(1.3f, 1.3f), b_mAngle, 255);
	}
	if (b_mType == Type::SUB_PLAYER1 || b_mType == Type::SUB_PLAYER2)
	{
		b_mAngle = 0.0f;
		renderer->draw2D("enemy2", Vector2(b_mPosittion.x, b_mPosittion.y), Vector2(0, 0), Vector2(64, 64), Vector2(32, 32), Vector2(1.3f, 1.3f), b_mAngle, b_mArpha);

	}
	if (b_mType == Type::ITEM)
	{
		DrawCircle(b_mPosittion.x + 64 / 2, b_mPosittion.y + 64 / 2, itemDesthCnt, GetColor(0, 255, 0), FALSE);
		renderer->draw2D("enemy2", Vector2(b_mPosittion.x, b_mPosittion.y), Vector2(0, 0), Vector2(64, 64), Vector2(32, 32), Vector2(1.3f, 1.3f), b_mAngle, b_mArpha);
	}

}

void WallReflectionEnemy::hit(BaseObject & other)
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
		switch (subChack())
		{
		case true:
			b_mType = Type::SUB_PLAYER2;
			break;
		case false:
			b_mType = Type::SUB_PLAYER1;
			break;
		default:
			break;
		}
	}


}

void WallReflectionEnemy::Shot(Vector2 pos)
{

	//Vector2 angleVec = Vector2(0, 0);
	//angleVec = checkPlayerPos(angleVec);  //角度を代入
	////角度に変換
	//float angle = atan2(-angleVec.y, angleVec.x)* 180.0f / DX_PI_F;
	int angle = 270;

#if 0

	switch (shottime)
	{
	case 12:
		charaManager->add(new WallReflectionBullet(Vector2(b_mPosittion.x, b_mPosittion.y) + Vector2(32, 32), charaManager, b_mType, angle - 70 - 4));
			break;
	case 12 * 2:
		charaManager->add(new WallReflectionBullet(Vector2(b_mPosittion.x, b_mPosittion.y) + Vector2(32, 32), charaManager, b_mType, angle - 72 - 4));
		break;
	case 12 * 3:
		charaManager->add(new WallReflectionBullet(Vector2(b_mPosittion.x, b_mPosittion.y) + Vector2(32, 32), charaManager, b_mType, angle - 74 - 4));
		break;
	case 12 * 4:
		charaManager->add(new WallReflectionBullet(Vector2(b_mPosittion.x, b_mPosittion.y) + Vector2(32, 32), charaManager, b_mType, angle - 76 - 4));
		break;
	case 12 * 5:
		charaManager->add(new WallReflectionBullet(Vector2(b_mPosittion.x, b_mPosittion.y) + Vector2(32, 32), charaManager, b_mType, angle - 78 - 4));
		break;
	case 12 * 5 * 2:
		shottime = 0;
		break;
	}

#elif 1

	if (shottime % 60 * 2 == 0)
	{
		charaManager->add(new WallReflectionBullet(Vector2(b_mPosittion.x, b_mPosittion.y) + Vector2(32, 32), charaManager, b_mType, angle - 60));
		charaManager->add(new WallReflectionBullet(Vector2(b_mPosittion.x, b_mPosittion.y) + Vector2(32, 32), charaManager, b_mType, angle + 60));
	}

	if (shottime % 60 * 3 == 0)
	{
		charaManager->add(new WallReflectionBullet(Vector2(b_mPosittion.x, b_mPosittion.y) + Vector2(32, 32), charaManager, b_mType, angle - 40));
		charaManager->add(new WallReflectionBullet(Vector2(b_mPosittion.x, b_mPosittion.y) + Vector2(32, 32), charaManager, b_mType, angle + 40));
	}

	if (shottime % 60 * 4 == 0)
	{
		shottime = 0;
	}

#endif // 0

}

void WallReflectionEnemy::SubShot(Vector2 pos)
{
	if (b_mType == Type::SUB_PLAYER1 || b_mType == Type::SUB_PLAYER2)
	{
		charaManager->add(new WallReflectionBullet(Vector2(b_mPosittion.x, b_mPosittion.y) + Vector2(32, 32), charaManager, b_mType, 90 - 60));
		charaManager->add(new WallReflectionBullet(Vector2(b_mPosittion.x, b_mPosittion.y) + Vector2(32, 32), charaManager, b_mType, 90 + 60));
	}																																	  
	else																																  
	{																																	  
		charaManager->add(new WallReflectionBullet(Vector2(b_mPosittion.x, b_mPosittion.y) + Vector2(32, 32), charaManager, b_mType, 90 - 60));
		charaManager->add(new WallReflectionBullet(Vector2(b_mPosittion.x, b_mPosittion.y) + Vector2(32, 32), charaManager, b_mType, 90 + 60));
	}
}


void WallReflectionEnemy::Jibaku(Vector2 pos)
{
	Sound::getInstance().playSE("burst02");
	charaManager->add(new Bom(pos, charaManager));
	b_mIsDeath = true;
}

void WallReflectionEnemy::move(float deltaTime)
{
	//敵以外ならリターン
	if (!b_mType == Type::ENEMY)return;
	moveTime += deltaTime * 1.0f;
	x = radius * cos(moveTime * rotateSpeed);
	y = radius * cos(moveTime * rotateSpeed * 2.0f);
	b_mPosittion += Vector2(x, y) * 1.0f;

	if (b_mHp <= 0)
	{
		b_mType = Type::ITEM;
		Score::getInstance().addScore(200);
	}

	Shot(b_mPosittion);

	//画面外なら死ぬ
	deathArea();
}
//自分がプレイヤーの時の動き
void WallReflectionEnemy::playerMove(float deltaTime)
{
	b_mVelocity = Vector2(0, 0);

	if (b_mType == Type::SUB_PLAYER1)
	{
		b_mPosittion = charaManager->searchPlayer() + Vector2(-30, 30);
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


	}

	if (b_mType == Type::SUB_PLAYER2)
	{
		b_mPosittion = charaManager->searchPlayer() + Vector2(30, 30);
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

	}

}
//死亡処理
void WallReflectionEnemy::deathArea()
{
	if (b_mPosittion.y > WindowInfo::WindowHeight
		|| b_mPosittion.x > WindowInfo::WindowWidth
		|| b_mPosittion.x < 0
		)
	{
		b_mIsDeath = true;
	}
}
//プレイヤーの位置を調べる
Vector2 WallReflectionEnemy::checkPlayerPos(Vector2 vec)
{
	//プレイヤーの位置を入れる
	mPlayerPos = charaManager->getPlayerPosition();
	Vector2 playerVec = mPlayerPos - b_mPosittion;  //プレイヤーとの差分
	return playerVec.normalize();

}

bool WallReflectionEnemy::subChack()
{
	for (auto object : charaManager->getUseList())
	{
		if (object->getType() == Type::SUB_PLAYER1)
		{
			return true;//いたらtrue
		}
	}
	return false;
}
