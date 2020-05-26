#pragma once
#ifndef _ITEM_H_
#define _ITEM_H_

#include "../CharaManager/BaseObject.h"

//弾の種類
enum BulletType
{
	None,
	T_Bullet,
	T_AngleBullet,
	T_CurveBullet,
	T_LaserBullet,
	T_Shotgun,
	T_TrakingBullet,
	T_WallRefllectionBullet,
};

//アイテム化オブジェクト
class Item : public BaseObject
{
public:
	Item(Vector2 pos, BulletType bulletType,std::string textureName);
	~Item();

	//初期化
	virtual void initialize()override;
	//更新
	virtual void update(float deltaTime)override;
	//描画
	virtual void draw(Renderer* renderer, Renderer3D* renderer3D)override;
	//当たりた時の処理
	virtual void hit(BaseObject& other) override;

	//弾の番号取得
	BulletType getBulletType() const;
	//
	std::string getWeponName() const;

private:
	BulletType mBulletType;
	std::string mTextureName;
};

#endif // !_ITEM_H_
