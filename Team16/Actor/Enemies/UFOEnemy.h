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
	void SubShot(Vector2 pos, float angle);
	void PlayerShot(Vector2 pos, float angle);

	

	void Jibaku(Vector2 pos);

	
private:

	bool MoveFlag;
	Input* input;
	CharactorManager* charaManager;
	Timer *mTimer;
	ChangeBullet *changeB;

	float angle1, angle2, angle3;
	Vector2 start, end;
	float time;
	bool down;

	Vector2 Traking();

	int subShotcnt;
	int itemCnt;
	float itemDesthCnt;//�A�C�e����������܂ł����o�I�ɂ킩�Ȃ�₷��
};
