#pragma once
#ifndef _MAPSPAWN_H_
#define _MAPSPAWN_H_

#include "../../Device/CSVReader.h"
#include "../CharaManager/EnemyBox.h"

//�}�b�v�^�����N���X
class MapSpawn
{
public:
	MapSpawn(CharactorManager& charactorManager,Camera& camera);
	~MapSpawn();
	//�I�u�W�F�N�g�̒ǉ�
	std::vector<EnemyBox*> addObject(int lineCnt, std::vector<std::string> record);
	//�}�b�v�̓ǂݍ���
	void loadMap(std::string fileName);

	//���X�g�̃N���A
	void clear();
	//�X�V
	void update(float deltaTime);

	void object_update(float deltaTime);

	//�`��
	void draw(Renderer* render,Renderer3D* render3D);

	int getWidth();  //��
	int getHeight(); //����

private:
	std::vector<std::vector<EnemyBox*>> mMapObjList;   //�I�u�W�F�N�g�̃}�b�v�z�u�p
	CharactorManager* m_pCharaManager;				   //�L�����}�l��ۑ�
	Camera* m_pCamera;                                 //�J������ۑ�
};


#endif // !_MAPSPAWN_H_
