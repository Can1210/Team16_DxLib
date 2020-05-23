#pragma once
#include"../CharaManager/BaseObject.h"
#include"../CharaManager/CharactorManager.h"

class UFOEnemy :public BaseObject
{
public:
	UFOEnemy(Vector2 pos, CharactorManager *c, float angle1, float angle2, float angle3, Vector2 end);
	~UFOEnemy();
	
	// BaseObject ����Čp������܂���
	virtual void initialize() override;

	virtual void update(float deltaTime) override;

	virtual void draw(Renderer * renderer, Renderer3D* renderer3D) override;

	virtual void hit(BaseObject & other) override;

	void Shot(Vector2 pos, float angle);

private:
	Vector2 Traking();
	
private:
	CharactorManager* charaManager;
	Timer *mTimer;
	float angle1, angle2, angle3;
	Vector2 start, end;
	float time;
	bool down;
	int subShotcnt;
};
