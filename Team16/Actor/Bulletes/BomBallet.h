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
	BomBullet(Vector2 pos, CharactorManager* c, Type t);
	~BomBullet();
	//弾のタイプ分け
	void setBulletType();
	//初期化
	virtual void initialize()override;
	//更新
	virtual void update(float deltaTime)override;
	//描画
	virtual void draw(Renderer* renderer)override;
	//当たりた時の処理
	virtual void hit(BaseObject& other) override;

	virtual bool getIsDeath() const override;

	virtual Type getType() const override;

	virtual Vector2 getPpstion() const override;

	virtual float getCircleSize() const override;

	virtual Type ChangeType()  override;
private:

	float angle;
	bool Death;
	Renderer* rend;
	CharactorManager* charaManager;
	Type b_SetType;
	Timer *mTimer;
	int BomFlag;
};
