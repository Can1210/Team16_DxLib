#pragma once
#ifndef _VECTOR3_H_
#define _VECTOR3_H_

#include <DirectXMath.h>

struct Vector3
{
	float x;
	float y;
	float z;

public:
	Vector3();
	Vector3(float X, float Y, float Z);
	//変換
	DirectX::XMVECTOR toXMVector();
	//メンバ関数
	float length()const;                 //ノルムを求める
	Vector3& normalize();                //正規化する
	float dot(const Vector3& v) const;   //内積
	Vector3 cross(const Vector3& v) const; //外積
	Vector3 lerp(const Vector3& end, const float time);

	//単項演算子オーバーロード
	Vector3 operator + ()const;
	Vector3 operator - ()const;
	bool operator == (Vector3 v)const;
	bool operator !=(Vector3 v)const;
	//代入演算子オーバーロード
	Vector3& operator += (const Vector3& v);
	Vector3& operator -= (const Vector3& v);
	Vector3& operator *= (float s);
	Vector3& operator /= (float s);


	//二項演算子オーバーロード
	friend const Vector3 operator + (const Vector3& v1, const Vector3& v2);
	friend const Vector3 operator - (const Vector3& v1, const Vector3& v2);
	friend const Vector3 operator * (const Vector3& v, float s);
	friend const Vector3 operator * (float s, const Vector3& v);
	friend const Vector3 operator / (const Vector3& v, float s);
};

#endif // !_VECTOR3_H_