#pragma once
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "DxLib.h"
#include "../Math/Vector3.h"
#include "../Actor/CharaManager/CharactorManager.h"
#include "../Device/Input.h"

//カメラクラス
class Camera
{
public:
	Camera(CharactorManager& chractorManager);
	~Camera();
	//初期化
	void initialize();
	//更新
	void update();

	//カメラの更新
	void cameraUpdate();

#pragma region  Get/Set
	//位置を返す
	Vector3 getPosition();
	//位置を変更する
	void setPosition(Vector3 position);
	//向いている位置を返す
	Vector3 getLookAtPosition();
	//向きの変更
	void setLookAtPosition(Vector3 lookAtPos);

private:
	//プレイヤーを探す
	void searchPlayer();

#pragma endregion

private:

	Vector3 mPosition;        //カメラ位置
	Vector3 mLookAtPosition;  //向き
	Vector3 mAngle;           //回転
	Vector3 mVelocity;        //移動量

	CharactorManager* m_pCharactorManager;   //プレイヤーを探す用
	const float lookAtDistance;   //とりあえず700
	Input* input;
};

#endif // !_CAMERA_H_
