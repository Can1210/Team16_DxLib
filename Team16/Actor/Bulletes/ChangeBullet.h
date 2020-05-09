#pragma once
#include"DxLib.h"
#include "../../Math/Vector2.h"
#include"../CharaManager/CharactorManager.h"
#include"../../Device/Renderer.h"
#include"../CharaManager/BaseObject.h"
#include"../../GameBase/WindowInfo.h"


class ChangeBullet :public BaseObject
{
public:
	ChangeBullet(Vector2 pos, CharactorManager* c);
	~ChangeBullet();
	//初期化
	virtual void initialize()override;
	//更新
	virtual void update(float deltaTime)override;
	//描画
	virtual void draw(Renderer* renderer, Renderer3D* renderer3D)override;
	//当たりた時の処理
	virtual void hit(BaseObject& other) override;

	virtual Type getType() const override;
	//変更後後処理
	void After();
	bool SubNull();//サブがあるかどうか
private:

	float angle;
	CharactorManager* charaManager;
	
	
};