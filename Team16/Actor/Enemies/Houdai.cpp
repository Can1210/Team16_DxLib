#include <random>
#include"Houdai.h"
#include "../Bulletes/Bullet.h"
#include "../Bulletes/AngleBullet.h"
#include"../Bulletes/TrakingBullet.h"
#include"../Bulletes/BomBallet.h"
#include "../Item/Item.h"
bool Houdai::lostHoudai;
Houdai::Houdai(Vector2 pos, CharactorManager *c) :mTimer(new Timer()), mTimerDamege(new Timer()),mTimerBom(new Timer())
{
	charaManager = c;
	b_mPosittion = pos;
}

Houdai::~Houdai()
{
	delete mTimer;
	delete mTimerDamege;
	delete mTimerBom;
	
}
void Houdai::initialize()
{
	b_mVelocity = checkPlayerPos(b_mVelocity);
	b_mHp = 30;
	b_mCircleSize = 32.0f;
	b_mType = Type::ENEMY;
	b_mAngle = 180.0f;
	b_mArpha = 255;
	mTimer->initialize();
	mTimerBom->initialize();
	
	b_animCnt = 0.0f;
	mDamageHit = 255;

	lostHoudai = false;
	//ボム用
	ShotRing = 200.0f;
	UltFlag = false;
	shotFlag = true;//ボム打ってるときは通常射撃してほしくないので
}

void Houdai::update(float deltaTime)
{
	mTimer->update(deltaTime);
	mTimerBom->update(deltaTime);
	Vector2 angleVec = Vector2(0, 0);
	angleVec = checkPlayerPos(angleVec);  //角度を代入
	//角度に変換
	float angle = atan2(-angleVec.y, angleVec.x)* 180.0f / DX_PI_F;
	ShotAngle = angle;
	if (mTimer->timerSet(2.0f)&&shotFlag == true)
	{
		Shot(Vector2(b_mPosittion.x, b_mPosittion.y));
	}
	//予兆
	
	if (mTimerBom->timerSet_Self(8.0f))
	{
		UltFlag = true;
		shotFlag = false;
		if (ShotRing <=0)
		{
			BomShot(Vector2(b_mPosittion.x, b_mPosittion.y));
		}
		ShotRing -= 10.0f;
	}
	else
	{
		ShotRing = 200.0f;
		UltFlag = false;
	}
	
	mTimerDamege->update(deltaTime);
	if (mTimerDamege->timerSet_Self(0.2f))
	{
		mDamageHit = 255;
	}
	//b_mPosittion -= b_mVelocity * b_mSpeed * deltaTime;
}

void Houdai::draw(Renderer * renderer, Renderer3D* renderer3D)
{
	renderer3D->draw3DTexture("houdai", Vector3(b_mPosittion.x, b_mPosittion.y, 0.0f), Vector2(0.0f, 0.0f), Vector2(64.0f, 64.0f), 96.0f*2, ShotAngle+90.0f,255,Vector2(0.5f,0.5f), Vector3((float)255, (float)mDamageHit, (float)mDamageHit));
	if (b_mHp <= 0)
	{
		b_animCnt += 64.0f;
		if (b_animCnt >= 1022.0f)
		{
			Score::getInstance().addScore(100);

			if (GetRand(2) == 2)
			{
				charaManager->add(new Item(b_mPosittion, BulletType::T_Bullet, "enemy")); 
				b_mIsDeath = true;
				lostHoudai = true;
			}

			b_mIsDeath = true;
			lostHoudai = true;
		}
		renderer3D->draw3DTexture("deathBurst", Vector3(b_mPosittion.x, b_mPosittion.y, 0.0f), Vector2(b_animCnt, 0.0f), Vector2(64.0f, 64.0f), 140.0f, b_mAngle);
	}

	if (UltFlag == true)
	{
		renderer3D->draw3DTexture("bossBullet", Vector3(b_mPosittion.x, b_mPosittion.y, 0.0f), Vector2(0.0f, 0.0f), Vector2(10.0f, 12.0f), ShotRing, 0.0f, 125);
	}
	//renderer->draw2D("enemy", Vector2(b_mPosittion.x, b_mPosittion.y), Vector2(0, 0), Vector2(64, 64), Vector2(32, 32), Vector2(1.3f, 1.3f), b_mAngle, 255);

}

void Houdai::hit(BaseObject & other)
{
	if (other.getType() == Type::PLAYER_BULLET&&b_mType == Type::ENEMY)
	{
		mDamageHit = 0;
		mTimerDamege->initialize();
		b_mHp -= charaManager->getPlayerBulletDamage();
	}
}

void Houdai::ultAtak(float deltaTime)
{
}

void Houdai::Shot(Vector2 pos)
{
	Vector2 angleVec = Vector2(0, 0);
	angleVec = checkPlayerPos(angleVec);
	float angle = atan2(-angleVec.y, angleVec.x)* 180.0f / DX_PI_F;
	charaManager->add(new AngleBullet(Vector2(b_mPosittion.x, b_mPosittion.y), charaManager, b_mType, angle - 20.0f));
	charaManager->add(new AngleBullet(Vector2(b_mPosittion.x, b_mPosittion.y), charaManager, b_mType, angle));
	charaManager->add(new AngleBullet(Vector2(b_mPosittion.x, b_mPosittion.y), charaManager, b_mType, angle + 20.0f));
}

void Houdai::BomShot(Vector2 pos)
{
	Vector2 angleVec = Vector2(0, 0);
	angleVec = checkPlayerPos(angleVec);
	float angle = atan2(-angleVec.y, angleVec.x)* 180.0f / DX_PI_F;
	charaManager->add(new BomBullet(Vector2(b_mPosittion.x, b_mPosittion.y), charaManager, b_mType,angle+180.0f));
	shotFlag = true;
	UltFlag = false;
	ShotRing = 200.0f;
	mTimerBom->initialize();
}



Vector2 Houdai::checkPlayerPos(Vector2 vec)
{
	//プレイヤーの位置を入れる
	Vector2 playerPos = charaManager->getPlayerPosition();
	Vector2 playerVec = playerPos - b_mPosittion;  //プレイヤーとの差分
	return playerVec.normalize();
}
