#pragma once
#include"../CharaManager/CharactorManager.h"
#include"../CharaManager/BaseObject.h"


class CircleBullet :public BaseObject
{
public:
	CircleBullet(Vector2 pos, CharactorManager* c, Type t, float angle);
	~CircleBullet();
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

private:
	CharactorManager* charaManager;
	Type b_SetType;

	bool curHit;
};
