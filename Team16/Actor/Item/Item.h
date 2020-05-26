#pragma once
#ifndef _ITEM_H_
#define _ITEM_H_

#include "../CharaManager/BaseObject.h"

//�e�̎��
enum BulletType
{
	None,
	T_Bullet,
	T_AngleBullet,
	T_CurveBullet,
	T_LaserBullet,
	T_Shotgun,
	T_TrakingBullet,
	T_WallRefllectionBullet,
};

//�A�C�e�����I�u�W�F�N�g
class Item : public BaseObject
{
public:
	Item(Vector2 pos, BulletType bulletType,std::string textureName);
	~Item();

	//������
	virtual void initialize()override;
	//�X�V
	virtual void update(float deltaTime)override;
	//�`��
	virtual void draw(Renderer* renderer, Renderer3D* renderer3D)override;
	//�����肽���̏���
	virtual void hit(BaseObject& other) override;

	//�e�̔ԍ��擾
	BulletType getBulletType() const;
	//
	std::string getWeponName() const;

private:
	BulletType mBulletType;
	std::string mTextureName;
};

#endif // !_ITEM_H_
