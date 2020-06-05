#include <random>
#include"Houdai.h"
#include "../Bulletes/Bullet.h"
#include "../Bulletes/AngleBullet.h"
#include "../Item/Item.h"

Houdai::Houdai(Vector2 pos, CharactorManager *c) :mTimer(new Timer())
{
	charaManager = c;
	b_mPosittion = pos;
}

Houdai::~Houdai()
{
	delete mTimer;
}
void Houdai::initialize()
{
	b_mVelocity = checkPlayerPos(b_mVelocity);
	b_mHp = 30;
	b_mCircleSize = 32.0f;
	b_mType = Type::ENEMY;
	b_mAngle = 180.0f;
	//b_mSpeed = 70.0f;
	b_mArpha = 255;
	mTimer->initialize();
	b_animCnt = 0.0f;
}

void Houdai::update(float deltaTime)
{
	mTimer->update(deltaTime);
	Vector2 angleVec = Vector2(0, 0);
	angleVec = checkPlayerPos(angleVec);  //�p�x����
	//�p�x�ɕϊ�
	float angle = atan2(-angleVec.y, angleVec.x)* 180.0f / DX_PI_F;
	ShotAngle = angle;
	if (mTimer->timerSet(2))
	{
		Shot(Vector2(b_mPosittion.x, b_mPosittion.y));
	}

	//b_mPosittion -= b_mVelocity * b_mSpeed * deltaTime;
}

void Houdai::draw(Renderer * renderer, Renderer3D* renderer3D)
{
	renderer3D->draw3DTexture("houdai", Vector3(b_mPosittion.x, b_mPosittion.y, 0.0f), Vector2(0.0f, 0.0f), Vector2(64.0f, 64.0f), 96.0f*2, ShotAngle+90.0f);
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
			}

			b_mIsDeath = true;
		}
		renderer3D->draw3DTexture("deathBurst", Vector3(b_mPosittion.x, b_mPosittion.y, 0.0f), Vector2(b_animCnt, 0.0f), Vector2(64.0f, 64.0f), 140.0f, b_mAngle);
	}
	//renderer->draw2D("enemy", Vector2(b_mPosittion.x, b_mPosittion.y), Vector2(0, 0), Vector2(64, 64), Vector2(32, 32), Vector2(1.3f, 1.3f), b_mAngle, 255);

}

void Houdai::hit(BaseObject & other)
{
	if (other.getType() == Type::PLAYER_BULLET&&b_mType == Type::ENEMY)
	{
		b_mHp -= charaManager->getPlayerBulletDamage();
	}
}

void Houdai::Shot(Vector2 pos)
{
	
	charaManager->add(new AngleBullet(Vector2(b_mPosittion.x, b_mPosittion.y) + Vector2(32, 32), charaManager, b_mType, ShotAngle));
}



Vector2 Houdai::checkPlayerPos(Vector2 vec)
{
	//�v���C���[�̈ʒu������
	Vector2 playerPos = charaManager->getPlayerPosition();
	Vector2 playerVec = playerPos - b_mPosittion;  //�v���C���[�Ƃ̍���
	return playerVec.normalize();
}