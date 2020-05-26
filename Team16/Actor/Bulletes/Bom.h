#pragma once
#include"../CharaManager/CharactorManager.h"
#include"../CharaManager/BaseObject.h"

class Bom :public BaseObject
{
public:
	Bom(Vector2 pos, CharactorManager* c);
	~Bom();
	//������
	virtual void initialize()override;
	//�X�V
	virtual void update(float deltaTime)override;
	//�`��
	virtual void draw(Renderer* renderer, Renderer3D* renderer3D)override;
	//�����肽���̏���
	virtual void hit(BaseObject& other) override;

	virtual Type getType() const override;
private:
	CharactorManager* charaManager;
	Timer *mTimer;
};