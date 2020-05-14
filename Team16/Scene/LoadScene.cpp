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
	TextureLoad::createInstance();   //テクスチャロードを作成

	//ゲームシーン
	//弾関係
	TextureLoad::getInstance().add("bullet", "Resouce/Texture/Bullet.png");
	TextureLoad::getInstance().add("bullet1", "Resouce/Texture/Bullet01.png");
	TextureLoad::getInstance().add("bullet2", "Resouce/Texture/Bullet02.png");
	TextureLoad::getInstance().add("bullet3", "Resouce/Texture/Bullet03.png");
	TextureLoad::getInstance().add("bullet4", "Resouce/Texture/Bullet04.png");
	TextureLoad::getInstance().add("bullet5", "Resouce/Texture/Bullet05.png");
	TextureLoad::getInstance().add("bullet6", "Resouce/Texture/Bullet06.png");
	//実機関係
	TextureLoad::getInstance().add("player", "Resouce/Texture/F4.png");
	TextureLoad::getInstance().add("enemy" , "Resouce/Texture/TankATK.png");
	TextureLoad::getInstance().add("enemy2", "Resouce/Texture/RedBTM.png");
	TextureLoad::getInstance().add("enemy3", "Resouce/Texture/RedATK.png");
	//フォント関係
	TextureLoad::getInstance().add("Font"  , "Resouce/Texture/font_just.png");
	TextureLoad::getInstance().add("hpNumber", "Resouce/Texture/denColor.png");

	//音関係
	//BGM
	SoundLoad::getInstance().addBGM("bgm", "Resouce/Sound/BGM/bgm.mp3");

	//SE
	SoundLoad::getInstance().addSE("burst01", "Resouce/Sound/SE/burst01.mp3");
	SoundLoad::getInstance().addSE("burst02", "Resouce/Sound/SE/burst02.mp3");
	SoundLoad::getInstance().addSE("click01", "Resouce/Sound/SE/click01.mp3");
	SoundLoad::getInstance().addSE("hit", "Resouce/Sound/SE/hit.mp3");
	SoundLoad::getInstance().addSE("shot", "Resouce/Sound/SE/shot.mp3");


	CWindow::getInstance().log("読み込みが終わったので終了します\n");
	isSceneEnd = true;       //ここまでエラーがなかったら終了状態にする
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
	return "title";       //終了したらtitleに行く
}
