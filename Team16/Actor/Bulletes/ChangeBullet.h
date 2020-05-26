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
	virtual void draw(Renderer* renderer, Renderer3D* renderer3D)override;
	//“–‚½‚è‚½‚Ìˆ—
	virtual void hit(BaseObject& other) override;

	virtual Type getType() const override;
	////•ÏXŒãŒãˆ—
	//void After();

private:

	float angle;
	CharactorManager* charaManager;
	
	
};