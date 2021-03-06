#pragma once
#include"../CharaManager/CharactorManager.h"
#include"../CharaManager/BaseObject.h"

class AngleBullet : public BaseObject
{
public:
	AngleBullet(Vector2 pos, CharactorManager* c, Type t, float angle);
	~AngleBullet();
	//初期化
	virtual void initialize()override;
	//更新
	virtual void update(float deltaTime)override;
	//描画
	virtual void draw(Renderer* renderer, Renderer3D* renderer3D)override;
	//当たりた時の処理
	virtual void hit(BaseObject& other) override;

private:
	//弾のタイプ分け
	void setBulletType();
	Vector2 RotationZ(float ang);//z軸回転の成分だけ

private:
	CharactorManager* charaManager;
	Type b_SetType;
	float PI = 3.141592653589793f;//円周率
	float bulletAngle;			  //bulletの角度
};