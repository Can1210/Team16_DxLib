#pragma once
#include"DxLib.h"
#include "../../Math/Vector2.h"
#include"../CharaManager/CharactorManager.h"
#include"../../Device/Renderer.h"
#include"../CharaManager/BaseObject.h"
#include"../../Support/CWindow.h"


class Bullet :public BaseObject
{
public:
	Bullet(Vector2 pos, CharactorManager* c, Type t);
	~Bullet();
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
	
	CharactorManager* charaManager;
	Type b_SetType;
};
