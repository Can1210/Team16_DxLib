#include "TestScene3D.h"

//�R���X�g���N�^
TestScene3D::TestScene3D(Input * input)
{
	charaManager = new CharactorManager();
	m_pInput = input;
	
}
//�f�X�X�g���N�^
TestScene3D::~TestScene3D()
{
	delete charaManager;
	delete mapSpawn;
	delete camera;
}
//������
void TestScene3D::initialize()
{
	charaManager->clear();
	isSceneEnd = false;   //�ŏ���false
	charaManager->add(new Player(Vector2(250.0f, 600.0f), charaManager));  //�v���C���[

	camera = new Camera(*charaManager, Vector2(250.0f,600.0f));
	camera->initialize();
	mapSpawn = new MapSpawn(*charaManager,*camera);
	mapSpawn->loadMap("Resouce/Map/test01.csv");
}
//�X�V
void TestScene3D::update(float deltaTime)
{
	charaManager->update(deltaTime);
	camera->update(deltaTime);
}
//�`��
void TestScene3D::draw(Renderer * renderer, Renderer3D * renderer3D)
{
	charaManager->draw(renderer, renderer3D);
}

//�I������
void TestScene3D::shutdown()
{
}
//�V�[���I��
bool TestScene3D::isEnd()
{
	return isSceneEnd;
}
//���̃V�[��
std::string TestScene3D::nextScene()
{
	return "title";
}
