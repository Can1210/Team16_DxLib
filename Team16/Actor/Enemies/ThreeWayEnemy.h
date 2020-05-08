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

class ThreeWayEnemy :public BaseObject
{
public:
	ThreeWayEnemy(Vector2 pos, CharactorManager *c,float angle1,float angle2,float angle3,Vector2 end);
	~ThreeWayEnemy();
	bool SubNull();
	void SubChange();
	// BaseObject ÇâÓÇµÇƒåpè≥Ç≥ÇÍÇ‹ÇµÇΩ
	virtual void initialize() override;

	virtual void update(float deltaTime) override;

	virtual void draw(Renderer * renderer, Renderer3D* renderer3D) override;

	virtual void hit(BaseObject & other) override;

	void Shot(Vector2 pos, float angle);

	void SubShot(Vector2 pos, float angle);

	void CShot(Vector2 pos);

	void Jibaku(Vector2 pos);

	//é©ï™ÇÃà íu
	virtual Vector2 getPpstion()const;
private:

	bool MoveFlag;
	Input* input;
	CharactorManager* charaManager;
	Timer *mTimer;
	ChangeBullet *changeB;

	float angle1, angle2, angle3;
	Vector2 start, end;

	Vector2 Traking();
	Vector2 KakoPos;//à íuÇÃï€ë∂óp

	int shotcnt;
	int r, b;
	bool DamgeFlag;
};
