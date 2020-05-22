#pragma once
#include "../CharaManager/BaseObject.h"
#include "../CharaManager/CharactorManager.h"
//ショットガンの弾
class ShotgunBullet : public BaseObject
{
public:
	ShotgunBullet(Vector2 pos, CharactorManager* c, Type t, float angle);
	~ShotgunBullet();
private:
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
	//死亡にかかる時間
	void deathTime(float deltaTime);
	void move(float deltaTime);

	Vector2 RotationZ(float ang);//z軸回転の成分だけ

private:
	bool mIsDeath;
	Type m_SetType;
	Vector2 playerPos;//プレイヤーのpos;
	float angle;
	float PI = 3.141592653589793f;//円周率
	float bulletAngle;			  //bulletの角度
	float mCurrentTime;           //現在の時間
	float mMaxTime;               //生存時間
	CharactorManager* m_pCharaManager;

	float alphaNum;      //α値


};

