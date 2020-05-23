#pragma once
#include "DxLib.h"
#include "../../Math/Vector2.h"
#include "../../Device/Input.h"
#include"../../Device/Renderer.h"
#include"../CharaManager/BaseObject.h"
#include"../CharaManager/CharactorManager.h"
#include"../Player/Player.h"


class WallReflectionEnemy :public BaseObject
{
public:
	WallReflectionEnemy(Vector2 pos, CharactorManager *c);
	~WallReflectionEnemy();
	// BaseObject ����Čp������܂���
	virtual void initialize() override;

	virtual void update(float deltaTime) override;

	virtual void draw(Renderer * renderer, Renderer3D* renderer3D) override;

	virtual void hit(BaseObject & other) override;

	void Shot(Vector2 pos);

	void SubShot(Vector2 pos);


	void Jibaku(Vector2 pos);
	//����
	void move(float deltaTime);
	//�v���C���[�̎��̓���
	void playerMove(float deltaTime);
	//���S�G���A
	void deathArea();
	////�v���C���[�̈ʒu�𒲂ׂ�
	Vector2 checkPlayerPos(Vector2 vec);

	bool subChack();//���ɃT�u�����邩�H

private:

	bool mMoveFlag;

	Input* m_pInput;
	Timer *m_pTimer;
	CharactorManager* charaManager;
	Vector2 mPlayerPos;

	Vector2 startPos;
	bool startEnd;
	int shottime;

	int subShotCnt;//���̎ˌ��̃��[�g
	int itemCnt;
	float itemDesthCnt;//�A�C�e����������܂ł����o�I�ɂ킩�Ȃ�₷��
	//�~�^��
	float x;
	float y;
	float radius;
	float rotateSpeed;
	float moveTime;
};
