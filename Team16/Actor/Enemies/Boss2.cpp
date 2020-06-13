#include "Boss2.h"
#include "../../Scene/GamePlay.h"
#include "../Bulletes/AngleBullet.h"
#include "../Bulletes/Bom.h"
#include "../Bulletes/BomBallet.h"
#include "../Bulletes/Bullet.h"
#include "../Bulletes/TrakingBullet.h"
#include "../Bulletes/WallReflectionBullet.h"
#include "../../Device/Camera.h"


Boss2::Boss2(Vector2 pos, CharactorManager * c) :
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

Boss2::~Boss2()
{
	delete mTimer;
	delete mTimerDamege;
	delete mAnimTimer;
	delete mEndTimer;
}

void Boss2::initialize()
{
	b_mHp = 200;
	b_mCircleSize = 64.0f;
	b_mType = Type::BOSS;
	b_mAngle = 0.0f;
	b_mSpeed = 20.0f;
	mTimer->initialize();
	mTimerDamege->initialize();
	mDamageHit = 255;
	m_pCirecleTimer->initialize();
	m_pCirecleEndTimer->initialize();
	boss2move = Boss2Move::NoneMove;
	shotTime = 0;
	mAnimTimer->initialize();
	mEndTimer->initialize();
	isAnim = false;    //‰æ‘œØ‚è‘Ö‚¦‚ðŠJŽn‚·‚é
	isChange = false;
}

void Boss2::update(float deltaTime)
{

	if (isChange)
	{
		mEndTimer->update(deltaTime);
		if (mEndTimer->timerSet(3.0f))
		{
			b_mIsDeath = true;  //Ž€–S
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
	if (m_pCamreraTimer->timerSet_Self(2.0f))
	{
		Camera::getInstance().setStop(true);
	}
	else
		b_mVelocity.y = 2;
	//–³“GŽžŠÔ
	if (DamgeFlag&&mTimer->timerSet(2))DamgeFlag = false;
	switch (shotTime)
	{
	case 60:
		break;

	case 60 * 2:

		boss2move = Boss2Move::Move_1;
		break;

	case 60 * 4:
		boss2move = Boss2Move::Move_2;
		break;

	case 60 * 5:
		charaManager->add(new Enemy(Vector2(b_mPosittion.x + 50.0f, b_mPosittion.y), charaManager));
		break;
	case 60 * 5 + 30:
		charaManager->add(new Enemy(Vector2(b_mPosittion.x - 50.0f, b_mPosittion.y), charaManager));
		break;
	case 60 * 6:
		charaManager->add(new Enemy(Vector2(b_mPosittion.x + 50.0f, b_mPosittion.y), charaManager));
		break;
	case 60 * 6 + 30:
		charaManager->add(new Enemy(Vector2(b_mPosittion.x - 50.0f, b_mPosittion.y), charaManager));
		break;
	case 60 * 7:
		charaManager->add(new Enemy(Vector2(b_mPosittion.x + 50.0f, b_mPosittion.y), charaManager));
		break;
	case 60 * 7 + 30:
		charaManager->add(new Enemy(Vector2(b_mPosittion.x - 50.0f, b_mPosittion.y), charaManager));
		break;

	case 60 * 9:
		boss2move = Boss2Move::Move_3;
		break;

	case 60 * 13:
		boss2move = Boss2Move::Move_1;
		for (int i = 0; i < 20; i++)
		{
			charaManager->add(new TrakingBullet(Vector2(b_mPosittion.x + (GetRand(150) - GetRand(150)), b_mPosittion.y), charaManager, b_mType, 270.0f));
		}
		shotTime = 0;
		break;

	default:
		break;
	}
	Vector2 v = b_mPosittion - charaManager->getPlayerPosition();
	switch (boss2move)
	{
	case Boss2Move::Move_1:
		shot2(b_mPosittion, shotTime - 60 * 2);
		v = v.normalize();
		b_mVelocity.x = v.x * 10.0f;
		break;
	case Boss2Move::Move_2:
		if (mTimer->timerSet(0.2f))
		{
			charaManager->add(new AngleBullet(Vector2(b_mPosittion.x + 100, b_mPosittion.y), charaManager, b_mType, 90.0f));
			charaManager->add(new AngleBullet(Vector2(b_mPosittion.x - 100, b_mPosittion.y), charaManager, b_mType, 90.0f));
		}
		shot(b_mPosittion, shotTime - 60 * 4);
		if (b_mHp < 200)
		{
			v = v.normalize();
			b_mVelocity.x = v.x * 10.0f;
		}
		break;
	case Boss2Move::Move_3:
		if (mTimer->timerSet(0.3f))
		{
			charaManager->add(new WallReflectionBullet(Vector2(b_mPosittion.x, b_mPosittion.y) + Vector2(32.0f, 32.0f), charaManager, b_mType, 270 - 60));
			charaManager->add(new WallReflectionBullet(Vector2(b_mPosittion.x, b_mPosittion.y) + Vector2(32.0f, 32.0f), charaManager, b_mType, 270 + 60));
		}
		b_mVelocity.x = cos(rotx * 1.0f) * 10.0f;
		break;
	case Boss2Move::NoneMove:
		break;
	}

	if (b_mHp <= 0)
	{
		Sound::getInstance().playSE("burst01");
		isAnim = true;
		Score::getInstance().addScore(66666);
		GamePlay::BossEnd = true;
	}

	shotTime++;
	rotx += deltaTime * 1.5f;
	//¡‚¾‚¯
	b_mPosittion -= b_mVelocity * b_mSpeed * deltaTime;
}

void Boss2::draw(Renderer * renderer, Renderer3D * renderer3D)
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
	//‰æ‘œØ‚è‘Ö‚¦
	if (isChange)
	{
		renderer3D->draw3DTexture("boss2A", Vector3(b_mPosittion.x, b_mPosittion.y, 0.0f), Vector2(0.0f, 0.0f), Vector2(64.0f, 64.0f), 96.0f * 3.0f, b_mAngle, 255, Vector2(0.5f, 0.5f), Vector3(255, 255, 255));
	}
	else
	{
		//’Êí
		renderer3D->draw3DTexture("boss2", Vector3(b_mPosittion.x, b_mPosittion.y, 0.0f), Vector2(0.0f, 0.0f), Vector2(64.0f, 64.0f), 96.0f * 3.0f, b_mAngle, 255, Vector2(0.5f, 0.5f), Vector3(255, (float)mDamageHit, (float)mDamageHit));

	}

}

void Boss2::hit(BaseObject & other)
{
	if (other.getType() == Type::PLAYER_BULLET)
	{
		mDamageHit = 0;
		mTimerDamege->initialize();
		b_mHp -= charaManager->getPlayerBulletDamage();
	}
	//ƒ{ƒ€‚ÉG‚ê‚½‚ç
	if (other.getType() == Type::BOM)
	{
		mDamageHit = 0;
		mTimerDamege->initialize();
		b_mHp -= charaManager->getPlayerBulletDamage() / 10.0f;
	}
}

void Boss2::shot(Vector2 pos, int t)
{
	if (t % 40 == 0)
	{
		charaManager->add(new BomBullet(Vector2(b_mPosittion.x + 5 + 90, b_mPosittion.y), charaManager, b_mType, 270.0f - 30.0f));
		charaManager->add(new BomBullet(Vector2(b_mPosittion.x + 5 - 90, b_mPosittion.y), charaManager, b_mType, 270.0f + 30.0f));
	}

	if (t % 60 == 0)
	{
		charaManager->add(new WallReflectionBullet(Vector2(b_mPosittion.x - 33, b_mPosittion.y) + Vector2(32.0f, 32.0f), charaManager, b_mType, 270 - 40));
		charaManager->add(new WallReflectionBullet(Vector2(b_mPosittion.x - 33, b_mPosittion.y) + Vector2(32.0f, 32.0f), charaManager, b_mType, 270 + 40));
		charaManager->add(new WallReflectionBullet(Vector2(b_mPosittion.x - 33, b_mPosittion.y) + Vector2(32.0f, 32.0f), charaManager, b_mType, 90 - 40));
		charaManager->add(new WallReflectionBullet(Vector2(b_mPosittion.x - 33, b_mPosittion.y) + Vector2(32.0f, 32.0f), charaManager, b_mType, 90 + 40));
	}
}

void Boss2::shot2(Vector2 p, int t)
{
	if (t > 60)
		t = t - 60;

	if (t <= 30)
		t = 30 - t;
	else if (t > 30)
		t = t - 30;

	int shotA;

	if (t % 3 == 0 && t <= 30)
	{
		shotA = t / 3;
		charaManager->add(new AngleBullet(Vector2(b_mPosittion.x + 100, b_mPosittion.y), charaManager, b_mType, 90.0f - (3 * shotA)));
		charaManager->add(new AngleBullet(Vector2(b_mPosittion.x - 100, b_mPosittion.y), charaManager, b_mType, 90.0f + (3 * shotA)));
	}
	else if (t % 3 && t > 30)
	{
		shotA = t / 3;
		charaManager->add(new AngleBullet(Vector2(b_mPosittion.x + 100, b_mPosittion.y), charaManager, b_mType, 90.0f - (3 * shotA)));
		charaManager->add(new AngleBullet(Vector2(b_mPosittion.x - 100, b_mPosittion.y), charaManager, b_mType, 90.0f + (3 * shotA)));
	}
}

bool Boss2::playerInArea()
{
	float x = (b_mPosittion.x + 5) - charaManager->getPlayerPosition().x;
	x = abs(x);
	if (x > 200.0f)
	{
		return true;
	}
	return false;
}
