#pragma once
#include"DxLib.h"
#include "../../Math/Vector2.h"
#include"../CharaManager/CharactorManager.h"
#include"../../Device/Renderer.h"
#include"../CharaManager/BaseObject.h"
#include"../../GameBase/WindowInfo.h"

class ChangeBullet :public BaseObject
{
public:
	ChangeBullet(Vector2 pos, CharactorManager* c);
	~ChangeBullet();
	//‰Šú‰»
	virtual void initialize()override;
	//XV
	virtual void update(float deltaTime)override;
	//•`‰æ
	virtual void draw(Renderer* renderer)override;
	//“–‚½‚è‚½‚Ìˆ—
	virtual void hit(BaseObject& other) override;

	virtual bool getIsDeath() const override;

	virtual Type getType() const override;

	virtual Vector2 getPpstion() const override;

	virtual float getCircleSize() const override;

	virtual Type ChangeType()  override;



private:

	float angle;
	bool Death;
	Renderer* rend;
	CharactorManager* charaManager;
};