#include "BaseObject.h"


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
