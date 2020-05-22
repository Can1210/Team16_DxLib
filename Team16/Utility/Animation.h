#pragma once
#ifndef _ANIMATION_H_
#define _ANIMATION_H_


#include "../Math/Vector2.h"
#include "Timer.h"

//アニメーションクラス
class Animation
{
public:
	Animation(Vector2 drawSize, Vector2 textureSize,float changeTime);
	~Animation();

	//初期化
	void initialize();

	//更新
	void update(float deltaTime);
	//アニメーション切り替え
	void changeAnimation(float deltaTime);

#pragma region Get
	//左上座標の取得
	Vector2 getLeftSize() const;
	//右上座標の追加
	Vector2 getDrawSize() const;

#pragma endregion

private:

	Vector2 mLeftSize;      //左上座標
	Vector2 mDrawSize;      //サイズ
	Vector2 mTextureSize;   //画像元サイズ
	float mChangeTime;      //切り替え時間

	Timer* m_pTimer;        //タイマークラス



};

#endif // !_ANIMATION_H_