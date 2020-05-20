#include <random>
#include"BomEnemy.h"
#include"../../Device/Sound.h"

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




void BomEnemy::initialize()
{
	b_mHp = 3;

	
	input->init();
	b_mCircleSize = 16.0f;
	b_mType = Type::ENEMY;
	b_mAngle = 180.0f;
	mTimer->initialize();
	b_mSpeed = 20.0f;
	subShotCnt = 20;
	b_mArpha = 255;
	itemCnt = 0;
	itemDesthCnt = 50.0f;
}

void BomEnemy::update(float deltaTime)
{
	mTimer->update(deltaTime);

	input->update();
	b_mVelocity = Vector2(0, 0);

	
	if (b_mType == Type::SUB_PLAYER)
	{
		b_mPosittion = charaManager->searchPlayer();
		if (input->isKeyState(KEYCORD::SPACE))
		{
			subShotCnt++;
			if (subShotCnt > 20)
			{
			    Shot(Vector2(b_mPosittion.x, b_mPosittion.y));
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
		
	}


	if (b_mType == Type::ENEMY)
	{
		b_mVelocity.y += 1;
		if (mTimer->timerSet(3.0f))
		{
			SubShot(Vector2(b_mPosittion.x, b_mPosittion.y));
		}
		if (b_mHp <= 0)
		{
			b_mType = Type::ITEM;
			Score::getInstance().addScore(300);
		}
		if (b_mPosittion.y > WindowInfo::WindowHeight
			|| b_mPosittion.x>WindowInfo::WindowWidth
			|| b_mPosittion.x < 0
			)
		{
			b_mIsDeath = true;
		}



		b_mPosittion += b_mVelocity * deltaTime*b_mSpeed;
	}


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
	
}

void BomEnemy::draw(Renderer * renderer, Renderer3D* renderer3D)
{
	if (b_mType == Type::ENEMY)
	{
		DrawCircle(b_mPosittion.x + 64 / 2, b_mPosittion.y + 64 / 2, b_mCircleSize, GetColor(255, 0, 0), FALSE);
		renderer->draw2D("enemy3", Vector2(b_mPosittion.x, b_mPosittion.y), Vector2(0, 0), Vector2(64, 64), Vector2(32, 32), Vector2(1.0f, 1.0f), b_mAngle, 255);
	}
   if(b_mType == Type::SUB_PLAYER)
	{
	
		b_mAngle = 0.0f;
		renderer->draw2D("enemy3", Vector2(b_mPosittion.x, b_mPosittion.y), Vector2(0, 0), Vector2(64, 64), Vector2(32, 32), Vector2(1.0f, 1.0f), b_mAngle, 255);
		if (b_mType == Type::PLAYER)
		{
			renderer->drawNumber("hpNumber", Vector2(150, 10), b_mHp, 0, Vector2(0, 0), Vector2(1, 1), 0.0f, 255);
		}
	}
	if (b_mType == Type::ITEM)
	{
		DrawCircle(b_mPosittion.x + 64 / 2, b_mPosittion.y + 64 / 2, itemDesthCnt, GetColor(0, 255, 0), FALSE);
		renderer->draw2D("enemy3", Vector2(b_mPosittion.x, b_mPosittion.y), Vector2(0, 0), Vector2(64, 64), Vector2(32, 32), Vector2(1.0f, 1.0f), b_mAngle, b_mArpha);
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


	if (other.getType() == Type::PLAYER&&b_mType == Type::ITEM)
	{
		//最初は控えに
		b_mType = Type::SUB_PLAYER;
	}

}

void BomEnemy::Shot(Vector2 pos)
{
	Vector2 angleVec = Vector2(0, 0);
	//angleVec = checkPlayerPos(angleVec);  //角度を代入
	//角度に変換
	//float angle = atan2(-angleVec.y, angleVec.x)* 180.0f / DX_PI_F;
	//3Wayに変更する
	charaManager->add(new AngleBullet(pos + Vector2(32, 32), charaManager, b_mType, 90.0f - 30.0f));
	charaManager->add(new AngleBullet(pos + Vector2(32, 32), charaManager, b_mType, 90.0f));
	charaManager->add(new AngleBullet(pos + Vector2(32, 32), charaManager, b_mType, 90.0f + 30.0f));
}

void BomEnemy::SubShot(Vector2 pos)
{
	//charaManager->add(new BomBullet(pos, charaManager, b_mType));
	//射撃許可ラインよりより下にいたら撃たない
	if (!isShot()) return;

	Vector2 angleVec = Vector2(0, 0);
	angleVec = checkPlayerPos(angleVec);  //角度を代入
	//角度に変換
	float angle = atan2(-angleVec.y, angleVec.x)* 180.0f / DX_PI_F;
	//3Wayに変更する
	charaManager->add(new AngleBullet(pos + Vector2(32,32), charaManager, b_mType, angle - 30.0f));
	charaManager->add(new AngleBullet(pos + Vector2(32,32), charaManager, b_mType, angle));
	charaManager->add(new AngleBullet(pos + Vector2(32,32), charaManager, b_mType, angle + 30.0f));
}												  


void BomEnemy::Jibaku(Vector2 pos)
{
	Sound::getInstance().playSE("burst02");
	charaManager->add(new Bom(pos, charaManager));
	b_mIsDeath = true;
}

Vector2 BomEnemy::checkPlayerPos(Vector2 vec)
{
	//プレイヤーの位置を入れる
	mPlayerPos = charaManager->getPlayerPosition();
	Vector2 playerVec = mPlayerPos - b_mPosittion;  //プレイヤーとの差分
	return playerVec.normalize();
}
//射撃してほしいかどうか
bool BomEnemy::isShot()
{
	if (b_mPosittion.y <= charaManager->getPlayerPosition().y - 64 * 2)
	{
		return true;
	}

	return false;
}

