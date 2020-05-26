#include <random>
#include"BomEnemy.h"
#include "../Bulletes/AngleBullet.h"
#include "../Item/Item.h"

BomEnemy::BomEnemy(Vector2 pos, CharactorManager *c) :mTimer(new Timer())
{
	charaManager = c;
	b_mPosittion = pos;
}

BomEnemy::~BomEnemy()
{
	delete mTimer;
}
void BomEnemy::initialize()
{
	b_mHp = 3;
	b_mCircleSize = 16.0f;
	b_mType = Type::ENEMY;
	b_mAngle = 180.0f;
	b_mSpeed = 20.0f;
	b_mArpha = 255;
	mTimer->initialize();
}

void BomEnemy::update(float deltaTime)
{
	mTimer->update(deltaTime);
	b_mVelocity = Vector2(0, 0);
	b_mVelocity.y += 1;
	if (mTimer->timerSet(3.0f))
	{
		shot(Vector2(b_mPosittion.x, b_mPosittion.y));
	}
	if (b_mHp <= 0)
	{
		charaManager->add(new Item(b_mPosittion, BulletType::T_Bullet, "enemy3"));   //
		Score::getInstance().addScore(300);
		b_mIsDeath = true;
	}

	b_mPosittion -= b_mVelocity * b_mSpeed * deltaTime;
}

void BomEnemy::draw(Renderer * renderer, Renderer3D* renderer3D)
{
	if (b_mType == Type::ENEMY)
	{
		//renderer->draw2D("enemy3", Vector2(b_mPosittion.x, b_mPosittion.y), Vector2(0, 0), Vector2(64, 64), Vector2(32, 32), Vector2(1.3f, 1.3f), b_mAngle, 255);
		renderer3D->draw3DTexture("enemy3", Vector3(b_mPosittion.x, b_mPosittion.y, 0.0f), Vector2(0.0f, 0.0f), Vector2(64.0f, 64.0f), 96.0f, b_mAngle);
	}
}

void BomEnemy::hit(BaseObject & other)
{
	if (other.getType() == Type::PLAYER_BULLET)
	{
		b_mHp -= 1;	}
}
void BomEnemy::shot(Vector2 pos)
{
	//�ˌ������C���������艺�ɂ����猂���Ȃ�
	if (!isShot()) return;
	Vector2 angleVec = Vector2(0, 0);
	angleVec = checkPlayerPos(angleVec);  //�p�x������
	//�p�x�ɕϊ�
	float angle = atan2(-angleVec.y, angleVec.x)* 180.0f / DX_PI_F;
	//3Way�ɕύX����
	charaManager->add(new AngleBullet(pos + Vector2(32,32), charaManager, b_mType, angle - 20.0f));
	charaManager->add(new AngleBullet(pos + Vector2(32,32), charaManager, b_mType, angle));
	charaManager->add(new AngleBullet(pos + Vector2(32,32), charaManager, b_mType, angle + 20.0f));
}

Vector2 BomEnemy::checkPlayerPos(Vector2 vec)
{
	//�v���C���[�̈ʒu��������
	mPlayerPos = charaManager->getPlayerPosition();
	Vector2 playerVec = mPlayerPos - b_mPosittion;  //�v���C���[�Ƃ̍���
	return playerVec.normalize();
}
//�ˌ����Ăق������ǂ���
bool BomEnemy::isShot()
{
	if (b_mPosittion.y <= charaManager->getPlayerPosition().y - 64 * 2)  return true;
	return false;
}
