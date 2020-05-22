#pragma once
#include "../CharaManager/BaseObject.h"
#include "../CharaManager/CharactorManager.h"

//ショットガン
class Shotgun : public BaseObject
{
public:
	Shotgun(Vector2 pos, CharactorManager& c, Type t, float angle);
	~Shotgun();

	
	//初期化
	virtual void initialize()override;
	//更新
	virtual void update(float deltaTime)override;
	//描画
	virtual void draw(Renderer* renderer, Renderer3D* renderer3D)override;
	//当たりた時の処理
	virtual void hit(BaseObject& other) override;

private:
	//指定範囲の乱数を出す
	int getRandom(int min, int max);
	void createBullet();
	void deathTime(float deltaTime);

private:
	//だんだん小さく消える
	Type b_SetType;
	float mCenterAngle;//弾の角度
	int mBulletNum;    //弾数 ランダム
	float mRange;      //40度　　-20　～　20

	CharactorManager* m_pCharactorManager;
	float mCurrentTime;           //現在の時間
	float mMaxTime;               //生存時間
	



};
