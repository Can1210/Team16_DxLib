#pragma once
#include"DxLib.h"
#include "../../Math/Vector2.h"
#include"../CharaManager/CharactorManager.h"
#include"../../Device/Renderer.h"
#include"../CharaManager/BaseObject.h"
#include"../../Support/CWindow.h"
#include"../../GameBase/WindowInfo.h"



class BomBullet :public BaseObject
{
public:
	BomBullet(Vector2 pos, CharactorManager* c, Type t,float angle);
	~BomBullet();
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

	float angle;
	bool Death;
	CharactorManager* charaManager;
	Type b_SetType;
	Timer *mTimer;
	int BomFlag;


	float PI = 3.141592653589793f;//円周率
	float bulletAngle;			  //bulletの角度
	Vector2 RotationZ(float ang);//z軸回転の成分だけ
};
