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
	b_mCircleSize += 10;
	if (mTimer->timerSet(0.5f))
	{
		b_mIsDeath = true;
	}
}

void Bom::draw(Renderer * renderer, Renderer3D* renderer3D)
{
	//DrawCircle((int)(b_mPosittion.x + 64 / 2), (int)(b_mPosittion.y + 32), (int)b_mCircleSize, GetColor(255, 150, 0), TRUE);
	renderer3D->draw3DTexture("bullet_en6", Vector3(b_mPosittion.x, b_mPosittion.y, 0.0f), Vector2(0.0f, 0.0f), Vector2(10.0f, 12.0f), b_mCircleSize, 0.0f);
}

void Bom::hit(BaseObject & other)
{
}

Type Bom::getType() const
{
	return BOM;
}
