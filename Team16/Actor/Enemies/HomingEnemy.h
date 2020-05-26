#pragma once
#include "DxLib.h"
#include"../CharaManager/BaseObject.h"
#include"../CharaManager/CharactorManager.h"

class HomingEnemy :public BaseObject
{
public:
	HomingEnemy(Vector2 pos, CharactorManager *c, Vector2 end);
	~HomingEnemy();

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
	Vector2 start, end;

};
