#include "Boss3.h"
#include "../../Device/Camera.h"
#include "../Bulletes/AngleBullet.h"
#include"../Bulletes/TrakingBullet.h"
#include"../Bulletes/BomBallet.h"
#include"Houdai.h"
#include "../../Scene/GamePlay.h"
#include"../Enemies/PlatoonEnemy.h"
#include"../Enemies/CircleMoveEnemy.h"

Boss3::Boss3(Vector2 pos, CharactorManager * c) :m_pCamreraTimer(new Timer()), mTimerDamege(new Timer()), mShotTimer(new Timer()),
mTimerM(new Timer()), mTimerL(new Timer()),
mAnimTimer(new Timer()),
mEndTimer(new Timer())
{
	charaManager = c;
	b_mPosittion = pos;
}

Boss3::~Boss3()
{
	delete m_pCamreraTimer;
	delete mShotTimer;
	delete mTimerM;
	delete mTimerL;
	delete mAnimTimer;
	delete mEndTimer;
}

void Boss3::initialize()
{
	b_mType = Type::BOSS;
	setFlag = false;
	lostCnt = 0;
	modeChangeFlag = false;
	mDamageHit = 255;
	b_mHp = 250;
	b_mCircleSize = 0.0f;
	mShotTimer->initialize();
	mTimerL->initialize();
	mTimerM->initialize();
	shotFlag = true;
	UltFlagL = false;
	UltFlagM = false;
	ShotRing = 200.0f;
	shotTime = 0;
    b_shotT = BossShotType::None;
	mAnimTimer->initialize();
	mEndTimer->initialize();
	isAnim = false;    //画像切り替えを開始する
	isChange = false;
}

void Boss3::update(float deltaTime)
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


	m_pCamreraTimer->update(deltaTime);
	mTimerDamege->update(deltaTime);
	if (mTimerDamege->timerSet_Self(0.2f))
	{
		mDamageHit = 255;
	}
	//無敵時間
	if (DamgeFlag&&mTimer->timerSet(2))DamgeFlag = false;

	if (m_pCamreraTimer->timerSet_Self(3.0f))
	{
		Camera::getInstance().setStop(true);
		if (setFlag == false)
		{
			HoudaiSpow();
			b_mAngle = 0;
		}
		
	}
	else
	{
		b_mVelocity.y = 2;
		b_mAngle += 3.0f;
	}

	
	if (Houdai::lostHoudai == true)
	{
		lostCnt++;
		Houdai::lostHoudai = false;
	}
	/*if (lostCnt >= 2)
	{
		mTimerL->update(deltaTime);
		
		if (ShotRing <= 0&&!UltFlagL)
		{
		  shotLazer(Vector2(b_mPosittion.x, b_mPosittion.y));
		}
		ShotRing -= 10;
	}*/
	if (lostCnt >= 4)
	{
		modeChangeFlag = true;
		modeChange(deltaTime);
	}
}

void Boss3::draw(Renderer * renderer, Renderer3D * renderer3D)
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
		renderer3D->draw3DTexture("boss3A", Vector3(b_mPosittion.x, b_mPosittion.y, 0.0f), Vector2(0.0f, 0.0f), Vector2(64.0f, 64.0f), 96.0f * 3.0f, 0.0f, 255, Vector2(0.5f, 0.5f), Vector3(255, 255, 255));
	}
	else
	{
		//通常
		renderer3D->draw3DTexture("boss3", Vector3(b_mPosittion.x, b_mPosittion.y, 0.0f), Vector2(0.0f, 0.0f), Vector2(64.0f, 64.0f), 96.0f * 8.0f, b_mAngle);
		if (modeChangeFlag == true)
		{
			renderer3D->draw3DTexture("boss3ATK", Vector3(b_mPosittion.x, b_mPosittion.y, 0.0f), Vector2(0.0f, 0.0f), Vector2(64.0f, 64.0f), 96.0f * 3.0f, shotAngle + 90.0f, 255, Vector2(0.5f, 0.5f), Vector3(255, (float)mDamageHit, (float)mDamageHit));
		}
	}

	

	
}

void Boss3::hit(BaseObject & other)
{
	if (modeChangeFlag == true)
	{
		if (other.getType() == Type::PLAYER_BULLET&&b_mType == Type::BOSS)
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
}

void Boss3::HoudaiSpow()
{
	charaManager->add(new Houdai(Vector2(b_mPosittion.x + 200, b_mPosittion.y + 200), charaManager));
	charaManager->add(new Houdai(Vector2(b_mPosittion.x - 200, b_mPosittion.y + 200), charaManager));
	charaManager->add(new Houdai(Vector2(b_mPosittion.x + 200, b_mPosittion.y - 200), charaManager));
	charaManager->add(new Houdai(Vector2(b_mPosittion.x - 200, b_mPosittion.y - 200), charaManager));
	setFlag = true;
}
//砲台がなくなったら
void Boss3::modeChange(float deltaTime)
{
	//当たり判定有効化
	b_mCircleSize = 64.0f;
	Vector2 angleVec = Vector2(0, 0);
	angleVec = checkPlayerPos(angleVec);  //角度を代入
	//角度に変換
	float angle = atan2(-angleVec.y, angleVec.x)* 180.0f / DX_PI_F;
	shotAngle = angle;
	//通常攻撃
	mShotTimer->update(deltaTime);
	if (mShotTimer->timerSet(1.5f)&&shotFlag)
	{
		shot(Vector2(b_mPosittion.x, b_mPosittion.y));
	}
	

	
	////第三形態
	//if (b_mHp < 50)
	//{
	//	modeChange2(deltaTime);
	//}
	//死亡処理
	if (b_mHp <= 0)
	{
		Sound::getInstance().playSE("burst01");
		isAnim = true;
		Score::getInstance().addScore(66666);
		GamePlay::BossEnd = true;
	}
	
	///特殊攻撃
	mTimerM->update(deltaTime);

	switch (shotTime)
	{
	case 60:
		break;
	case 60*2:
		for (int i = 0; i < 10; i++)
		{
			charaManager->add(new TrakingBullet(Vector2(b_mPosittion.x + (GetRand(350) - GetRand(350)), b_mPosittion.y), charaManager, b_mType, 270.0f));
		}
		break;
	case 60 * 4:
		charaManager->add(new AngleBullet(Vector2(b_mPosittion.x, b_mPosittion.y), charaManager, b_mType, angle + 80.0f));
		charaManager->add(new AngleBullet(Vector2(b_mPosittion.x, b_mPosittion.y), charaManager, b_mType, angle));
		charaManager->add(new AngleBullet(Vector2(b_mPosittion.x, b_mPosittion.y), charaManager, b_mType, angle - 80.0f));
		break;
	case 60 * 6:
		for (int i = 0; i < 15; i++)
		{
			charaManager->add(new TrakingBullet(Vector2(b_mPosittion.x + (GetRand(250) - GetRand(250)), b_mPosittion.y), charaManager, b_mType, 270.0f));
		}
		break;
	case 60 * 8:
		charaManager->add(new AngleBullet(Vector2(b_mPosittion.x, b_mPosittion.y), charaManager, b_mType, angle + 20.0f));
		charaManager->add(new AngleBullet(Vector2(b_mPosittion.x, b_mPosittion.y), charaManager, b_mType, angle));
		charaManager->add(new AngleBullet(Vector2(b_mPosittion.x, b_mPosittion.y), charaManager, b_mType, angle - 20.0f));
	case 60 * 13:
		charaManager->add(new PlatoonEnemy(Vector2(b_mPosittion.x + 100.0f, b_mPosittion.y), charaManager, Vector2(300,800) ));
		charaManager->add(new PlatoonEnemy(Vector2(b_mPosittion.x - 100.0f, b_mPosittion.y), charaManager, Vector2(300, 800)));
		break;
	case 60 * 16:
		b_shotT = BossShotType::B;
		break;
	case 60 * 18:
		b_shotT = BossShotType::L;
		break;
	case 60 *20:
		charaManager->add(new CirecleMoveEnemy(Vector2(b_mPosittion.x + 200.0f, b_mPosittion.y), charaManager));
		charaManager->add(new CirecleMoveEnemy(Vector2(b_mPosittion.x - 200.0f, b_mPosittion.y), charaManager));
		break;
	case 60 * 23:
		shotTime = 0;
		break;
	default:
		break;
	}
	switch (b_shotT)
	{
	case L:
		shotL(Vector2(b_mPosittion.x, b_mPosittion.y), shotTime - 60 * 4);
		break;
	case B:
		shotB(Vector2(b_mPosittion.x, b_mPosittion.y), shotTime - 60 * 8);
		break;
	case X:
		shotX(Vector2(b_mPosittion.x, b_mPosittion.y), shotTime - 60 * 13);
	case None:
		break;
	}
	shotTime++;
}

void Boss3::modeChange2(float deltaTime)
{

	
}

void Boss3::shot(Vector2 pos)
{
	Vector2 angleVec = Vector2(0, 0);
	angleVec = checkPlayerPos(angleVec);
	float angle = atan2(-angleVec.y, angleVec.x)* 180.0f / DX_PI_F;
	charaManager->add(new AngleBullet(Vector2(b_mPosittion.x, b_mPosittion.y), charaManager, b_mType, angle - 20.0f));
	charaManager->add(new AngleBullet(Vector2(b_mPosittion.x, b_mPosittion.y), charaManager, b_mType, angle));
	charaManager->add(new AngleBullet(Vector2(b_mPosittion.x, b_mPosittion.y), charaManager, b_mType, angle + 20.0f));
}

void Boss3::shotM(Vector2 pos,int t)
{
	
		for (int i = 0; i < 30; i++)
		{
			charaManager->add(new TrakingBullet(Vector2(b_mPosittion.x + (GetRand(350) - GetRand(350)), b_mPosittion.y), charaManager, b_mType, 270.0f));
		}
	
	shotFlag = true;

	
}

void Boss3::shotL(Vector2 pos,int t)
{
	Vector2 angleVec = Vector2(0, 0);
	angleVec = checkPlayerPos(angleVec);
	float angle = atan2(-angleVec.y, angleVec.x)* 180.0f / DX_PI_F;
	if (t % 20 == 0)
	{
		charaManager->add(new AngleBullet(Vector2(b_mPosittion.x, b_mPosittion.y), charaManager, b_mType, angle + 80.0f));
		charaManager->add(new AngleBullet(Vector2(b_mPosittion.x, b_mPosittion.y), charaManager, b_mType, angle - 40.0f));
		charaManager->add(new AngleBullet(Vector2(b_mPosittion.x, b_mPosittion.y), charaManager, b_mType, angle));
		charaManager->add(new AngleBullet(Vector2(b_mPosittion.x, b_mPosittion.y), charaManager, b_mType, angle + 40.0f));
		charaManager->add(new AngleBullet(Vector2(b_mPosittion.x, b_mPosittion.y), charaManager, b_mType, angle - 80.0f));
	}
	
		shotFlag = true;
	
}

void Boss3::shotB(Vector2 pos, int t)
{
	Vector2 angleVec = Vector2(0, 0);
	angleVec = checkPlayerPos(angleVec);
	float angle = atan2(-angleVec.y, angleVec.x)* 180.0f / DX_PI_F;
	if (t % 120 == 0)
	{
		charaManager->add(new BomBullet(Vector2(b_mPosittion.x, b_mPosittion.y), charaManager, b_mType, angle + 180.0f));
	}
}

void Boss3::shotX(Vector2 pos, int t)
{
	Vector2 angleVec = Vector2(0, 0);
	angleVec = checkPlayerPos(angleVec);
	float angle = atan2(-angleVec.y, angleVec.x)* 180.0f / DX_PI_F;
	if (t % 40 == 0)
	{
		charaManager->add(new AngleBullet(Vector2(b_mPosittion.x, b_mPosittion.y), charaManager, b_mType, angle + 80.0f));
		charaManager->add(new AngleBullet(Vector2(b_mPosittion.x, b_mPosittion.y), charaManager, b_mType, angle - 80.0f));
		charaManager->add(new AngleBullet(Vector2(b_mPosittion.x, b_mPosittion.y), charaManager, b_mType, angle - 220.0f));
		charaManager->add(new AngleBullet(Vector2(b_mPosittion.x, b_mPosittion.y), charaManager, b_mType, angle + 220.0f));
		
	}

}

void Boss3::shotLazer(Vector2 pos)
{
	
	Vector2 angleVec = Vector2(0, 0);
	angleVec = checkPlayerPos(angleVec);
	float angle = atan2(-angleVec.y, angleVec.x)* 180.0f / DX_PI_F;
	charaManager->add(new AngleBullet(Vector2(b_mPosittion.x, b_mPosittion.y), charaManager, b_mType, angle));
	if (mTimerL->timerSet(1))
	{
		UltFlagL = true;
	}
}


Vector2 Boss3::checkPlayerPos(Vector2 vec)
{
	//プレイヤーの位置を入れる
	Vector2 playerPos = charaManager->getPlayerPosition();
	Vector2 playerVec = playerPos - b_mPosittion;  //プレイヤーとの差分
	return playerVec.normalize();
}
