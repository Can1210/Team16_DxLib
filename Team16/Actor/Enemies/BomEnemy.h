#pragma once
#include "DxLib.h"
#include "../../Math/Vector2.h"
#include "../../Device/Input.h"
#include"../../Device/Renderer.h"
#include"../CharaManager/BaseObject.h"
#include"../CharaManager/CharactorManager.h"
#include"../Player/Player.h"
#include"../Bulletes/Bom.h"
#include"../Bulletes/BomBallet.h"


class BomEnemy :public BaseObject
{
public:
	BomEnemy(Vector2 pos, CharactorManager *c);
	~BomEnemy();

	// BaseObject ����Čp������܂���
	virtual void initialize() override;

	virtual void update(float deltaTime) override;

	virtual void draw(Renderer * renderer, Renderer3D* renderer3D) override;

	virtual void hit(BaseObject & other) override;

	void Shot(Vector2 pos);

	void SubShot(Vector2 pos);

	

	void Jibaku(Vector2 pos);

	Vector2 checkPlayerPos(Vector2 vec);

	bool isShot();
	
private:
	Vector2 KakoPos;//�ʒu�̕ۑ��p
	bool DamgeFlag;
	Input* input;
	CharactorManager* charaManager;
	Timer *mTimer;
	int itemCnt;
	int subShotCnt;//���̎ˌ��̃��[�g

	Vector2 mPlayerPos;   //�v���C���[�̈ʒu

};
