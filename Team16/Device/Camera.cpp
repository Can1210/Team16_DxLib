#include "Camera.h"
#include "../Actor/CharaManager/DeathPoint.h"

// ラインを描く範囲
#define LINE_AREA_SIZE			10000.0f

// ラインの数
#define LINE_NUM			5

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
	mSpeed = 20.0f;
}
//更新
void Camera::update(float deltaTime)
{
	cameraMove(deltaTime);
	cameraUpdate();
}
void Camera::cameraUpdate()
{
	// 位置関係が分かるように地面にラインを描画する
	{
		int i;
		VECTOR Pos1;
		VECTOR Pos2;

		SetUseZBufferFlag(TRUE);

		Pos1 = VGet(-LINE_AREA_SIZE / 2.0f, 0.0f, -LINE_AREA_SIZE / 2.0f);
		Pos2 = VGet(-LINE_AREA_SIZE / 2.0f, 0.0f, LINE_AREA_SIZE / 2.0f);
		for (i = 0; i <= LINE_NUM; i++)
		{
			DrawLine3D(Pos1, Pos2, GetColor(255, 255, 255));
			Pos1.x += LINE_AREA_SIZE / LINE_NUM;
			Pos2.x += LINE_AREA_SIZE / LINE_NUM;
		}

		Pos1 = VGet(-LINE_AREA_SIZE / 2.0f, 0.0f, -LINE_AREA_SIZE / 2.0f);
		Pos2 = VGet(LINE_AREA_SIZE / 2.0f, 0.0f, -LINE_AREA_SIZE / 2.0f);
		for (i = 0; i < LINE_NUM; i++)
		{
			DrawLine3D(Pos1, Pos2, GetColor(255, 255, 255));
			Pos1.z += LINE_AREA_SIZE / LINE_NUM;
			Pos2.z += LINE_AREA_SIZE / LINE_NUM;
		}

		SetUseZBufferFlag(FALSE);
	}

}


void Camera::cameraMove(float deltaTime)
{
	mVelocity.y = 1.0f;
	mPosition.y += mVelocity.y * mSpeed * deltaTime;
	mLookAtPosition.y = mPosition.y;   //Y軸しか動かない
	// カメラの設定に反映する
	SetCameraPositionAndTarget_UpVecY(VGet(mPosition.x, mPosition.y, mPosition.z), VGet(mLookAtPosition.x, mLookAtPosition.y, mLookAtPosition.z));

	DeathPoint::getInstance().setUp(mPosition.y + 800.0f);
	DeathPoint::getInstance().setDown(mPosition.y - 500.0f);
	DeathPoint::getInstance().setLeft(mPosition.x - 500.0f);
	DeathPoint::getInstance().setRight(mPosition.x + 500.0f);
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