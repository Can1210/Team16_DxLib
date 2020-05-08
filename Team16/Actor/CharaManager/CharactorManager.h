#pragma once

#ifndef _CHARACTORMANAGER_H_
#define _CHARACTORMANAGER_H_
#include <vector>
#include "BaseObject.h"
#include"../../Support/CWindow.h"
//�I�u�W�F�N�g�̊Ǘ�
class CharactorManager
{
public:
	CharactorManager();
	~CharactorManager();

	//�v���C���[������
	Vector2 searchPlayer();

	//���X�g�̃N���A
	void clear();
	//���X�g�ւ̒ǉ�
	void add(BaseObject* addObj);
	//�X�V
	void update(float deltaTime);

#pragma region update����
	void addList_update();
	void objectsManager_update(float deltaTime);
	void removeList_update();
#pragma endregion
	//�`��
	void draw(Renderer* renderer, Renderer3D* renderer3D);
	//���ݎg���Ă��郊�X�g�̎擾
	std::vector<BaseObject*> getUseList();
	//�v���C���[�̈ʒu���擾����
	Vector2 getPlayerPosition()const;

private:
	std::vector<BaseObject*> mObjectsList;        //�I�u�W�F�N�g�̃��X�g
	std::vector<BaseObject*> mAddObjectsList;     //�ǉ�����I�u�W�F�N�g
};

#endif // !_CHARACTORMANAGER_H_