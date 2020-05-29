#include "Boss2.h"
#include "../../Scene/GamePlay.h"
#include "../Bulletes/AngleBullet.h"
#include "../Bulletes/Bom.h"
#include "../Bulletes/BomBallet.h"
#include "../Bulletes/Bullet.h"
#include "../Bulletes/TrakingBullet.h"
#include "../../Device/Camera.h"


Boss2::Boss2(Vector2 pos, CharactorManager * c) :
	mTimer(new Timer()),
	m_pCirecleTimer(new Timer()),
	m_pCirecleEndTimer(new Timer()),
	m_pCamreraTimer(new Timer())
{
	charaManager = c;
	b_mPosittion = pos;

}

Boss2::~Boss2()
{
	delete mTimer;
}

void Boss2::initialize()
{
	b_mHp = 100;
	b_mCircleSize = 64.0f;
	b_mType = Type::BOSS;
	b_mAngle = 180.0f;
	b_mSpeed = 20.0f;
	mTimer->initialize();
	m_pCirecleTimer->initialize();
	m_pCirecleEndTimer->initialize();

	shotTime = 0;
}

void Boss2::update(float deltaTime)
{
	mTimer->update(deltaTime);
	m_pCirecleTimer->update(deltaTime);
	m_pCamreraTimer->update(deltaTime);
	if (m_pCamreraTimer->timerSet_Self(3.0f))
	{
		Camera::getInstance().setStop(true);
	}

	b_mVelocity = Vector2(0, 0);
	//–³“GŽžŠÔ
	if (DamgeFlag&&mTimer->timerSet(2))DamgeFlag = false;
	switch (shotTime)
	{
	case 60:
		shot(b_mPosittion);
			break;

	case 60 * 2:
		shotTime = 0;
		break;

	default:
		break;
	}

	if (b_mHp <= 0)
	{
		Sound::getInstance().playSE("burst01");
		b_mIsDeath = true;
		Score::getInstance().addScore(66666);
		GamePlay::BossEnd = true;
	}
	shotTime++;
	b_mPosittion -= b_mVelocity * b_mSpeed * deltaTime;
}

void Boss2::draw(Renderer * renderer, Renderer3D * renderer3D)
{
	if (b_mType == Type::BOSS)
	{
		renderer3D->draw3DTexture("enemy2", Vector3(b_mPosittion.x, b_mPosittion.y, 0.0f), Vector2(0.0f, 0.0f), Vector2(64.0f, 64.0f), 96.0f * 3.0f, b_mAngle);
		renderer3D->draw3DTexture("enemy3", Vector3(b_mPosittion.x, b_mPosittion.y, 0.0f), Vector2(0.0f, 0.0f), Vector2(64.0f, 64.0f), 96.0f * 3.0f, b_mAngle);
	}
	else if (!b_mEndFlag)
	{
		b_mAngle = 0.0f;
		renderer3D->draw3DTexture("enemy2", Vector3(b_mPosittion.x, b_mPosittion.y, 0.0f), Vector2(0.0f, 0.0f), Vector2(64.0f, 64.0f), 96.0f * 3.0f, b_mAngle);
		renderer3D->draw3DTexture("enemy3", Vector3(b_mPosittion.x, b_mPosittion.y, 0.0f), Vector2(0.0f, 0.0f), Vector2(64.0f, 64.0f), 96.0f * 3.0f, b_mAngle);
	}
}

void Boss2::hit(BaseObject & other)
{
	if (other.getType() == Type::PLAYER_BULLET)
	{
		b_mHp -= charaManager->getPlayerBulletDamage();
	}
}

void Boss2::shot(Vector2 pos)
{
	//charaManager->add(new Bullet(Vector2(pos.x + 20, pos.y), charaManager, b_mType, 0.0f));
	charaManager->add(new TrakingBullet(Vector2(pos.x + 5 , pos.y - 100), charaManager, b_mType, 0.0f));
	charaManager->add(new TrakingBullet(Vector2(pos.x + 5 + 20, pos.y - 100), charaManager, b_mType, 0.0f));
	charaManager->add(new TrakingBullet(Vector2(pos.x + 5 + 40, pos.y - 100), charaManager, b_mType, 0.0f));
	charaManager->add(new TrakingBullet(Vector2(pos.x + 5 + 60, pos.y - 100), charaManager, b_mType, 0.0f));

	charaManager->add(new TrakingBullet(Vector2(pos.x + 5 - 20, pos.y - 100), charaManager, b_mType, 0.0f));
	charaManager->add(new TrakingBullet(Vector2(pos.x + 5 - 40, pos.y - 100), charaManager, b_mType, 0.0f));
	charaManager->add(new TrakingBullet(Vector2(pos.x + 5 - 60, pos.y - 100), charaManager, b_mType, 0.0f));
}
