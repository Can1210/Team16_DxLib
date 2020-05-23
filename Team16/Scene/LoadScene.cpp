#include "LoadScene.h"
#include "../Device/Loader/TextureLoad.h"
#include "../Device/Loader/SoundLoad.h"
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
	//�w�i
	TextureLoad::getInstance().add("back", "Resouce/Texture/backgraund.png");
	//�e�֌W
	TextureLoad::getInstance().add("bullet", "Resouce/Texture/Bullet.png");
	TextureLoad::getInstance().add("bullet1", "Resouce/Texture/Bullet01.png");
	TextureLoad::getInstance().add("bullet2", "Resouce/Texture/Bullet02.png");
	TextureLoad::getInstance().add("bullet3", "Resouce/Texture/Bullet03.png");
	TextureLoad::getInstance().add("bullet4", "Resouce/Texture/Bullet04.png");
	TextureLoad::getInstance().add("bullet5", "Resouce/Texture/Bullet05.png");
	TextureLoad::getInstance().add("bullet6", "Resouce/Texture/Bullet06.png"); 
	TextureLoad::getInstance().add("bossBullet", "Resouce/Texture/Bullet_S05.png");
	TextureLoad::getInstance().add("WallReflectionBullet", "Resouce/Texture/Bullet_S01.png");
	//���@�֌W
	TextureLoad::getInstance().add("player", "Resouce/Texture/F4.png");
	TextureLoad::getInstance().add("enemy" , "Resouce/Texture/TankATK.png");
	TextureLoad::getInstance().add("enemy2", "Resouce/Texture/RedBTM.png");
	TextureLoad::getInstance().add("enemy3", "Resouce/Texture/RedATK.png");
	//�t�H���g�֌W
	TextureLoad::getInstance().add("Font"  , "Resouce/Texture/font_just.png");
	TextureLoad::getInstance().add("hpNumber", "Resouce/Texture/denColor.png");
	TextureLoad::getInstance().add("sousa", "Resouce/Texture/sousa.png");
	TextureLoad::getInstance().add("sousa2", "Resouce/Texture/sousa2.png");

	//���֌W
	//BGM
	SoundLoad::getInstance().addBGM("bgm", "Resouce/Sound/BGM/bgm.mp3");

	//SE
	SoundLoad::getInstance().addSE("burst01", "Resouce/Sound/SE/burst01.mp3");
	SoundLoad::getInstance().addSE("burst02", "Resouce/Sound/SE/burst02.mp3");
	SoundLoad::getInstance().addSE("click01", "Resouce/Sound/SE/click01.mp3");
	SoundLoad::getInstance().addSE("hit", "Resouce/Sound/SE/hit.mp3");
	SoundLoad::getInstance().addSE("shot", "Resouce/Sound/SE/shot.mp3");


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
