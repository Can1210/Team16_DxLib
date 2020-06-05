#pragma once
#include"../CharaManager/BaseObject.h"
#include"../CharaManager/CharactorManager.h"

class UFOEnemy :public BaseObject
{
public:
	UFOEnemy(Vector2 pos, CharactorManager *c);
	~UFOEnemy();
	
	// BaseObject ‚ğ‰î‚µ‚ÄŒp³‚³‚ê‚Ü‚µ‚½
	virtual void initialize() override;

	virtual void update(float deltaTime) override;

	virtual void draw(Renderer * renderer, Renderer3D* renderer3D) override;

	virtual void hit(BaseObject & other) override;

	void Shot(Vector2 pos, float angle);
	
private:
	CharactorManager* charaManager;
	Timer *mTimer;
	Timer *mTimerDamege;
	int mDamageHit;
	float time;
	bool down;
	int subShotcnt;
};
