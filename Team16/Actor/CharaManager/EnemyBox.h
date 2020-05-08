#pragma once
#ifndef _ENEMY_BOX_H_
#define _ENEMY_BOX_H_
#include "BaseObject.h"
#include "CharactorManager.h"
#include "../../Device/Camera.h"

//�G������
class EnemyBox
{
public:
	EnemyBox(CharactorManager& charactorMnager,Camera& camera, unsigned int enemyNumber,Vector2 position);
	~EnemyBox();

	//�X�V
	void update(float deltaTime);
	//�`��i�e�X�g�p�Ȃ̂Ŗ{�Ԃ͏����j
	void draw(Renderer* renderer, Renderer3D* renderer3D);
	//�G�̐���
	void spawn();
	//�J�����Ƃ̋����𑪂�
	void checkDistance();

#pragma region get/set
	bool getIsDeath() const;
	void setIsDeath(bool isDeath);
	Vector2 getPosition() const;
	void setPosition(Vector2 position);
#pragma endregion


private:
	CharactorManager* m_pCharactorManager;
	Camera* m_pCamera;
	unsigned int mEnemyNum;   //�G�̔ԍ�
	Vector2 mPosition;        //�����̈ʒu
	bool mIsDeath;            //����ł��邩�ǂ���
};
#endif // !_ENEMY_BOX_H_
