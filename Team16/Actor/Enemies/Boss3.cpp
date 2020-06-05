#include "Boss3.h"
#include "../../Device/Camera.h"
#include "../Bulletes/AngleBullet.h"
#include"Houdai.h"


Boss3::Boss3(Vector2 pos, CharactorManager * c):m_pCamreraTimer(new Timer())
{
	charaManager = c;
	b_mPosittion = pos;
}

Boss3::~Boss3()
{
	delete m_pCamreraTimer;
}

void Boss3::initialize()
{
	b_mType = Type::BOSS;
	setFlag = false;
	
}

void Boss3::update(float deltaTime)
{
	m_pCamreraTimer->update(deltaTime);
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

	
}

void Boss3::draw(Renderer * renderer, Renderer3D * renderer3D)
{
	renderer3D->draw3DTexture("boss", Vector3(b_mPosittion.x, b_mPosittion.y, 0.0f), Vector2(0.0f, 0.0f), Vector2(64.0f, 64.0f), 96.0f * 7.0f, b_mAngle);
}

void Boss3::hit(BaseObject & other)
{
}

void Boss3::HoudaiSpow()
{
	charaManager->add(new Houdai(Vector2(b_mPosittion.x + 200, b_mPosittion.y + 200), charaManager));
	charaManager->add(new Houdai(Vector2(b_mPosittion.x - 200, b_mPosittion.y + 200), charaManager));
	charaManager->add(new Houdai(Vector2(b_mPosittion.x + 200, b_mPosittion.y - 200), charaManager));
	charaManager->add(new Houdai(Vector2(b_mPosittion.x - 200, b_mPosittion.y - 200), charaManager));
	setFlag = true;
}

void Boss3::shot(Vector2 pos)
{
}
