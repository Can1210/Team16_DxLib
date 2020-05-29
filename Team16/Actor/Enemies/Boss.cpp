#include "Boss.h"
#include "../../Scene/GamePlay.h"
#include "../Bulletes/AngleBullet.h"
#include "../Bulletes/Bom.h"
#include "../Bulletes/BomBallet.h"
#include "../Bulletes/Bullet.h"
#include "../../Device/Camera.h"


Boss::Boss(Vector2 pos, CharactorManager * c) :
	mTimer(new Timer()),
	m_pCirecleTimer(new Timer()),
	m_pCirecleEndTimer(new Timer()),
	m_pCamreraTimer(new Timer())
{
	charaManager = c;
	b_mPosittion = pos;

}

Boss::~Boss()
{
	delete mTimer;
	delete m_pCirecleTimer;
	delete m_pCirecleEndTimer;
}

void Boss::initialize()
{
	b_mHp = 30;
	b_mCircleSize = 64.0f;
	b_mType = Type::BOSS;
	b_mAngle = 180.0f;
	b_mSpeed = 20.0f;
	mTimer->initialize();
    m_pCirecleTimer->initialize();
    m_pCirecleEndTimer->initialize();
	bomshotAngle = 180.0f;
}

void Boss::update(float deltaTime)
{
	mTimer->update(deltaTime);
	m_pCirecleTimer->update(deltaTime);
	m_pCamreraTimer->update(deltaTime);
	if (m_pCamreraTimer->timerSet_Self(3.0f))
	{
		Camera::getInstance().setStop(true);
	}

	b_mVelocity = Vector2(0, 0);
	//無敵時間
	if (DamgeFlag&&mTimer->timerSet(2))DamgeFlag = false;

	b_mVelocity.y += 2;
	if (b_mPosittion.y > 150) b_mVelocity = Vector2(0, 0);
	attack(deltaTime);
	if (b_mHp <= 0)
	{
		Sound::getInstance().playSE("burst01");
		b_mIsDeath = true;
		Score::getInstance().addScore(66666);
		GamePlay::BossEnd = true;
	}
	b_mPosittion -= b_mVelocity * b_mSpeed * deltaTime ;
}

void Boss::draw(Renderer * renderer, Renderer3D * renderer3D)
{
	if (b_mType == Type::BOSS)
	{
		//renderer->draw2D("enemy2", Vector2(b_mPosittion.x, b_mPosittion.y), Vector2(0, 0), Vector2(64, 64), Vector2(32, 32), Vector2(3.0f, 3.0f), b_mAngle, 255);
		//renderer->draw2D("enemy3", Vector2(b_mPosittion.x, b_mPosittion.y), Vector2(0, 0), Vector2(64, 64), Vector2(32, 32), Vector2(3.0f, 3.0f), b_mAngle, 255);
		renderer3D->draw3DTexture("enemy2", Vector3(b_mPosittion.x, b_mPosittion.y, 0.0f), Vector2(0.0f, 0.0f), Vector2(64.0f, 64.0f), 96.0f * 3.0f, b_mAngle);
		renderer3D->draw3DTexture("enemy3", Vector3(b_mPosittion.x, b_mPosittion.y, 0.0f), Vector2(0.0f, 0.0f), Vector2(64.0f, 64.0f), 96.0f * 3.0f, b_mAngle);
	}
	else if (!b_mEndFlag)
	{
		b_mAngle = 0.0f;
		//renderer->draw2D("enemy2", Vector2(b_mPosittion.x, b_mPosittion.y), Vector2(0, 0), Vector2(64, 64), Vector2(32, 32), Vector2(3.0f, 3.0f), b_mAngle, 255);
		//renderer->draw2D("enemy3", Vector2(b_mPosittion.x, b_mPosittion.y), Vector2(0, 0), Vector2(64, 64), Vector2(32, 32), Vector2(3.0f, 3.0f), b_mAngle, 255);
		renderer3D->draw3DTexture("enemy2", Vector3(b_mPosittion.x, b_mPosittion.y, 0.0f), Vector2(0.0f, 0.0f), Vector2(64.0f, 64.0f), 96.0f * 3.0f, b_mAngle);
		renderer3D->draw3DTexture("enemy3", Vector3(b_mPosittion.x, b_mPosittion.y, 0.0f), Vector2(0.0f, 0.0f), Vector2(64.0f, 64.0f), 96.0f * 3.0f, b_mAngle);
	}
}

void Boss::hit(BaseObject & other)
{
	if (other.getType() == Type::PLAYER_BULLET)
	{
		b_mHp -= charaManager->getPlayerBulletDamage();
	}
}
void Boss::attack(float deltaTime)
{
	if (mTimer->timerSet(2)) shot(Vector2(b_mPosittion.x, b_mPosittion.y));
	//円状の攻撃
	if (m_pCirecleTimer->timerSet_Self(10.0f))
		circleShot(deltaTime);
	else
		shotAngle = 0.0f;
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
	bomshotAngle = atan2(-angleVec.y, angleVec.x)* 180.0f / DX_PI_F;
	charaManager->add(new BomBullet(pos, charaManager, b_mType, bomshotAngle));
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

Vector2 Boss::checkPlayerPos(Vector2 vec)
{
	//プレイヤーの位置を入れる
	mPlayerPos = charaManager->getPlayerPosition();
	Vector2 playerVec = mPlayerPos - b_mPosittion;  //プレイヤーとの差分
	return playerVec.normalize();
}