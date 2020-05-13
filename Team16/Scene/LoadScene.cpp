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
	//�e�֌W
	TextureLoad::getInstance().add("bullet", "Resouce/Texture/Bullet.png");
	TextureLoad::getInstance().add("bullet1", "Resouce/Texture/Bullet01.png");
	TextureLoad::getInstance().add("bullet2", "Resouce/Texture/Bullet02.png");
	TextureLoad::getInstance().add("bullet3", "Resouce/Texture/Bullet03.png");
	TextureLoad::getInstance().add("bullet4", "Resouce/Texture/Bullet04.png");
	TextureLoad::getInstance().add("bullet5", "Resouce/Texture/Bullet05.png");
	TextureLoad::getInstance().add("bullet6", "Resouce/Texture/Bullet06.png");
	//���@�֌W
	TextureLoad::getInstance().add("player", "Resouce/Texture/F4.png");
	TextureLoad::getInstance().add("enemy" , "Resouce/Texture/TankATK.png");
	TextureLoad::getInstance().add("enemy2", "Resouce/Texture/RedBTM.png");
	TextureLoad::getInstance().add("enemy3", "Resouce/Texture/RedATK.png");
	//�t�H���g�֌W
	TextureLoad::getInstance().add("Font"  , "Resouce/Texture/font_just.png");
	TextureLoad::getInstance().add("hpNumber", "Resouce/Texture/denColor.png");
	CWindow::getInstance().log("�ǂݍ��݂��I������̂ŏI�����܂�\n");
	isSceneEnd = true;       //�����܂ŃG���[���Ȃ�������I����Ԃɂ���
}

void LoadScene::update(float deltaTime)
{
}

void LoadScene::draw(Renderer* renderer, Renderer3D* renderer3D)
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
