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
	TextureLoad::getInstance().add("Mixam", "Resouce/Texture/Mixam.png");
	//UI
	TextureLoad::getInstance().add("UI", "Resouce/Texture/16Ui.png");
	//アイテム
	TextureLoad::getInstance().add("sg", "Resouce/Texture/SGanB.png");
	TextureLoad::getInstance().add("misaile", "Resouce/Texture/misaileR.png");
	TextureLoad::getInstance().add("lazer", "Resouce/Texture/lezerG.png");
	TextureLoad::getInstance().add("none", "Resouce/Texture/none.png");
	TextureLoad::getInstance().add("sgU", "Resouce/Texture/sguepun.png");
	TextureLoad::getInstance().add("misaileU", "Resouce/Texture/misaleUepon.png");
	TextureLoad::getInstance().add("lazerU", "Resouce/Texture/lazeruepon.png");
	//エフェクト
	TextureLoad::getInstance().add("deathBurst", "Resouce/Texture/burst.png");
	//背景
	TextureLoad::getInstance().add("back", "Resouce/Texture/backgraund_01.png");
	TextureLoad::getInstance().add("back2", "Resouce/Texture/backgraund_02.png");
	//弾関係
	TextureLoad::getInstance().add("bullet", "Resouce/Texture/16Bullet.png");
	TextureLoad::getInstance().add("bullet1", "Resouce/Texture/Bullet01.png");
	TextureLoad::getInstance().add("bullet2", "Resouce/Texture/Bullet02.png");
	TextureLoad::getInstance().add("bullet3", "Resouce/Texture/Bullet03.png");
	TextureLoad::getInstance().add("bullet4", "Resouce/Texture/Bullet04.png");
	TextureLoad::getInstance().add("bullet5", "Resouce/Texture/Bullet05.png");
	TextureLoad::getInstance().add("bullet6", "Resouce/Texture/Bullet06.png"); 
	TextureLoad::getInstance().add("bossBullet", "Resouce/Texture/Bullet_S05.png");
	TextureLoad::getInstance().add("misaill", "Resouce/Texture/misaille.png");
	TextureLoad::getInstance().add("bullet_en2", "Resouce/Texture/Bullet_S02.png");
	TextureLoad::getInstance().add("bullet_en3", "Resouce/Texture/Bullet_S03.png");
	TextureLoad::getInstance().add("bullet_en4", "Resouce/Texture/Bullet_S04.png");
	TextureLoad::getInstance().add("bullet_en6", "Resouce/Texture/Bullet_S06.png");
	TextureLoad::getInstance().add("Beme", "Resouce/Texture/Bemepng.png");

	TextureLoad::getInstance().add("WallReflectionBullet", "Resouce/Texture/Bullet_S01.png");
	//実機関係
	TextureLoad::getInstance().add("player", "Resouce/Texture/F4.png");
	TextureLoad::getInstance().add("player2", "Resouce/Texture/BlueRob.png");
	TextureLoad::getInstance().add("enemy" , "Resouce/Texture/TankATK.png");
	TextureLoad::getInstance().add("enemyR", "Resouce/Texture/16enemyRR.png");
	TextureLoad::getInstance().add("enemyG", "Resouce/Texture/16enemyGG.png");
	TextureLoad::getInstance().add("enemyB", "Resouce/Texture/16enemyBB.png");
	TextureLoad::getInstance().add("enemy2", "Resouce/Texture/RedBTM.png");
	TextureLoad::getInstance().add("enemy3", "Resouce/Texture/RedATK.png");
	TextureLoad::getInstance().add("enemyR2", "Resouce/Texture/16misaileE.png");
	TextureLoad::getInstance().add("boss3", "Resouce/Texture/16Boss.png");
	TextureLoad::getInstance().add("hodai", "Resouce/Texture/TankATK16.png");
	//フォント関係
	TextureLoad::getInstance().add("Font"  , "Resouce/Texture/font_just.png");
	TextureLoad::getInstance().add("hpNumber", "Resouce/Texture/denColor.png");
	TextureLoad::getInstance().add("sousa", "Resouce/Texture/sousa.png");
	TextureLoad::getInstance().add("sousa2", "Resouce/Texture/sousa2.png");

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
