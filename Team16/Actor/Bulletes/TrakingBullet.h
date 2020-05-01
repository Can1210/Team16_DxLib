#pragma once
#include"DxLib.h"
#include "../../Math/Vector2.h"
#include"../CharaManager/CharactorManager.h"
#include"../../Device/Renderer.h"
#include"../CharaManager/BaseObject.h"
#include"../../Support/CWindow.h"

class TrakingBullet : public BaseObject
{
public:
	TrakingBullet(Vector2 pos, CharactorManager* c, Type t,float angle);
	~TrakingBullet();
	//�e�̃^�C�v����
	void setBulletType();
	//������
	virtual void initialize()override;
	//�X�V
	virtual void update(float deltaTime)override;
	//�`��
	virtual void draw(Renderer* renderer, Renderer3D* renderer3D)override;
	//�����肽���̏���
	virtual void hit(BaseObject& other) override;

	virtual bool getIsDeath() const override;

	virtual Type getType() const override;

	virtual Vector2 getPpstion() const override;

	virtual float getCircleSize() const override;

	virtual void setIsDeath(bool isDeath) override;
private:
	float angle;
	bool Death;
	CharactorManager* charaManager;
	Type b_SetType;

	float bulletAngle;
	Vector2 RotationZ( float ang);//z����]�̐�������
	float PI = 3.141592653589793;
	std::vector<BaseObject*> objs;
};