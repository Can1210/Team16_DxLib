#pragma once
#ifndef _ENEMY_BOX_H_
#define _ENEMY_BOX_H_
#include "BaseObject.h"
#include "CharactorManager.h"
#include "../../Device/Camera.h"
//敵生成箱
class EnemyBox : public BaseObject
{
public:
	EnemyBox(CharactorManager& charactorMnager, unsigned int enemyNumber,Vector2 position);
	~EnemyBox();

	// BaseObject を介して継承されました
	virtual void initialize() override;

	virtual void update(float deltaTime) override;

	virtual void draw(Renderer * renderer, Renderer3D* renderer3D) override;

	virtual void hit(BaseObject & other) override;
	//敵の生成
	void spawn();
	//カメラとの距離を測る
	void checkDistance();

	void setPosition(Vector2 position);

private:
	CharactorManager* m_pCharactorManager;
	unsigned int mEnemyNum;   //敵の番号
};
#endif // !_ENEMY_BOX_H_
