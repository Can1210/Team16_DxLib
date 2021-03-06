#pragma once
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "../Math/Vector3.h"
#include "../Actor/CharaManager/CharactorManager.h"
#include "../Support/Singleton.h"
//カメラクラス
class Camera : public Singleton<Camera>
{
protected:
	Camera();
	virtual ~Camera();

public:
	friend class Singleton<Camera>;  //Singletonでのインスタンス作成は許可
	//初期化
	void initialize();
	//更新
	void update(float deltaTime);

#pragma region  Get/Set
	//位置を返す
	Vector3 getPosition() const;
	//位置を変更する
	void setPosition(Vector2 position);
	//速さを変える
	void setSpeed(float speed);
	float getSpeed()const;

	//止まるフラグ
	bool getStop() const;
	void setStop(bool stop);
	//向いている位置を返す
	Vector3 getLookAtPosition() const;
	//向きの変更
	void setLookAtPosition(Vector3 lookAtPos);
#pragma endregion

private:
	//カメラの移動
	void cameraMove(float deltaTime);

private:

	Vector3 mPosition;        //カメラ位置
	float mSpeed;              //スピード
	Vector3 mLookAtPosition;  //向き
	Vector3 mAngle;           //回転
	Vector3 mVelocity;        //移動量
	float lookAtDistance;
	bool isStop;


};

#endif // !_CAMERA_H_
