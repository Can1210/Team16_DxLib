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


class Enemy :public BaseObject
{
public:
	Enemy(Vector2 pos, CharactorManager *c);
	~Enemy();

	// BaseObject ����Čp������܂���
	virtual void initialize() override;

	virtual void update(float deltaTime) override;

	virtual void draw(Renderer * renderer, Renderer3D* renderer3D) override;

	virtual void hit(BaseObject & other) override;

	void Shot(Vector2 pos);

	

	void Jibaku(Vector2 pos);

	bool subChack();//���ɃT�u�����邩�H
private:
	Vector2 KakoPos;//�ʒu�̕ۑ��p
	
	Input* input;
	CharactorManager* charaManager;
	Timer *mTimer;
	int subShotCnt;
	int itemCnt;
	float itemDesthCnt;//�A�C�e����������܂ł����o�I�ɂ킩�Ȃ�₷��
	
};
