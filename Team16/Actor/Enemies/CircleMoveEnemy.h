#pragma once
#include "DxLib.h"
#include "../../Math/Vector2.h"
#include "../../Device/Input.h"
#include"../../Device/Renderer.h"
#include"../CharaManager/BaseObject.h"
#include"../CharaManager/CharactorManager.h"
#include"../Player/Player.h"


class CirecleMoveEnemy :public BaseObject
{
public:
	CirecleMoveEnemy(Vector2 pos, CharactorManager *c);
	~CirecleMoveEnemy();
	// BaseObject ����Čp������܂���
	virtual void initialize() override;

	virtual void update(float deltaTime) override;

	virtual void draw(Renderer * renderer, Renderer3D* renderer3D) override;

	virtual void hit(BaseObject & other) override;

	void Shot(Vector2 pos);

	void CShot(Vector2 pos);

	void Jibaku(Vector2 pos);
	//����
	void move(float deltaTime);
	//�v���C���[�̎��̓���
	void playerMove(float deltaTime);
	//���S�G���A
	void deathArea();
	//�v���C���[�̈ʒu�𒲂ׂ�
	void checkPlayerPos();

private:

	bool mMoveFlag;
	Input* m_pInput;
	Timer *m_pTimer;
	CharactorManager* m_pCharaManager;
	Vector2 mPlayerPos;

	//�~�^��
	float x;
	float y;
	float radius;
	float rotateSpeed;
	float moveTime;

};
