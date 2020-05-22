#pragma once
#include "DxLib.h"
#include "../../Math/Vector2.h"
#include "../../Device/Input.h"
#include"../../Device/Renderer.h"
#include"../CharaManager/BaseObject.h"
#include"../CharaManager/CharactorManager.h"
#include"../Player/Player.h"


class CirecleMoveEnemy :public BaseObject
{
public:
	CirecleMoveEnemy(Vector2 pos, CharactorManager *c);
	~CirecleMoveEnemy();
	// BaseObject を介して継承されました
	virtual void initialize() override;

	virtual void update(float deltaTime) override;

	virtual void draw(Renderer * renderer, Renderer3D* renderer3D) override;

	virtual void hit(BaseObject & other) override;

	void Shot(Vector2 pos);

	void SubShot(Vector2 pos);


	void Jibaku(Vector2 pos);
	//動き
	void move(float deltaTime);
	//プレイヤーの時の動き
	void playerMove(float deltaTime);
	//死亡エリア
	void deathArea();
	////プレイヤーの位置を調べる
	Vector2 checkPlayerPos(Vector2 vec);

	bool subChack();//既にサブがいるか？

private:

	bool mMoveFlag;

	Input* m_pInput;
	Timer *m_pTimer;
	CharactorManager* charaManager;
	Vector2 mPlayerPos;
	
	int subShotCnt;//合体射撃のレート
	int itemCnt;
	float itemDesthCnt;//アイテムが消えるまでを視覚的にわかなりやすく
	//円運動
	float x;
	float y;
	float radius;
	float rotateSpeed;
	float moveTime;
};
