#include "Shotgun.h"
#include <stdio.h>
#include <time.h>
#include "../Bulletes/ShotgunBullet_sin.h"
#include "../Bulletes/AngleBullet.h"

Shotgun::Shotgun(Vector2 pos, CharactorManager& c, Type t, float angle)
{
	b_mPosittion = pos;
	b_mVelocity = Vector2(0, 0);
	b_SetType = t;
	b_mCircleSize = 4.0f;

	mCenterAngle = angle;
	b_mSpeed = 160.0f;
	//ƒ‰ƒ“ƒ_ƒ€İ’è
	mBulletNum = getRandom(10, 20);	  //ƒ‰ƒ“ƒ_ƒ€‚È’e‚Ì”
	
	m_pCharactorManager = &c;
	mMaxTime = 0.0001f;
}

Shotgun::~Shotgun()
{
}

void Shotgun::deathTime(float deltaTime)
{
	//ŠÔ‚ª‚½‚Á‚½‚ç€‚Ê
	if (mCurrentTime >= mMaxTime)
		b_mIsDeath = true;
	mCurrentTime += deltaTime;

	for (int i = 0; i < mBulletNum; i++)
	{

		mRange = (float)getRandom(-20, 20);       //ƒ‰ƒ“ƒ_ƒ€‚È’e‚Ì”ÍˆÍ
		//’e‚ğ’Ç‰Á‚·‚é
		m_pCharactorManager->add(new ShotgunBullet_sin(b_mPosittion, m_pCharactorManager, b_SetType, 90.0f + mRange));
	}

}

void Shotgun::initialize()
{
}

void Shotgun::update(float deltaTime)
{
	deathTime(deltaTime);
}

void Shotgun::draw(Renderer * renderer, Renderer3D * renderer3D)
{
}

void Shotgun::hit(BaseObject & other)
{
}

//ƒ‰ƒ“ƒ_ƒ€‚È®”‚ğ•Ô‚·
int Shotgun::getRandom(int min, int max)
{
	static int flag;

	if (flag == 0)
	{
		srand((unsigned int)time(NULL));
		flag = 1;
	}

	return min + (int)(rand()*(max - min + 1.0) / (1.0 + RAND_MAX));
}
