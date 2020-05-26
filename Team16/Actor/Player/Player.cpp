#include "Player.h"
#include"../../Scene/GamePlay.h"
#include "../../GameBase/Score.h"//Scoreが10000行けばhpが増える用

//弾
#include"../Bulletes/Bullet.h"
#include"../Bulletes/TrakingBullet.h"
#include"../Bulletes/CurveBullet.h"
#include"../Bulletes/AngleBullet.h"
#include"../Bulletes/LaserBullet.h"
#include"../Bulletes/WallReflectionBullet.h"
#include "../Bulletes/Shotgun.h"
#include "../Bulletes/Bom.h"
#include <typeinfo.h>

Player::Player(Vector2 pos, CharactorManager *c) :mTimer(new Timer())
{
	charaManager = c;
	b_mPosittion = pos;
	input = new Input;
}

Player::~Player()
{
	delete input;
	delete mTimer;
	delete playerAmds;
}


void Player::initialize()
{
	b_mEndFlag = false;
	b_mCircleSize = 16.0f;
	b_mType = Type::PLAYER;
	b_mHp = 300;                                       //Hpを設定
	hpLimit = (int)b_mHp;                                   //Hpの上限を受け取る(HP設定の下に記述)
	b_mSpeed = 60.0f;
	mTimer->initialize();
	input->init();
	shotcnt = 0;
	subShotCnt = 20;
	r = 0;
	b = 255;
	mSubVec = { BulletType::None,BulletType::None };   //無しで初期化
	mSubName = { "","" };                              //無しで初期化
	mSubPos = { Vector2(0.0f,0.0f),Vector2(0.0f,0.0f) };
	scoreCnt = 10000;                                  //scoreがどこまで行ったら回復するか設定
	scorePlus = scoreCnt;
	//パワーショット系
	amd = { BulletType::None,BulletType::None,ArmedRank::NoneRank };//無し
	playerAmds = new PlayerArneds();
	b_mNoDeathArea = true;
	b_mBulletDamage = 1.0f;//bulletの弾ダメージ1
}

void Player::update(float deltaTime)
{
	//サブ機の位置
	mSubPos[0] = b_mPosittion + Vector2(64.0f, -100.0f);
	mSubPos[1] = b_mPosittion + Vector2(-64.0f, -100.0f);

	b_mVelocity = Vector2(0, 0);   //毎回移動量を0にする
	input->update();
	mTimer->update(deltaTime);
	
	bom1();						   //ここ処理順変えないように
	bom2();                        //ここ処理順変えないように
	//無敵時間
	if (DamgeFlag&&mTimer->timerSet(2))DamgeFlag = FALSE;

	//if (input->isKeyState(KEYCORD::SPACE))
	//{
	//	subShotCnt++;
	//	if (subShotCnt > 20)
	//	{
	//		Shot(Vector2(b_mPosittion.x, b_mPosittion.y));
	//		SubShots(0);
	//		SubShots(1);
	//		subShotCnt = 0;
	//	}

	//	b_mSpeed = 20.0f;
	//}
	//else
	//	b_mSpeed = 60.0f;

//ここからパワーショット
	if (input->isKeyState(KEYCORD::SPACE))
	{
		//ArmedRankCheck();//どんな球が打てるかチェック
		subShotCnt++;
		PowerShot();

		b_mSpeed = 20.0f;
	}
	else
		b_mSpeed = 60.0f;

	move();
	b_mPosittion -= b_mVelocity * deltaTime*b_mSpeed;
}

void Player::draw(Renderer * renderer, Renderer3D* renderer3D)
{

	if (b_mType == Type::PLAYER && !b_mEndFlag)
	{
		if (DamgeFlag) b_mArpha = 155;
		else b_mArpha = 255;

		DrawBox(0, 0, shotcnt, 100, GetColor(r, 0, b), TRUE);
		if (shotcnt == 100)
		{
			r = 255;
			b = 0;
		}
		//DrawCircle((int)(b_mPosittion.x + 64 / 2), (int)(b_mPosittion.y + 16), (int)b_mCircleSize, GetColor(0, 0, 255), FALSE);
		//renderer->draw2D("player", Vector2(b_mPosittion.x, b_mPosittion.y), Vector2(0.0f, 0.0f), Vector2(64.0f, 64.0f), Vector2(32.0f, 32.0f), Vector2(1.3f, 1.3f), b_mAngle, b_mArpha);
		renderer3D->draw3DTexture("player", Vector3(b_mPosittion.x, b_mPosittion.y, 0.0f), Vector2(0.0f, 0.0f), Vector2(64.0f, 64.0f), 96.0f, 0.0f);

		renderer->drawNumber("hpNumber", Vector2(150.0f, 10.0f), b_mHp, 0, Vector2(0.0f, 0.0f), Vector2(1.0f, 1.0f), 0.0f, 255);
	}
	//ここはプレイヤーの処理じゃない
	if (b_mEndFlag)
	{
		renderer->drawText("Font", "GAMEOVER", Vector2(100, 450), Vector2(0, 0), Vector2(1, 1), 0.0f, 255);
		renderer->drawText("Font", "PUSH SPACE", Vector2(100, 550), Vector2(0, 0), Vector2(1, 1), 0.0f, 255);

		if (input->isKeyDown(KEYCORD::SPACE))
		{
			GamePlay::PlayerEnd = true;     //スタティックなので注意！！
		}
	}

	//サブウェポン描画
	if (!(mSubVec[0] == BulletType::None))
		renderer3D->draw3DTexture(mSubName[0], Vector3(mSubPos[0].x, mSubPos[0].y, 0.0f), Vector2(0.0f, 0.0f), Vector2(64.0f, 64.0f), 96.0f, b_mAngle);
		//renderer->draw2D(mSubName[0], mSubPos[0], Vector2(0.0f, 0.0f), Vector2(64.0f, 64.0f), Vector2(32.0f, 32.0f), Vector2(1.3f, 1.3f), b_mAngle, b_mArpha);
	if (!(mSubVec[1] == BulletType::None))
		renderer3D->draw3DTexture(mSubName[1], Vector3(mSubPos[1].x, mSubPos[1].y, 0.0f), Vector2(0.0f, 0.0f), Vector2(64.0f, 64.0f), 96.0f, b_mAngle);
	//HP回復処理
	PlusHp();

#pragma region パワーショット何使っているか(色)
	//パワーショット今何持ってるか表示仮　ここに書かなくてよい
	//switch (amd.rank)
	//{
	//case ArmedRank::NoneRank:
	//	DrawCircle(30, 780, 16, GetColor(255, 255, 255), TRUE);
	//	DrawCircle(70, 780, 16, GetColor(255, 255, 255), TRUE);
	//	break;
	//case ArmedRank::S_Rank:
	//	DrawCircle(70, 780, 16, GetColor(255, 255, 255), TRUE);
	//	DrawCircle(30, 780, 16, GetColor(0, 0, 255), TRUE);
	//	break;
	//case ArmedRank::M_Rank:
	//	DrawCircle(70, 780, 16, GetColor(255, 255, 255), TRUE);
	//	DrawCircle(30, 780, 16, GetColor(255, 0, 0), TRUE);
	//	break;
	//case ArmedRank::B_Rank:
	//	DrawCircle(70, 780, 16, GetColor(255, 255, 255), TRUE);
	//	DrawCircle(30, 780, 16, GetColor(0, 255, 0), TRUE);
	//	break;
	//case ArmedRank::SS_Rank:
	//	DrawCircle(30, 780, 16, GetColor(0, 0, 255), TRUE);
	//	DrawCircle(70, 780, 16, GetColor(0, 0, 255), TRUE);
	//	break;
	//case ArmedRank::MM_Rank:
	//	DrawCircle(30, 780, 16, GetColor(255, 0, 0), TRUE);
	//	DrawCircle(70, 780, 16, GetColor(255, 0, 0), TRUE);
	//	break;
	//case ArmedRank::BB_Rank:
	//	DrawCircle(30, 780, 16, GetColor(0, 255, 0), TRUE);
	//	DrawCircle(70, 780, 16, GetColor(0, 255, 0), TRUE);
	//	break;
	//case ArmedRank::SM_Rank:
	//	DrawCircle(30, 780, 16, GetColor(0, 0, 255), TRUE);
	//	DrawCircle(70, 780, 16, GetColor(255, 0, 0), TRUE);
	//	break;
	//case ArmedRank::SB_Rank:
	//	DrawCircle(30, 780, 16, GetColor(0, 0, 255), TRUE);
	//	DrawCircle(70, 780, 16, GetColor(0, 255, 0), TRUE);
	//	break;
	//case ArmedRank::MB_Rank:
	//	DrawCircle(30, 780, 16, GetColor(255, 0, 0), TRUE);
	//	DrawCircle(70, 780, 16, GetColor(0, 255, 0), TRUE);
	//	break;
	//default:
	//	break;
	//}

	if(amd.first == BulletType::None)
		DrawCircle(30, 780, 16, GetColor(255, 255, 255), TRUE);
	else if(amd.first == BulletType::T_Bullet || mSubVec[0] == BulletType::T_AngleBullet)
		DrawCircle(30, 780, 16, GetColor(0, 0, 255), TRUE);
	else if(amd.first == BulletType::T_LaserBullet)
		DrawCircle(30, 780, 16, GetColor(0, 255, 0), TRUE);
	else if(amd.first == BulletType::T_TrakingBullet)
		DrawCircle(30, 780, 16, GetColor(255, 0, 0), TRUE); 

	if (amd.second == BulletType::None)
		DrawCircle(70, 780, 16, GetColor(255, 255, 255), TRUE);
	else if (amd.second == BulletType::T_Bullet || mSubVec[1] == BulletType::T_AngleBullet)
		DrawCircle(70, 780, 16, GetColor(0, 0, 255), TRUE);
	else if (amd.second == BulletType::T_LaserBullet)
		DrawCircle(70, 780, 16, GetColor(0, 255, 0), TRUE);
	else if (amd.second == BulletType::T_TrakingBullet)
		 DrawCircle(70, 780, 16, GetColor(255, 0, 0), TRUE);

#pragma endregion
}


void Player::hit(BaseObject & other)
{
	if (!DamgeFlag)
	{
		if (other.getType() == Type::ENEMY_BULLET)
		{
			Sound::getInstance().playSE("hit");
			b_mHp -= 1;
			DrawCircle((int)(b_mPosittion.x + 64 / 2), (int)(b_mPosittion.y + 16), (int)b_mCircleSize, GetColor(255, 255, 0), TRUE);
			mTimer->initialize();
			DamgeFlag = TRUE;

		}

		if (other.getType() == Type::ENEMY)
		{
			Sound::getInstance().playSE("hit");
			b_mHp -= 1;
			DrawCircle((int)(b_mPosittion.x + 64 / 2), (int)(b_mPosittion.y + 16), (int)b_mCircleSize, GetColor(255, 255, 0), TRUE);
			mTimer->initialize();
			DamgeFlag = TRUE;

		}
	}
	//アイテムなら通す
	if (other.getType() == ITEM)
	{
		//ダウンキャスト
		Item* item = dynamic_cast<Item*>(&other);
		//1が爆破でNoneの状態の時なら追加ではなく値を入れ替える
		if (mSubVec[0] == BulletType::None)
		{
			mSubVec[0] = item->getBulletType();
			mSubName[0] = item->getWeponName();
		}
		else
		{
			//普通に追加する　・サブウェポンの上から変更する
			mSubVec.insert(mSubVec.begin(), item->getBulletType());
			mSubName.insert(mSubName.begin(), item->getWeponName());
		}

		//hitパワーショット処理
		//何も入っていなかった場合
		if (amd.first == BulletType::None && amd.second == BulletType::None)
		{
			amd.first = item->getBulletType();
		}
		else if (amd.first != BulletType::None && amd.second == BulletType::None)
		{
			BulletType tAmd = amd.first;
			amd.first = item->getBulletType();
			amd.second = tAmd;
		}
		else if(amd.first == BulletType::None && amd.second != BulletType::None)
		{
			BulletType tAmd = amd.second;
			amd.second = item->getBulletType();
			amd.first = tAmd;
		}
		else if (amd.first != BulletType::None && amd.second != BulletType::None) {
			BulletType tAmd = amd.first;
			amd.first = item->getBulletType();
			amd.second = tAmd;
		}

		ArmedRankCheck();//どんな球が打てるかチェック
	}
	
}

void Player::move()
{
	if (b_mType == Type::PLAYER && !b_mEndFlag)
	{
		//上下左右移動
		if (input->isKeyState(KEYCORD::ARROW_UP))     b_mVelocity.y -= 6;
		if (input->isKeyState(KEYCORD::ARROW_DOWN))   b_mVelocity.y += 6;
		if (input->isKeyState(KEYCORD::ARROW_RIGHT))  b_mVelocity.x += 6;
		if (input->isKeyState(KEYCORD::ARROW_LEFT))   b_mVelocity.x -= 6;
		if (input->isKeyDown(KEYCORD::SPACE))
		{
			Shot(Vector2(b_mPosittion.x, b_mPosittion.y+64.0f));
		}
		//死亡処理
		if (b_mHp <= 0)
		{
			Sound::getInstance().playSE("burst02");
			b_mEndFlag = true;
		}
	}
}

#pragma region 射撃系

//普通の射撃
void Player::Shot(Vector2 pos)
{
	charaManager->add(new Bullet(Vector2(pos.x,pos.y - 35), charaManager, b_mType, 0.0f));
	Sound::getInstance().playSE("shot");
}

//HP回復処理
void Player::PlusHp()
{
	//scoreCnt以上いったら回復 && 現在のHPが限界HPより下なら
	if (Score::getInstance().getScore() >= scoreCnt && b_mHp < hpLimit)
	{
		scoreCnt = scorePlus + Score::getInstance().getScore();//scoreCnt上限を増やす
		b_mHp++;
	}
	else if (Score::getInstance().getScore() >= scoreCnt && b_mHp == hpLimit)
	{
		scoreCnt = scorePlus + Score::getInstance().getScore();//scoreCnt上限を増やす
	}
}
//サブ射撃
void Player::SubShots(unsigned int num)
{
	switch (mSubVec[num])
	{
	case BulletType::None:    //無しなら何もしない
		break;
	case BulletType::T_Bullet:
		charaManager->add(new Bullet(mSubPos[num], charaManager, b_mType, 0.0f));
		break;
	case BulletType::T_AngleBullet:
		charaManager->add(new Bullet(mSubPos[num], charaManager, b_mType, 0.0f));
		break;
	case BulletType::T_CurveBullet:
		charaManager->add(new Bullet(mSubPos[num], charaManager, b_mType, 0.0f));
		break;
	case BulletType::T_LaserBullet:
		charaManager->add(new Bullet(mSubPos[num], charaManager, b_mType, 0.0f));
		break;
	case BulletType::T_Shotgun:
		charaManager->add(new Bullet(mSubPos[num], charaManager, b_mType, 0.0f));
		break;
	case BulletType::T_TrakingBullet:
		charaManager->add(new Bullet(mSubPos[num], charaManager, b_mType, 0.0f));
		break;
	case BulletType::T_WallRefllectionBullet:
		charaManager->add(new Bullet(mSubPos[num], charaManager, b_mType, 0.0f));
		break;
	default:
		break;
	}
}
//爆弾処理 サブ二つとも爆破可能
void Player::bom1()
{
	//爆破するのは先頭から Noneならリターン
	if (mSubVec[0] == BulletType::None) return;
	if (input->isKeyDown(KEYCORD::C))
	{
		//爆弾生成処理
		charaManager->add(new Bom(mSubPos[0], charaManager));
		mSubVec[0] = BulletType::None;   //無しに変更する
	}
}

void Player::bom2()
{
	//0番目がNoneなら通る
	if (mSubVec[1] == BulletType::None) return;
	if (input->isKeyDown(KEYCORD::C))
	{
		//爆弾生成処理
		charaManager->add(new Bom(mSubPos[1], charaManager));
		mSubVec[1] = BulletType::None;   //無しに変更する
	}
}
#pragma endregion

//各バレット処理	bulletダメージを変化
void Player::PowerShot()
{
	switch (amd.rank)
	{
	case ArmedRank::NoneRank:
		if (subShotCnt > 20)
		{
			charaManager->add(new Bullet(Vector2(b_mPosittion.x, b_mPosittion.y + 40.0f), charaManager, b_mType, 0.0f));
			Sound::getInstance().playSE("shot");
			b_mBulletDamage = 1.0f;
			subShotCnt = 0;
		}
		break;
	case ArmedRank::S_Rank://レートが上がるだけ
		if (subShotCnt > 5)
		{
			charaManager->add(new Bullet(Vector2(b_mPosittion.x, b_mPosittion.y + 40.0f), charaManager, b_mType, 0.0f));
			//charaManager->add(new AngleBullet(b_mPosittion, charaManager, b_mType, 90.0f));
			Sound::getInstance().playSE("shot");
			b_mBulletDamage = 1.0f;
			subShotCnt = 0;
		}
		break;
	case ArmedRank::M_Rank://レートが上がるだけ
		if (subShotCnt > 5)
		{
			charaManager->add(new Bullet(Vector2(b_mPosittion.x, b_mPosittion.y + 40.0f), charaManager, b_mType, 0.0f));
			Sound::getInstance().playSE("shot");
			b_mBulletDamage = 1.0f;
			subShotCnt = 0;
		}
		break;
	case ArmedRank::B_Rank://レートが上がるだけ
		if (subShotCnt > 5)
		{
			charaManager->add(new Bullet(Vector2(b_mPosittion.x, b_mPosittion.y + 40.0f), charaManager, b_mType, 0.0f));
			Sound::getInstance().playSE("shot");
			b_mBulletDamage = 1.0f;
			subShotCnt = 0;
		}
		break;
	case ArmedRank::SS_Rank://ショットガン
		if (subShotCnt > 5)
		{
			charaManager->add(new Shotgun(Vector2(b_mPosittion.x -34.0f, b_mPosittion.y + 40.0f), *charaManager, b_mType, 0.0f));
			Sound::getInstance().playSE("shot");
			b_mBulletDamage = 5.0f;
			subShotCnt = 0;
		}
		break;
	case ArmedRank::MM_Rank://ホーミングミサイル
		if (subShotCnt > 20)
		{
			charaManager->add(new TrakingBullet(Vector2(b_mPosittion.x, b_mPosittion.y + 40.0f), charaManager, b_mType, 90.0f));
			Sound::getInstance().playSE("shot");
			b_mBulletDamage = 1.5f;
			subShotCnt = 0;
		}
		break;
	case ArmedRank::BB_Rank://レーザー
		charaManager->add(new LaserBullet(Vector2(b_mPosittion.x, b_mPosittion.y + 40.0f), charaManager, b_mType, 90.0f));
		b_mBulletDamage = 0.1f;
		break;
	case ArmedRank::SM_Rank://ロックオンマシンガン
		if (subShotCnt > 5)
		{
			charaManager->add(new TrakingBullet(Vector2(b_mPosittion.x, b_mPosittion.y + 40.0f), charaManager, b_mType, 90.0f));
			Sound::getInstance().playSE("shot");
			b_mBulletDamage = 0.5f;
			subShotCnt = 0;
		}
		break;
	case ArmedRank::SB_Rank://反射ビーム
		charaManager->add(new WallReflectionBullet(Vector2(b_mPosittion.x, b_mPosittion.y + 40.0f) + Vector2(32.0f, 32.0f), charaManager, b_mType, 90 - 50));
		charaManager->add(new WallReflectionBullet(Vector2(b_mPosittion.x, b_mPosittion.y + 40.0f) + Vector2(32.0f, 32.0f), charaManager, b_mType, 90 + 50));
		b_mBulletDamage = 0.08f;
		break;
	case ArmedRank::MB_Rank:
		if (subShotCnt > 5)
		{
			charaManager->add(new Bullet(Vector2(b_mPosittion.x - 5, b_mPosittion.y + 40.0f), charaManager, b_mType, 0.0f));
			charaManager->add(new Bullet(Vector2(b_mPosittion.x, b_mPosittion.y + 40.0f), charaManager, b_mType, 0.0f));
			charaManager->add(new Bullet(Vector2(b_mPosittion.x + 5, b_mPosittion.y + 40.0f), charaManager, b_mType, 0.0f));
			Sound::getInstance().playSE("shot");
			b_mBulletDamage = 1.1f;
			subShotCnt = 0;
		}
		break;
	default:
		break;
	}
}

void Player::ArmedRankCheck()
{
	Armed tAmd = amd;
	for (int i = 0; i < playerAmds->sizeMax; i++)
	{
		BulletType f = playerAmds->gArmeds[i].first;
		BulletType s = playerAmds->gArmeds[i].second;
		if (tAmd.first == f && tAmd.second == s)
		{
			amd.first = f; amd.second = s;
			amd.rank = playerAmds->gArmeds[i].rank;
		}
	}
}