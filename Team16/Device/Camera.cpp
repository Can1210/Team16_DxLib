#include "Camera.h"
#include "../Actor/CharaManager/DeathPoint.h"
#include "../Support/CWindow.h"

//コンストラクタ
Camera::Camera()
{
}

//デスストクタ
Camera::~Camera()
{
}
//初期化
void Camera::initialize()
{
	lookAtDistance = 1000.0f;
	mPosition = Vector3(0.0f,0.0f,lookAtDistance);
	mLookAtPosition = Vector3(0.0f, 0.0f, 0.0f);
	mSpeed = 100.0f;
}
//更新
void Camera::update(float deltaTime)
{
	cameraMove(deltaTime);
}

void Camera::cameraMove(float deltaTime)
{



	mVelocity.y = 1.0f;
	mPosition.y += mVelocity.y * mSpeed * deltaTime;

	if (mPosition.y >= 6050.0f)
	{
		mPosition.y = 6050.0f;
	}



	mLookAtPosition.y = mPosition.y;   //Y軸しか動かない
	// カメラの設定に反映する
	SetCameraPositionAndTarget_UpVecY(VGet(mPosition.x, mPosition.y, mPosition.z), VGet(mLookAtPosition.x, mLookAtPosition.y, mLookAtPosition.z));

	DeathPoint::getInstance().setUp(mPosition.y + 800.0f);
	DeathPoint::getInstance().setDown(mPosition.y - 500.0f);
	DeathPoint::getInstance().setLeft(mPosition.x - 500.0f);
	DeathPoint::getInstance().setRight(mPosition.x + 500.0f);
	DeathPoint::getInstance().setCenter(mPosition.y);
	DeathPoint::getInstance().cameraVely(mVelocity.y * mSpeed);

	

	//CWindow::getInstance().log("ｙ座標 %f\n", mPosition.y);
}

#pragma region Get/Set

//位置を返す
Vector3 Camera::getPosition() const
{
	return mPosition;
}
//位置を変更する
void Camera::setPosition(Vector2 position)
{
	mPosition = Vector3(position.x, position.y, lookAtDistance);
	DeathPoint::getInstance().setUp(mPosition.y + 800.0f);        //上
	DeathPoint::getInstance().setDown(mPosition.y - 500.0f);	  //下
	DeathPoint::getInstance().setLeft(mPosition.x - 500.0f);	  //右
	DeathPoint::getInstance().setRight(mPosition.x + 500.0f);	  //左
	DeathPoint::getInstance().setCenter(mPosition.y);
	DeathPoint::getInstance().cameraVely(mVelocity.y * mSpeed);
}
//速度を変える
void Camera::setSpeed(float speed)
{
	mSpeed = speed;
}
//向いている位置を返す
Vector3 Camera::getLookAtPosition() const
{
	return mLookAtPosition;
}
//向いている位置を変更する
void Camera::setLookAtPosition(Vector3 lookAtPos)
{
	mLookAtPosition = lookAtPos;
}

#pragma endregion