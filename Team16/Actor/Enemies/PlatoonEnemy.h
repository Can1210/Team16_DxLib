#pragma once
#include"../CharaManager/BaseObject.h"
#include"../CharaManager/CharactorManager.h"
#include"../Enemies/Array.h"
#include"../Enemies/SoldierEnemy.h"

enum MoveType {
	Move1,
};

class PlatoonEnemy :public BaseObject
{
public:
	PlatoonEnemy(Vector2 pos, CharactorManager *c, Vector2 end);
	~PlatoonEnemy();

	
	// BaseObject ‚ğ‰î‚µ‚ÄŒp³‚³‚ê‚Ü‚µ‚½
	virtual void initialize() override;

	virtual void update(float deltaTime) override;

	virtual void draw(Renderer * renderer, Renderer3D* renderer3D) override;

	virtual void hit(BaseObject & other) override;

	void shot(Vector2 pos, float angle);

private:
	Vector2 Traking();
	int GetRandom(int min, int max);
private:
	CharactorManager* charaManager;
	Timer *mTimer;
	Timer *mTimerDamege;
	int mDamageHit;
	Vector2 start, end;
	Array<Vector2> vec_Array;
	SoldierEnemy* s1;	SoldierEnemy* s2;	SoldierEnemy* s3;	SoldierEnemy* s4;	SoldierEnemy* s5;
	int arraySize;
	int childCount;
	float angle1, angle2, angle3;
	int enemyTime;
	bool childs;
	float rnd;
	MoveType mtype;
	//‰æ‘œ‚ÌŒü‚« 
	float moveAngle;
	bool isBom;
};
