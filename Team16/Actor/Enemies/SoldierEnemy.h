#pragma once
#include"../CharaManager/BaseObject.h"
#include"../CharaManager/CharactorManager.h"
#include"../Enemies/Array.h"

class SoldierEnemy :public BaseObject
{
public:
	SoldierEnemy(Vector2 pos, CharactorManager *c);
	~SoldierEnemy();
	
	// BaseObject ‚ğ‰î‚µ‚ÄŒp³‚³‚ê‚Ü‚µ‚½
	virtual void initialize() override;

	virtual void update(float deltaTime) override;

	virtual void draw(Renderer * renderer, Renderer3D* renderer3D) override;

	virtual void hit(BaseObject & other) override;

	void SetParentPos(Vector2 v);

	void Shot(Vector2 pos);

private:
	CharactorManager* charaManager;
	Timer *mTimer;
	Timer *mTimerDamege;
	int mDamageHit;
};
