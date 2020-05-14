#pragma once
#include "DxLib.h"
#include "../../Math/Vector2.h"
#include "../../Device/Input.h"
#include"../../Device/Renderer.h"
#include"../CharaManager/BaseObject.h"
#include"../CharaManager/CharactorManager.h"
#include"../Player/Player.h"
#include"../Bulletes/Bom.h"
#include"../Bulletes/ChangeBullet.h"
#include"../Enemies/Array.h"
#include"../Enemies/SoldierEnemy.h"

enum MoveType {
	Move1,
};

class PlatoonEnemy :public BaseObject
{
public:
	PlatoonEnemy(Vector2 pos, CharactorManager *c, float angle1, float angle2, float angle3, Vector2 end);
	~PlatoonEnemy();

	
	// BaseObject ‚ğ‰î‚µ‚ÄŒp³‚³‚ê‚Ü‚µ‚½
	virtual void initialize() override;

	virtual void update(float deltaTime) override;

	virtual void draw(Renderer * renderer, Renderer3D* renderer3D) override;

	virtual void hit(BaseObject & other) override;

	void Shot(Vector2 pos, float angle);

	void SubShot(Vector2 pos, float angle);

	

	void Jibaku(Vector2 pos);

private:

	bool MoveFlag;
	Input* input;
	CharactorManager* charaManager;
	Timer *mTimer;
	ChangeBullet *changeB;

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

	Vector2 Traking();
	int GetRandom(int min, int max);
	
	int subShotCnt;//‡‘ÌËŒ‚‚ÌƒŒ[ƒg
	int itemCnt;
};
