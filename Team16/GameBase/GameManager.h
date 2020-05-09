#pragma once
#ifndef _GAMEMANAGER_H_
#define _GAMEMANAGER_H_
#include "../Support/Singleton.h"
#include "../Device/Renderer.h"
#include "../Device/Renderer3D.h"
#include "../Device/Input.h"

//�Q�[���S�̊Ǘ�  �V���O���g��
class GameManager :public Singleton<GameManager>
{
protected:
	GameManager();
	virtual ~GameManager();
public:
	friend class Singleton<GameManager>;        //Singleton�ł̃C���X�^���X�쐬�͋���

	//������
	void initialize(Input* input);
	void sceneInitialize(Input* input);     //�V�[���̏�����

	//�X�V
	void update();
private:
	Renderer* m_pRenderer;        //�����_���[�i�V���O���g���ł��悩�������Ǖp�ɂɎg�����R�[�h�������Ȃ邩������ɒu�����Ƃɂ���j
	Renderer3D* m_pRenderer3D;    //3D�`��
};

#endif // !_GAMEMANAGER_H_