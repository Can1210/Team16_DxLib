#pragma once
#include"../CharaManager/BaseObject.h"
#include"../CharaManager/CharactorManager.h"

class LaserEnemy :public BaseObject
{
public:
	LaserEnemy(Vector2 pos, CharactorManager *c, Vector2 end);
	~LaserEnemy();

	// BaseObject ‚ğ‰î‚µ‚ÄŒp³‚³‚ê‚Ü‚µ‚½
	virtual void initialize() override;

	virtual void update(float deltaTime) override;

	virtual void draw(Renderer * renderer, Renderer3D* renderer3D) override;

	virtual void hit(BaseObject & other) override;

	void shot(Vector2 pos, float angle);

private:
	Vector2 Traking();

private:
	CharactorManager* charaManager;
	Timer *mTimer;
	Timer *mTimerDamege;
	int mDamageHit;
	Vector2 start, end;
	float laserY;
	int hitSoundTime;
};
