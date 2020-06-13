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
	//TextureLoad::getInstance().add("Mixam", "Resouce/Texture/BatlleFry.png");
	TextureLoad::getInstance().add("fade", "Resouce/Texture/16Fade.png");
	TextureLoad::getInstance().add("title", "Resouce/Texture/BatlleFry.png");
	TextureLoad::getInstance().add("titleText", "Resouce/Texture/StartText.png");
	TextureLoad::getInstance().add("title2", "Resouce/Texture/BatlleFry.png");
	//UI
	TextureLoad::getInstance().add("UI", "Resouce/Texture/16Ui.png");
	//アイテム
	TextureLoad::getInstance().add("sg", "Resouce/Texture/16Poteto_A.png");
	TextureLoad::getInstance().add("misaile", "Resouce/Texture/16Ebi_A.png");
	TextureLoad::getInstance().add("lazer", "Resouce/Texture/16Tikuwa_A.png");
	TextureLoad::getInstance().add("none", "Resouce/Texture/16None.png");
	TextureLoad::getInstance().add("sgU", "Resouce/Texture/16Poteto.png");
	TextureLoad::getInstance().add("misaileU", "Resouce/Texture/16Ebi_MU.png");
	TextureLoad::getInstance().add("lazerU", "Resouce/Texture/16Tikuwa.png");
	//エフェクト
	TextureLoad::getInstance().add("deathBurst", "Resouce/Texture/burst.png");
	//背景
	TextureLoad::getInstance().add("back", "Resouce/Texture/16Back.png");
	//TextureLoad::getInstance().add("back2", "Resouce/Texture/16Back.png");
	//TextureLoad::getInstance().add("back3", "Resouce/Texture/16Back.png");
	//弾関係
	TextureLoad::getInstance().add("bullet", "Resouce/Texture/16Bullet.png");
	TextureLoad::getInstance().add("bulletAge", "Resouce/Texture/16Ballet_ageage.png");
	TextureLoad::getInstance().add("bullet1", "Resouce/Texture/Bullet01.png");
	TextureLoad::getInstance().add("bullet2", "Resouce/Texture/Bullet02.png");
	TextureLoad::getInstance().add("bullet3", "Resouce/Texture/Bullet03.png");
	TextureLoad::getInstance().add("bullet4", "Resouce/Texture/Bullet04.png");
	TextureLoad::getInstance().add("bullet5", "Resouce/Texture/Bullet05.png");
	TextureLoad::getInstance().add("bullet6", "Resouce/Texture/Bullet06.png"); 
	TextureLoad::getInstance().add("bossBullet", "Resouce/Texture/Bullet_S05.png");
	TextureLoad::getInstance().add("misaill", "Resouce/Texture/16Ebi_M.png");
	TextureLoad::getInstance().add("bullet_en2", "Resouce/Texture/Bullet_S02.png");
	TextureLoad::getInstance().add("bullet_en3", "Resouce/Texture/Bullet_S03.png");
	TextureLoad::getInstance().add("bullet_en4", "Resouce/Texture/Bullet_S04.png");
	TextureLoad::getInstance().add("bullet_en6", "Resouce/Texture/Bullet_S06.png");
	TextureLoad::getInstance().add("Beme", "Resouce/Texture/Bemepng.png");

	TextureLoad::getInstance().add("WallReflectionBullet", "Resouce/Texture/Bullet_S01.png");
	//実機関係
	TextureLoad::getInstance().add("player", "Resouce/Texture/16Ebi.png");
	TextureLoad::getInstance().add("player2", "Resouce/Texture/BlueRob.png");
	TextureLoad::getInstance().add("enemy" , "Resouce/Texture/TankATK.png");
	TextureLoad::getInstance().add("enemyT", "Resouce/Texture/TankBTM_Re.png");
	TextureLoad::getInstance().add("enemyR", "Resouce/Texture/16enemyRR.png");
	TextureLoad::getInstance().add("enemyG", "Resouce/Texture/16Enemy_AGEL.png");
	TextureLoad::getInstance().add("enemyB", "Resouce/Texture/16Enemy_AGES.png");
	TextureLoad::getInstance().add("enemy2", "Resouce/Texture/RedBTM.png");
	TextureLoad::getInstance().add("enemy3", "Resouce/Texture/RedATK.png");
	TextureLoad::getInstance().add("enemyR2", "Resouce/Texture/16Enemy_AGEMR.png");
	TextureLoad::getInstance().add("enemyG2", "Resouce/Texture/16lazerE.png");
	TextureLoad::getInstance().add("boss", "Resouce/Texture/16Boss.png");
	TextureLoad::getInstance().add("houdai", "Resouce/Texture/TankATK16.png");
	//フォント関係
	TextureLoad::getInstance().add("Font"  , "Resouce/Texture/font_just.png");
	TextureLoad::getInstance().add("Font_white"  , "Resouce/Texture/Font.png");
	TextureLoad::getInstance().add("Font_green"  , "Resouce/Texture/Font_green.png");
	TextureLoad::getInstance().add("hpNumber", "Resouce/Texture/denColor.png");
	TextureLoad::getInstance().add("sousa", "Resouce/Texture/sousa.png");
	TextureLoad::getInstance().add("sousa2", "Resouce/Texture/sousa2.png");
	//sコア
	TextureLoad::getInstance().add("1000", "Resouce/Texture/score_1000.png");
	TextureLoad::getInstance().add("2000", "Resouce/Texture/score_2000.png");
	TextureLoad::getInstance().add("5000", "Resouce/Texture/score_5000.png");
	TextureLoad::getInstance().add("10000", "Resouce/Texture/score_10000.png");
	//音関係
	//BGM
	SoundLoad::getInstance().addBGM("bgm", "Resouce/Sound/BGM/bgm.mp3");
	SoundLoad::getInstance().addBGM("chikoku", "Resouce/Sound/BGM/chikoku.mp3");
	SoundLoad::getInstance().addBGM("mahou", "Resouce/Sound/BGM/mahounote.mp3");
	SoundLoad::getInstance().addBGM("piko", "Resouce/Sound/BGM/Picopico.mp3");
	SoundLoad::getInstance().addBGM("retro", "Resouce/Sound/BGM/retropark.mp3");

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
