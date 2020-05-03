#pragma once
#ifndef _ENEMY_BOX_H_
#define _ENEMY_BOX_H_
#include "BaseObject.h"
#include "CharactorManager.h"
#include "../../Device/Camera.h"

//敵生成箱
class EnemyBox
{
public:
	EnemyBox(CharactorManager& charactorMnager,Camera& camera, unsigned int enemyNumber,Vector2 position);
	~EnemyBox();

	//更新
	void update(float deltaTime);
	//描画（テスト用なので本番は消す）
	void draw(Renderer* renderer, Renderer3D* renderer3D);
	//敵の生成
	void spawn();
	//カメラとの距離を測る
	void checkDistance();

#pragma region get/set
	bool getIsDeath() const;
	void setIsDeath(bool isDeath);
	Vector2 getPosition() const;
	void setPosition(Vector2 position);
#pragma endregion


private:
	CharactorManager* m_pCharactorManager;
	Camera* m_pCamera;
	unsigned int mEnemyNum;   //敵の番号
	Vector2 mPosition;        //自分の位置
	bool mIsDeath;            //死んでいるかどうか
};
#endif // !_ENEMY_BOX_H_
