#include "GameManager.h"
#include "GameTime.h"
#include "../Scene/SceneManager.h"
#include "../Scene/Title.h"
#include "../Scene/GamePlay.h"
#include "../Scene/Ending.h"
#include "../Scene/LoadScene.h"
//�R���X�g���N�^
GameManager::GameManager()
{
}

//�f�X�X�g���N�^
GameManager::~GameManager()
{
	delete m_pRenderer;
	delete m_pRenderer3D;
}
//������
void GameManager::initialize(Input* input)
{
	m_pRenderer = new Renderer();
	m_pRenderer3D = new Renderer3D();
	sceneInitialize(input);   //�V�[���֌W��������
}
void GameManager::sceneInitialize(Input* input)
{
	//�V�[���}�l�[�W���[�̏�����
	SceneManager::createInstance();  //�V�[���}�l�[�W���[�̐���
	//�V�[���̒ǉ�
	SceneManager::getInstance().add("load", new LoadScene());
	SceneManager::getInstance().add("title", new Title(input));
	SceneManager::getInstance().add("gameplay", new GamePlay(input));
	SceneManager::getInstance().add("ending", new Ending(input));
	SceneManager::getInstance().change("load");      //�ŏ��̓^�C�g���ɐݒ�
}
//�X�V
void GameManager::update()
{
	//�V�[���}�l�[�W���[�̍X�V����
	SceneManager::getInstance().update(GameTime::getInstance().getDeltaTime());  //�Ƃ肠�����X�V
	SceneManager::getInstance().draw(m_pRenderer,m_pRenderer3D);
}
