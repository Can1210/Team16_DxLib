#pragma once
#include"../CharaManager/CharactorManager.h"
#include"../CharaManager/BaseObject.h"

class WallReflectionBullet : public BaseObject
{
public:
	WallReflectionBullet(Vector2 pos, CharactorManager* c, Type t, int angle);
	WallReflectionBullet(Vector2 pos, CharactorManager* c, Type t, int angle,bool hitSound);
	~WallReflectionBullet();
	//弾のタイプ分け
	void setBulletType();
	//初期化
	virtual void initialize()override;
	//更新
	virtual void update(float deltaTime)override;
	//描画
	virtual void draw(Renderer* renderer, Renderer3D* renderer3D)override;
	//当たりた時の処理
	virtual void hit(BaseObject& other) override;

private:
	enum WallType {
		R,
		L,
		None,
	};

	Vector2 RotationZ(float ang);//z軸回転の成分だけ

private:
	CharactorManager* charaManager;
	Type b_SetType;
	int angle;
	float PI = 3.141592653589793f;//円周率
	float bulletAngle;			  //bulletの角度
	bool hits;

	WallType type;
};