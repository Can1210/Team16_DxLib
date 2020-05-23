#include "Camera.h"


// ラインを描く範囲
#define LINE_AREA_SIZE			10000.0f

// ラインの数
#define LINE_NUM			5


//コンストラクタ
Camera::Camera(CharactorManager& chractorManager,Vector2 pos) :
	mPosition(pos.x, pos.y, lookAtDistance),
	mLookAtPosition(0, 0, 0),
	m_pCharactorManager(&chractorManager),
	lookAtDistance(1000),
	mSpeed(20.0f)
{
}

//デスストクタ
Camera::~Camera()
{
	delete input;
}
//初期化
void Camera::initialize()
{
	mPosition = Vector3(0,0,lookAtDistance);
	mLookAtPosition = Vector3(0, 0, 0);
	input = new Input();
	input->init();
}
//更新
void Camera::update(float deltaTime)
{
	input->update();
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
}


//位置を返す
Vector3 Camera::getPosition() const
{
	return mPosition;
}
//位置を変更する
void Camera::setPosition(Vector3 position)
{
	mPosition = position;
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
