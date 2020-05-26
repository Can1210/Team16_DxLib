#pragma once
#ifndef _BASEOBJECT_H_
#define _BASEOBJECT_H_
#include "../../Device/Renderer.h"
#include "../../Device/Renderer3D.h"
#include "../../Device/Sound.h"
#include "../../Math/Vector2.h"
#include "../../Utility/Timer.h"
#include "../../GameBase/Score.h"
#include "../../GameBase/WindowInfo.h"

#include "DxLib.h"

//物体のタイプ
enum Type
{
	PLAYER,
	ENEMY,
	PLAYER_BULLET,
	ENEMY_BULLET,
	CHANGE_BULLET,
	BOM,
	BOSS,
	ITEM,
	SPWAN,
};

//描画するオブジェクトの基底クラス
class BaseObject
{


public:
	BaseObject();
	virtual ~BaseObject();

	//初期化
	virtual void initialize() = 0;
	//更新
	virtual void update(float deltaTime) = 0;
	//描画
	virtual void draw(Renderer* renderer, Renderer3D* renderer3D) = 0;
	//当たりた時の処理
	virtual void hit(BaseObject& other) = 0;

#pragma region Get/Set

	//死亡しているか
	virtual bool getIsDeath()const;
	virtual void setIsDeath(bool isDeath);
	//自分の種類
	virtual Type getType()const;
	//自分の位置
	virtual Vector2 getPpstion()const;
	
	//自分の半径
	virtual float getCircleSize()const;

	//自分の位置
	virtual float getBulletDamage()const;
#pragma endregion

	void outArea();

	//円同士の当たり判定
	bool circle_circle_Collision(BaseObject& other);

protected:
	float b_mHp;                //体力
	float b_mSpeed;           //速さ
	float b_mCircleSize;      //円の判定の半径
	Vector2 b_mPosittion;     //位置
	Vector2 b_mVelocity;      //移動方向
	Vector2 b_mSize;          //画像サイズ
	bool b_mIsDeath;          //死んだかどうか
	Type b_mType;             //自分のタイプ
	float b_mAngle;//角度
	int b_mArpha; //画像のアルファ値
	bool b_mEndFlag;//ゲームオーバー
	bool b_mNoDeathArea = false;
	float b_mBulletDamage;//bulletダメージ
	
};


#endif // !_BASEOBJECT_H_
