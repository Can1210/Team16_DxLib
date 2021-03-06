#pragma once
#ifndef _SHOTGUNBULLET_SIN_H_
#define _SHOTGUNBULLET_SIN_H_

#include "../CharaManager/BaseObject.h"
#include "../CharaManager/CharactorManager.h"



class ShotgunBullet_sin :public BaseObject
{
public:
	ShotgunBullet_sin(Vector2 pos, CharactorManager* c, Type t, float angle);
	~ShotgunBullet_sin();


	//初期化
	virtual void initialize()override;
	//更新
	virtual void update(float deltaTime)override;
	//描画
	virtual void draw(Renderer* renderer, Renderer3D* renderer3D)override;
	//当たりた時の処理
	virtual void hit(BaseObject& other) override;

private:
	void setBulletType();
    void deathTime(float deltaTime);
	void move(float deltaTime);

	Vector2 RotationZ(float ang);

private:
	CharactorManager* m_pCharaManager;
	float mCurrentTime;
	float mMaxTime;
	float PI = 3.141592653589793f;//円周率
	float bulletAngle;
	Type m_SetType;

};


#endif // !_SHOTGUNBULLET_SIN_H_