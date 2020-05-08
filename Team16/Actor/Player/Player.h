#pragma once
#include"DxLib.h"
#include "../../Math/Vector2.h"
#include "../../Device/Input.h"
#include"../../Device/Renderer.h"
#include"../CharaManager/BaseObject.h"
#include"../CharaManager/CharactorManager.h"
#include<list>
#include"../Bulletes/Bullet.h"
#include"../Bulletes/TrakingBullet.h"
#include"../Bulletes/CurveBullet.h"
#include"../Bulletes/AngleBullet.h"
#include"../../Actor/Enemies/Enemy.h"
#include"../Bulletes/ChangeBullet.h"
#include "../../Support/CWindow.h"


class Player :public BaseObject
{
	//一番最初の操作キャラ、ボム使用時にこれに戻る
public:
	Player(Vector2 pos, CharactorManager *c);
	~Player();
	bool SubNull();
	

	void Shot(Vector2 pos);
	void CShot(Vector2 pos);
	void TShot(Vector2 pos,float deltaTime);

	// BaseObject を介して継承されました
	virtual void initialize() override;

	virtual void update(float deltaTime) override;

	virtual void draw(Renderer * renderer, Renderer3D* renderer3D) override;

	virtual void hit(BaseObject & other) override;

	

private:

	bool DamgeFlag;
	Input* input;
	CharactorManager* charaManager;
	Timer *mTimer;

	int shotcnt;
	int r, b;
	
};
