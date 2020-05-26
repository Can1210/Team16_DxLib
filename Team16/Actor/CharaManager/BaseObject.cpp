#include "BaseObject.h"
#include "../CharaManager/DeathPoint.h"

//コンストラクタ
BaseObject::BaseObject()
{
}

//デスストラクタ
BaseObject::~BaseObject()
{
}
//円同士の当たり判定
bool BaseObject::circle_circle_Collision(BaseObject& other)
{
	//自分と相手の距離を計算
	float length = Vector2((b_mPosittion - other.b_mPosittion)).length();
	float radiusSum = b_mCircleSize + other.b_mCircleSize;     //二つの半径を足す
	//距離より二つの半径が大きければ当たっている
	if (length <= radiusSum)
	{
		return true;
	}
	return false;
}

bool BaseObject::getIsDeath() const
{
	return b_mIsDeath;
}

void BaseObject::setIsDeath(bool isDeath)
{
	b_mIsDeath = isDeath;
}

Type BaseObject::getType() const
{
	return b_mType;
}

Vector2 BaseObject::getPpstion() const
{
	return b_mPosittion;
}

float BaseObject::getCircleSize() const
{
	return b_mCircleSize;
}
float BaseObject::getBulletDamage() const
{
	return b_mBulletDamage;
}
//死亡エリア
void BaseObject::outArea()
{
	if (b_mNoDeathArea) return;

	//Y
	if (b_mPosittion.y >= DeathPoint::getInstance().getUp()
		|| b_mPosittion.y <= DeathPoint::getInstance().getDown())
		b_mIsDeath = true;
	//X
	if (b_mPosittion.x >= DeathPoint::getInstance().getRight()
		|| b_mPosittion.x <= DeathPoint::getInstance().getLeft())
		b_mIsDeath = true;
}

