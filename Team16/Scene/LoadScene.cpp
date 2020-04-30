#include "LoadScene.h"
#include "../Device/Loader/TextureLoad.h"

LoadScene::LoadScene()
{
}


LoadScene::~LoadScene()
{
}

void LoadScene::initialize()
{
	TextureLoad::createInstance();   //�e�N�X�`�����[�h���쐬

	//�Q�[���V�[��
	TextureLoad::getInstance().add("bullet", "Resouce/Texture/Bullet.png");
	TextureLoad::getInstance().add("player", "Resouce/Texture/F4.png");
	TextureLoad::getInstance().add("enemy" , "Resouce/Texture/TankATK.png");
	TextureLoad::getInstance().add("enemy2", "Resouce/Texture/RedBTM.png");
	TextureLoad::getInstance().add("enemy3", "Resouce/Texture/RedATK.png");
	TextureLoad::getInstance().add("Font"  , "Resouce/Texture/font_just.png");
	TextureLoad::getInstance().add("hpNumber", "Resouce/Texture/denColor.png");
	CWindow::getInstance().log("�ǂݍ��݂��I������̂ŏI�����܂�");
	isSceneEnd = true;       //�����܂ŃG���[���Ȃ�������I����Ԃɂ���
}

void LoadScene::update(float deltaTime)
{
}

void LoadScene::draw(Renderer* renderer)
{
}

void LoadScene::shutdown()
{
}

bool LoadScene::isEnd()
{
	return isSceneEnd;
}

std::string LoadScene::nextScene()
{
	return "title";       //�I��������title�ɍs��
}
