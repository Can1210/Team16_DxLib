#include "Boss.h"
#include "../../Scene/GamePlay.h"
#include "../Bulletes/AngleBullet.h"
#include "../Bulletes/Bom.h"
#include "../Bulletes/Bullet.h"
#include "../../Device/Camera.h"


Boss::Boss(Vector2 pos, CharactorManager * c) :
	mTimer(new Timer()),
	m_pCirecleTimer(new Timer()),
	m_pCirecleEndTimer(new Timer()),
	m_pCamreraTimer(new Timer()),
	mTimerDamege(new Timer()),
	mAnimTimer(new Timer()),
	mEndTimer(new Timer())
{
	charaManager = c;
	b_mPosittion = pos;

}

Boss::~Boss()
{
	delete mTimer;
	delete m_pCirecleTimer;
	delete m_pCirecleEndTimer;
	delete mTimerDamege;
	delete mAnimTimer;
	delete mEndTimer;
}

void Boss::initialize()
{
	b_mHp =  150;
	b_mCircleSize = 64.0f;
	b_mType = Type::BOSS;
	b_mAngle = 0.0f;
	b_mSpeed = 20.0f;
	mTimer->initialize();
	mTimerDamege->initialize();
	mDamageHit = 255;
    m_pCirecleTimer->initialize();
    m_pCirecleEndTimer->initialize();
	mAnimTimer->initialize();
	mEndTimer->initialize();
	bomshotAngle = 180.0f;
	//円
	rotateSpeed = 0.5f;//1周にかかる時間
	radius = 5.0f;   //半径10
	//溜め
	mIsCharge = false;
	mChargeScalse = 400.0f;
	mDamageHit = 255;
	isAnim = false;    //画像切り替えを開始する
	isChange = false;
}

void Boss::update(float deltaTime)
{
	if (isChange)
	{
		mEndTimer->update(deltaTime);
		if (mEndTimer->timerSet(3.0f))
		{
			b_mIsDeath = true;  //死亡
		}
	}
	if (isAnim)
	{
		mDamageHit = 255;
		mAnimTimer->update(deltaTime);
		if (mAnimTimer->timerSet_Self(2.0f))
		{
			isChange = true;
		}
	}
	if (isAnim) return;

	b_mVelocity = Vector2(0, 0);
	mTimer->update(deltaTime);
	mTimerDamege->update(deltaTime);
	if (mTimerDamege->timerSet_Self(0.2f))
	{
		mDamageHit = 255;
	}
	m_pCirecleTimer->update(deltaTime);
	m_pCamreraTimer->update(deltaTime);
	if (m_pCamreraTimer->timerSet_Self(3.0f))
	{
		Camera::getInstance().setStop(true);
	}
	else
		b_mVelocity.y = 2;
	//無敵時間
	if (DamgeFlag&&mTimer->timerSet(2))DamgeFlag = false;
	attack(deltaTime);
	if (b_mHp <= 0)
	{
		Sound::getInstance().playSE("burst01");
		isAnim = true;
		//b_mIsDeath = true;
		Score::getInstance().addScore(66666);
		GamePlay::BossEnd = true;
	}
	
	//今だけ
	b_mPosittion -= b_mVelocity * b_mSpeed * deltaTime ;
}

void Boss::draw(Renderer * renderer, Renderer3D * renderer3D)
{
	if (isAnim)
	{
		if (!isChange)
		{
			b_animCnt += 64.0f;

			if (b_animCnt >= 1022.0f)
			{
				b_animCnt = 0;
			}
			renderer3D->draw3DTexture("deathBurst", Vector3(b_mPosittion.x + 0.0f, b_mPosittion.y + 0.0f, 0.0f), Vector2(b_animCnt, 0.0f), Vector2(64.0f, 64.0f), 140.0f, b_mAngle);
			renderer3D->draw3DTexture("deathBurst", Vector3(b_mPosittion.x + 100.0f, b_mPosittion.y + 100.0f, 0.0f), Vector2(b_animCnt, 0.0f), Vector2(64.0f, 64.0f), 140.0f, b_mAngle);
			renderer3D->draw3DTexture("deathBurst", Vector3(b_mPosittion.x + 100.0f, b_mPosittion.y + 25.0f, 0.0f), Vector2(b_animCnt, 0.0f), Vector2(64.0f, 64.0f), 140.0f, b_mAngle);
			renderer3D->draw3DTexture("deathBurst", Vector3(b_mPosittion.x - 20.0f, b_mPosittion.y - 100.0f, 0.0f), Vector2(b_animCnt, 0.0f), Vector2(64.0f, 64.0f), 140.0f, b_mAngle);
		}
		
	}
	//画像切り替え
	if (isChange)
	{
		renderer3D->draw3DTexture("boss1A", Vector3(b_mPosittion.x, b_mPosittion.y, 0.0f), Vector2(0.0f, 0.0f), Vector2(64.0f, 64.0f), 96.0f * 3.0f, b_mAngle, 255, Vector2(0.5f, 0.5f), Vector3(255, 255, 255));
	}
	else
	{
		//通常
		renderer3D->draw3DTexture("boss1", Vector3(b_mPosittion.x, b_mPosittion.y, 0.0f), Vector2(0.0f, 0.0f), Vector2(64.0f, 64.0f), 96.0f * 3.0f, b_mAngle, 255, Vector2(0.5f, 0.5f), Vector3(255, (float)mDamageHit, (float)mDamageHit));

	}
	//チャージ攻撃
	if (mIsCharge)
	{
		renderer3D->draw3DTexture("bullet_en6", Vector3(b_mPosittion.x, b_mPosittion.y, 0.0f), Vector2(0.0f, 0.0f), Vector2(10.0f, 12.0f), mChargeScalse, 0.0f, 125);
	}
}

void Boss::hit(BaseObject & other)
{
	if (other.getType() == Type::PLAYER_BULLET)
	{
		mDamageHit = 0;
		mTimerDamege->initialize();
		b_mHp -= charaManager->getPlayerBulletDamage();
	}
	//ボムに触れたら
	if (other.getType() == Type::BOM)
	{
		mDamageHit = 0;
		mTimerDamege->initialize();
		b_mHp -= charaManager->getPlayerBulletDamage() / 10.0f;
	}


}
void Boss::attack(float deltaTime)
{
	if (mTimer->timerSet(2)) shot(Vector2(b_mPosittion.x, b_mPosittion.y));
	//円状の攻撃
	if (m_pCirecleTimer->timerSet_Self(6.0f) && ((b_mPosittion.x >= -10.0f && b_mPosittion.x <= 10.0f)))
	{
		mIsCharge = true;
		if (mChargeScalse <= 0)
		{
			mIsCharge = false;
			circleShot(deltaTime);
		}
		mChargeScalse -= 10.0f;

	}
	else
	{
		mChargeScalse = 400.0f;
		mIsCharge = false;
		circleMove(deltaTime);
		shotAngle = 0.0f;
	}
}
void Boss::shot(Vector2 pos)
{
	charaManager->add(new Bullet(Vector2(b_mPosittion.x + 20, b_mPosittion.y), charaManager, b_mType, 30.0f));
	charaManager->add(new Bullet(Vector2(b_mPosittion.x - 20, b_mPosittion.y), charaManager, b_mType, -30.0f));

	charaManager->add(new Bullet(Vector2(b_mPosittion.x + 40, b_mPosittion.y), charaManager, b_mType, 30.0f));
	charaManager->add(new Bullet(Vector2(b_mPosittion.x - 40, b_mPosittion.y), charaManager, b_mType, -30.0f));
	angleVec = Vector2(0, 0);
	angleVec = checkPlayerPos(angleVec);  //角度を代入
	//角度に変換
	bomshotAngle = atan2(angleVec.y, -angleVec.x)* 180.0f / DX_PI_F;
	
}
//円攻撃
void Boss::circleShot(float deltaTime)
{


	m_pCirecleEndTimer->update(deltaTime);
	//円攻撃時間の設定
	if (m_pCirecleEndTimer->timerSet(3.0f))
		m_pCirecleTimer->initialize();

	charaManager->add(new AngleBullet(Vector2(b_mPosittion.x, b_mPosittion.y ), charaManager, b_mType, shotAngle));
	shotAngle += 93.0f;
	charaManager->add(new AngleBullet(Vector2(b_mPosittion.x, b_mPosittion.y ), charaManager, b_mType, shotAngle));
	shotAngle += 93.0f;
}

void Boss::circleMove(float deltaTime)
{
	//円運動
	moveTime += deltaTime * 4.0f;
	x = 2 * radius * cos(moveTime* rotateSpeed);
	y = radius * cos(moveTime* rotateSpeed * 2);
	b_mPosittion += Vector2(x, y);

}
//チャージ
bool Boss::charge()
{
	return mIsCharge;
}

Vector2 Boss::checkPlayerPos(Vector2 vec)
{
	//プレイヤーの位置を入れる
	mPlayerPos = charaManager->getPlayerPosition();
	Vector2 playerVec = mPlayerPos - b_mPosittion;  //プレイヤーとの差分
	return playerVec.normalize();
}