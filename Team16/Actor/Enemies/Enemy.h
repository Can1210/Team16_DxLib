#pragma once
#include "DxLib.h"
#include "../../Math/Vector2.h"
#include "../../Device/Input.h"
#include"../../Device/Renderer.h"
#include"../CharaManager/BaseObject.h"
#include"../CharaManager/CharactorManager.h"
#include"../Player/Player.h"
#include"../Bulletes/Bom.h"
#include"../Bulletes/ChangeBullet.h"


class Enemy :public BaseObject
{
public:
	Enemy(Vector2 pos, CharactorManager *c);
	~Enemy();

	// BaseObject を介して継承されました
	virtual void initialize() override;

	virtual void update(float deltaTime) override;

	virtual void draw(Renderer * renderer, Renderer3D* renderer3D) override;

	virtual void hit(BaseObject & other) override;

	void Shot(Vector2 pos);

	

	void Jibaku(Vector2 pos);

	bool subChack();//既にサブがいるか？
private:
	Vector2 KakoPos;//位置の保存用
	
	Input* input;
	CharactorManager* charaManager;
	Timer *mTimer;
	int subShotCnt;
	int itemCnt;
	float itemDesthCnt;//アイテムが消えるまでを視覚的にわかなりやすく
	
};
