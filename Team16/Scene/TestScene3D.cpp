#include "TestScene3D.h"
#include "../Actor/CharaManager/DeathPoint.h"
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
	DeathPoint::getInstance().initialize();
	charaManager->clear();
	isSceneEnd = false;   //�ŏ���false
	charaManager->add(new Player(Vector2(0.0f, -600.0f), charaManager));  //�v���C���[
	camera = new Camera();
	camera->initialize();
	camera->setPosition(Vector2(0.0f, -600.0f));
	mapSpawn = new MapSpawn(*charaManager,*camera);
	mapSpawn->loadMap("Resouce/Map/stage01.csv");

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

	renderer3D->draw3DTexture("enemy", Vector3(camera->getPosition().x, camera->getPosition().y, 0.0f), Vector2(0.0f, 0.0f), Vector2(64.0f, 64.0f), 32.0f, 0.0f);
	
	renderer3D->draw3DTexture("enemy", Vector3(camera->getPosition().x, DeathPoint::getInstance().getUp(), 0.0f), Vector2(0.0f, 0.0f), Vector2(64.0f, 64.0f), 32.0f, 0.0f);
	renderer3D->draw3DTexture("enemy", Vector3(camera->getPosition().x, DeathPoint::getInstance().getDown(), 0.0f), Vector2(0.0f, 0.0f), Vector2(64.0f, 64.0f), 32.0f, 0.0f);
	renderer3D->draw3DTexture("enemy", Vector3(DeathPoint::getInstance().getLeft(), camera->getPosition().y, 0.0f), Vector2(0.0f, 0.0f), Vector2(64.0f, 64.0f), 32.0f, 0.0f);
	renderer3D->draw3DTexture("enemy", Vector3(DeathPoint::getInstance().getRight(), camera->getPosition().y, 0.0f), Vector2(0.0f, 0.0f), Vector2(64.0f, 64.0f), 32.0f, 0.0f);
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
