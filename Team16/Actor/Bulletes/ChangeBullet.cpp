#include "ChangeBullet.h"


ChangeBullet::ChangeBullet(Vector2 pos, CharactorManager * c)
{
	b_mPosittion = Vector2(pos);
	b_mVelocity = Vector2(0, 0);
	charaManager = c;
}

ChangeBullet::~ChangeBullet()
{

}

void ChangeBullet::initialize()
{
	b_mCircleSize = 10;
	b_mSpeed = 30;
}

void ChangeBullet::update(float deltaTime)
{
	b_mVelocity.y -= 2;
	b_mPosittion += b_mVelocity*deltaTime*b_mSpeed;

	if (b_mPosittion.y > WindowInfo::WindowHeight
		|| b_mPosittion.y<0
		|| b_mPosittion.x>WindowInfo::WindowWidth
		|| b_mPosittion.x < 0)
	{
		b_mIsDeath = true;
	}
}

void ChangeBullet::draw(Renderer * renderer, Renderer3D* renderer3D)
{
	DrawCircle((int)(b_mPosittion.x + 64 / 2), (int)(b_mPosittion.y + 32), (int)b_mCircleSize, GetColor(0, 0, 255), TRUE);
}

void ChangeBullet::hit(BaseObject & other)
{
	if (other.getType() == Type::ENEMY)
	{
		After();
		b_mIsDeath = true;
	}

}

Type ChangeBullet::getType() const
{
	return CHANGE_BULLET;
}


void ChangeBullet::After()
{
	for (auto object : charaManager->getUseList())
	{

		if (object->getType() == Type::SUB_PLAYER1)
		{
			object->setIsDeath(true);
		}

	}
}





