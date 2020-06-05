#pragma once
#include"../CharaManager/BaseObject.h"
#include"../CharaManager/CharactorManager.h"


class Houdai :public BaseObject
{
public:
	Houdai(Vector2 pos, CharactorManager *c);
	~Houdai();

	// BaseObject 
	virtual void initialize() override;

	virtual void update(float deltaTime) override;

	virtual void draw(Renderer * renderer, Renderer3D* renderer3D) override;

	virtual void hit(BaseObject & other) override;

	void Shot(Vector2 pos);
	//�v���C���[�̈ʒu�𒲂ׂ�
	Vector2 checkPlayerPos(Vector2 vec);
private:
	CharactorManager* charaManager;
	Timer *mTimer;

};
