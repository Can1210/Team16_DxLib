#pragma once
#include"DxLib.h"
#include "../../Math/Vector2.h"
#include"../CharaManager/CharactorManager.h"
#include"../../Device/Renderer.h"
#include"../CharaManager/BaseObject.h"
#include"../../Support/CWindow.h"

class CurveBullet : public BaseObject
{
public:
	CurveBullet(Vector2 pos, CharactorManager* c, Type t, float angle,float deltaTime);
	~CurveBullet();
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

	float PI = 3.141592653589793;//円周率
	float bulletAngle;			  //bulletの角度
	bool isFound;//見つけたかどうか
	float t;
	float rndTime;
	BaseObject* obj;//ターゲットのオブジェ
	Vector2 playerPos;//プレイヤーのpos;
	Vector2 target1, target2,enemyPos;

	void getOtherPos();	//otherPosを入れる
	int GetRandom(int min, int max);
	int GetRandom(int min, int max ,float t);
	Vector2 RotationZ(float ang);//z軸回転の成分だけ
	Vector2 traking(Vector2 v1);		//弾がターゲットに近ずく
	Vector2 VecLerp(Vector2 v1,Vector2 v2,float t);	//lerp
	Vector2 Curve(Vector2 v0, Vector2 v1, Vector2 v2, Vector2 v3, float t);
};