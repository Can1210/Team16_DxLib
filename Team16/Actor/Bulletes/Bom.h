#pragma once
#include"../CharaManager/CharactorManager.h"
#include"../CharaManager/BaseObject.h"

class Bom :public BaseObject
{
public:
	Bom(Vector2 pos, CharactorManager* c);
	~Bom();
	//‰Šú‰»
	virtual void initialize()override;
	//XV
	virtual void update(float deltaTime)override;
	//•`‰æ
	virtual void draw(Renderer* renderer, Renderer3D* renderer3D)override;
	//“–‚½‚è‚½‚Ìˆ—
	virtual void hit(BaseObject& other) override;

	virtual Type getType() const override;
private:
	CharactorManager* charaManager;
	Timer *mTimer;
};