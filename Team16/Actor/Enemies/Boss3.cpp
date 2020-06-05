#include "Boss3.h"
#include "../../Device/Camera.h"
#include "../Bulletes/AngleBullet.h"


Boss3::Boss3(Vector2 pos, CharactorManager * c)
{
	charaManager = c;
	b_mPosittion = pos;
}

Boss3::~Boss3()
{
}

void Boss3::initialize()
{
}

void Boss3::update(float deltaTime)
{
}

void Boss3::draw(Renderer * renderer, Renderer3D * renderer3D)
{
	renderer3D->draw3DTexture("boss", Vector3(b_mPosittion.x, b_mPosittion.y, 0.0f), Vector2(0.0f, 0.0f), Vector2(64.0f, 64.0f), 96.0f * 7.0f, b_mAngle);
}

void Boss3::hit(BaseObject & other)
{
}

void Boss3::shot(Vector2 pos)
{
}
