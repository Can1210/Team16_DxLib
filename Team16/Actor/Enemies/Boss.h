#pragma once
#include "DxLib.h"
#include "../../Math/Vector2.h"
#include "../../Device/Input.h"
#include"../../Device/Renderer.h"
#include"../CharaManager/BaseObject.h"
#include"../CharaManager/CharactorManager.h"
#include"../Player/Player.h"
#include"../Bulletes/Bom.h"
#include"../Bulletes/BomBallet.h"


class Boss :public BaseObject
{
public:
	Boss(Vector2 pos, CharactorManager *c);
	~Boss();
	// BaseObject を介して継承されました
	virtual void initialize() override;

	virtual void update(float deltaTime) override;

	virtual void draw(Renderer * renderer, Renderer3D* renderer3D) override;

	virtual void hit(BaseObject & other) override;

	void Shot(Vector2 pos);

	void CShot(Vector2 pos);

	void Jibaku(Vector2 pos);

	void circleShot(float deltaTime);


	virtual bool getIsDeath() const override;

	virtual Type getType() const override;





	virtual float getCircleSize() const override;

	virtual void setIsDeath(bool isDeath) override;


	bool SubNull();
	void SubChange();

private:
	Vector2 KakoPos;//位置の保存用
	bool DamgeFlag;
	Input* input;
	Renderer* rend;
	CharactorManager* charaManager;
	Timer *mTimer;
	int shotcnt;
	int subShotCnt;//合体射撃のレート
	int r, b;

	Timer* m_pCirecleTimer;
	Timer* m_pCirecleEndTimer;

	float shotAngle;

};
