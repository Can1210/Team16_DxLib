#pragma once
#include"../CharaManager/CharactorManager.h"
#include"../CharaManager/BaseObject.h"

class Bom :public BaseObject
{
public:
	Bom(Vector2 pos, CharactorManager* c);
	~Bom();
	//初期化
	virtual void initialize()override;
	//更新
	virtual void update(float deltaTime)override;
	//描画
	virtual void draw(Renderer* renderer, Renderer3D* renderer3D)override;
	//当たりた時の処理
	virtual void hit(BaseObject& other) override;

	virtual Type getType() const override;
private:
	CharactorManager* charaManager;
	Timer *mTimer;
};