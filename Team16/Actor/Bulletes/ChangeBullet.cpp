#include "ChangeBullet.h"

ChangeBullet::ChangeBullet(Vector2 pos, CharactorManager * c)
{
	b_mPosittion = Vector2(pos);
	b_mVelocity = Vector2(0, 0);
}

ChangeBullet::~ChangeBullet()
{

}

void ChangeBullet::initialize()
{
	b_mCircleSize = 16;
}

void ChangeBullet::update(float deltaTime)
{
	b_mVelocity.y -= 2;
	b_mPosittion += b_mVelocity;

	if (b_mPosittion.y > WindowInfo::WindowHeight
		|| b_mPosittion.y<0
		|| b_mPosittion.x>WindowInfo::WindowWidth
		|| b_mPosittion.x < 0)
	{
		b_mIsDeath = true;
	}
}

void ChangeBullet::draw(Renderer * renderer)
{
	//rend->draw2D("bullet", Vector2(b_mPosittion.x, b_mPosittion.y), Vector2(0, 0), Vector2(64, 64));
	DrawCircle(b_mPosittion.x + 64 / 2, b_mPosittion.y + 32, b_mCircleSize, GetColor(0, 0, 255), TRUE);
}

void ChangeBullet::hit(BaseObject & other)
{
	if (other.getType() == Type::ENEMY)
	{
		b_mIsDeath = true;
	}

}

bool ChangeBullet::getIsDeath() const
{
	return b_mIsDeath;
}

Type ChangeBullet::getType() const
{
	return CHANGE_BULLET;
}

Vector2 ChangeBullet::getPpstion() const
{
	return b_mPosittion;
}

float ChangeBullet::getCircleSize() const
{
	return b_mCircleSize;
}

Type ChangeBullet::ChangeType()
{
	return Type();
}

