#include "Bom.h"

Bom::Bom(Vector2 pos, CharactorManager * c) :mTimer(new Timer())
{
	b_mPosittion = Vector2(pos);
}

Bom::~Bom()
{
	delete mTimer;
}

void Bom::initialize()
{
	b_mCircleSize = 0;
	mTimer->initialize();
}

void Bom::update(float deltaTime)
{
	mTimer->update(deltaTime);
	b_mCircleSize += 20;
	if (mTimer->timerSet(0.5f))
	{
		b_mIsDeath = true;
	}

}

void Bom::draw(Renderer * renderer, Renderer3D* renderer3D)
{
	DrawCircle(b_mPosittion.x + 64 / 2, b_mPosittion.y + 32, b_mCircleSize, GetColor(255, 150, 0), TRUE);
}

void Bom::hit(BaseObject & other)
{

}

bool Bom::getIsDeath() const
{
	return b_mIsDeath;
}

Type Bom::getType() const
{
	return PLAYER_BULLET;
}

Vector2 Bom::getPpstion() const
{
	return b_mPosittion;
}

float Bom::getCircleSize() const
{
	return b_mCircleSize;
}

void Bom::setIsDeath(bool isDeath)
{
	b_mIsDeath = isDeath;
}
