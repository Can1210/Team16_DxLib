#include "GameManager.h"
#include "GameTime.h"
#include "Score.h"
#include "../Actor/CharaManager/DeathPoint.h"
#include "../Device/Sound.h"
#include "../Device/Camera.h"
#include "../Scene/SceneManager.h"
#include "../Scene/Title.h"
#include "../Scene/GamePlay.h"
#include "../Scene/Ending.h"
#include "../Scene/LoadScene.h"
#include "../Scene/TestScene3D.h"
#include "../Scene/Stage01.h"
#include "../Scene/Stage02.h"

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
void GameManager::initialize()
{
	m_pRenderer = new Renderer();
	m_pRenderer3D = new Renderer3D();
	sceneInitialize();             //�V�[���֌W��������
	Score::createInstance();            //�X�R�A�̐���
	Score::getInstance().initialize();  //�X�R�A�̏�����
	Sound::createInstance();
	Sound::getInstance().volumeInitialize();
	DeathPoint::createInstance();
	DeathPoint::getInstance().initialize();
	Camera::createInstance();
	Camera::getInstance().initialize();


}
void GameManager::sceneInitialize()
{
	//�V�[���}�l�[�W���[�̏�����
	SceneManager::createInstance();  //�V�[���}�l�[�W���[�̐���
	//�V�[���̒ǉ�
	SceneManager::getInstance().add("load", new LoadScene());
	SceneManager::getInstance().add("title", new Title());
	SceneManager::getInstance().add("gameplay", new GamePlay());
	SceneManager::getInstance().add("ending", new Ending());
	SceneManager::getInstance().add("test", new TestScene3D());
	SceneManager::getInstance().add("stage1", new Stage01());
	SceneManager::getInstance().add("stage2", new Stage02());
	SceneManager::getInstance().change("load");      //�ŏ��̓^�C�g���ɐݒ�

}
//�X�V
void GameManager::update()
{
	//�V�[���}�l�[�W���[�̍X�V����
	SceneManager::getInstance().update(GameTime::getInstance().getDeltaTime());  //�Ƃ肠�����X�V
	SceneManager::getInstance().draw(m_pRenderer,m_pRenderer3D);
}
