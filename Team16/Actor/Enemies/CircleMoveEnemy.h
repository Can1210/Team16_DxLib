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
	// BaseObject ÇâÓÇµÇƒåpè≥Ç≥ÇÍÇ‹ÇµÇΩ
	virtual void initialize() override;

	virtual void update(float deltaTime) override;

	virtual void draw(Renderer * renderer) override;

	virtual void hit(BaseObject & other) override;

	void Shot(Vector2 pos);

	void CShot(Vector2 pos);

	void Jibaku(Vector2 pos);

	virtual bool getIsDeath() const override;

	virtual Type getType() const override;

	virtual Vector2 getPpstion() const override;

	virtual float getCircleSize() const override;

	virtual Type ChangeType() override;





private:

	bool MoveFlag;
	Input* input;
	Renderer* rend;
	CharactorManager* charaManager;
	Timer *mTimer;


};
