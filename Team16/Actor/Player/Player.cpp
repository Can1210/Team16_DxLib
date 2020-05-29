#include "Player.h"
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
#include "../../Device/Camera.h"

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
	b_mCircleSize = 12.0f;
	b_mType = Type::PLAYER;
	b_mHp = 3;                                       //Hpを設定
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
	support1 = 0; support2 = 0;//援護射撃のレート
}

void Player::update(float deltaTime)
{
	//サブ機の位置
	mSubPos[0] = b_mPosittion + Vector2(42.0f, -50.0f);
	mSubPos[1] = b_mPosittion + Vector2(-42.0f, -50.0f);

	b_mVelocity = Vector2(0, 0);   //毎回移動量を0にする
	input->update();
	mTimer->update(deltaTime);
	
	bom1();						   //ここ処理順変えないように
	bom2();                        //ここ処理順変えないように
	//無敵時間
	if (DamgeFlag&&mTimer->timerSet(2))DamgeFlag = FALSE;
//ここからパワーショット

	move();
	if (input->isKeyState(KEYCORD::SPACE))  // || input->isGamePadBottonState(GAMEPAD_KEYCORD::BUTTON_A, 0))
	{
		subShotCnt++;
		support1++; support2++;
		PowerShot();

		if (!Camera::getInstance().getStop())
		{
			b_mVelocity.y -= 1.655f * 3.0f;
		}
		b_mSpeed = 20.0f;
	}
	else
	{
		if (!Camera::getInstance().getStop())
		{
			b_mVelocity.y -= 1.655f;
		}
		b_mSpeed = 60.0f;
	}
	

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
		renderer3D->draw3DTexture("player2", Vector3(b_mPosittion.x, b_mPosittion.y, 0.0f), Vector2(0.0f, 0.0f), Vector2(64.0f, 64.0f), 140.0f, 0.0f);
		renderer->drawNumber("hpNumber", Vector2(70.0f, 850.0f), b_mHp, 0, Vector2(0.0f, 0.0f), Vector2(1.0f, 1.0f), 0.0f, 255);
	}

	//サブウェポン描画
	if (!(mSubVec[0] == BulletType::None))
	{
		switch (mSubVec[0])
		{
		case BulletType::T_Bullet:
				renderer3D->draw3DTexture("sgU", Vector3(mSubPos[0].x, mSubPos[0].y, 0.0f), Vector2(0.0f, 0.0f), Vector2(64.0f, 64.0f), 96.0f, b_mAngle);
				break;
		case BulletType::T_AngleBullet:
			renderer3D->draw3DTexture("misaileU", Vector3(mSubPos[0].x, mSubPos[0].y, 0.0f), Vector2(0.0f, 0.0f), Vector2(64.0f, 64.0f), 96.0f, b_mAngle);
			break;
		case BulletType::T_CurveBullet:
			renderer3D->draw3DTexture("misaileU", Vector3(mSubPos[0].x, mSubPos[0].y, 0.0f), Vector2(0.0f, 0.0f), Vector2(64.0f, 64.0f), 96.0f, b_mAngle);
			break;
		case BulletType::T_LaserBullet:
			renderer3D->draw3DTexture("lazerU", Vector3(mSubPos[0].x, mSubPos[0].y, 0.0f), Vector2(0.0f, 0.0f), Vector2(64.0f, 64.0f), 96.0f, b_mAngle,255,Vector2(0.5f,0.5f));
			break;
		case BulletType::T_Shotgun:
			renderer3D->draw3DTexture("sgU", Vector3(mSubPos[0].x, mSubPos[0].y, 0.0f), Vector2(0.0f, 0.0f), Vector2(64.0f, 64.0f), 96.0f, b_mAngle);
			break;
		case BulletType::T_TrakingBullet:
			renderer3D->draw3DTexture("misaileU", Vector3(mSubPos[0].x, mSubPos[0].y, 0.0f), Vector2(0.0f, 0.0f), Vector2(64.0f, 64.0f), 96.0f, b_mAngle);
			break;
		case BulletType::T_WallRefllectionBullet:
			renderer3D->draw3DTexture("lazerU", Vector3(mSubPos[0].x, mSubPos[0].y, 0.0f), Vector2(0.0f, 0.0f), Vector2(64.0f, 64.0f), 96.0f, b_mAngle, 255, Vector2(0.5f, 0.5f));
			break;
		default:
			break;
		}
	}
		
		//renderer->draw2D(mSubName[0], mSubPos[0], Vector2(0.0f, 0.0f), Vector2(64.0f, 64.0f), Vector2(32.0f, 32.0f), Vector2(1.3f, 1.3f), b_mAngle, b_mArpha);
	if (!(mSubVec[1] == BulletType::None))
	{
		switch (mSubVec[1])
		{
		case BulletType::T_Bullet:
			renderer3D->draw3DTexture("sgU", Vector3(mSubPos[1].x, mSubPos[1].y, 0.0f), Vector2(0.0f, 0.0f), Vector2(64.0f, 64.0f), 96.0f, b_mAngle);
			break;
		case BulletType::T_AngleBullet:
			renderer3D->draw3DTexture("misaileU", Vector3(mSubPos[1].x, mSubPos[1].y, 0.0f), Vector2(0.0f, 0.0f), Vector2(64.0f, 64.0f), 96.0f, b_mAngle);
			break;
		case BulletType::T_CurveBullet:
			renderer3D->draw3DTexture("misaileU", Vector3(mSubPos[1].x, mSubPos[1].y, 0.0f), Vector2(0.0f, 0.0f), Vector2(64.0f, 64.0f), 96.0f, b_mAngle);
			break;
		case BulletType::T_LaserBullet:
			renderer3D->draw3DTexture("lazerU", Vector3(mSubPos[1].x, mSubPos[1].y, 0.0f), Vector2(0.0f, 0.0f), Vector2(64.0f, 64.0f), 96.0f, b_mAngle);
			break;
		case BulletType::T_Shotgun:
			renderer3D->draw3DTexture("sgU", Vector3(mSubPos[1].x, mSubPos[1].y, 0.0f), Vector2(0.0f, 0.0f), Vector2(64.0f, 64.0f), 96.0f, b_mAngle);
			break;
		case BulletType::T_TrakingBullet:
			renderer3D->draw3DTexture("misaileU", Vector3(mSubPos[1].x, mSubPos[1].y, 0.0f), Vector2(0.0f, 0.0f), Vector2(64.0f, 64.0f), 96.0f, b_mAngle);
			break;
		case BulletType::T_WallRefllectionBullet:
			renderer3D->draw3DTexture("lazerU", Vector3(mSubPos[1].x, mSubPos[1].y, 0.0f), Vector2(0.0f, 0.0f), Vector2(64.0f, 64.0f), 96.0f, b_mAngle);
			break;
		default:
			break;
		}
	}
	
		
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
		renderer->draw2D("none", Vector2(0.0f, 780.0f), Vector2(0.0f, 0.0f), Vector2(64.0f, 64.0f), Vector2(32.0f, 32.0f), Vector2(1.0f, 1.0f), b_mAngle, 255);
	else if(amd.first == BulletType::T_Bullet || amd.first == BulletType::T_AngleBullet)
		renderer->draw2D("sg", Vector2(0.0f, 780.0f), Vector2(0.0f, 0.0f), Vector2(64.0f, 64.0f), Vector2(32.0f, 32.0f), Vector2(1.0f, 1.0f), b_mAngle, 255);
	else if(amd.first == BulletType::T_LaserBullet)
		renderer->draw2D("lazer", Vector2(0.0f, 780.0f), Vector2(0.0f, 0.0f), Vector2(64.0f, 64.0f), Vector2(32.0f, 32.0f), Vector2(1.0f, 1.0f), b_mAngle, 255);
	else if(amd.first == BulletType::T_TrakingBullet)
		renderer->draw2D("misaile", Vector2(0.0f, 780.0f), Vector2(0.0f, 0.0f), Vector2(64.0f, 64.0f), Vector2(32.0f, 32.0f), Vector2(1.0f, 1.0f), b_mAngle, 255);

	if (amd.second == BulletType::None)
		renderer->draw2D("none", Vector2(70.0f, 780.0f), Vector2(0.0f, 0.0f), Vector2(64.0f, 64.0f), Vector2(32.0f, 32.0f), Vector2(1.0f, 1.0f), b_mAngle, 255);
	else if (amd.second == BulletType::T_Bullet || amd.second == BulletType::T_AngleBullet)
		renderer->draw2D("sg", Vector2(70.0f, 780.0f), Vector2(0.0f, 0.0f), Vector2(64.0f, 64.0f), Vector2(32.0f, 32.0f), Vector2(1.0f, 1.0f), b_mAngle, 255);
	else if (amd.second == BulletType::T_LaserBullet)
		renderer->draw2D("lazer", Vector2(70.0f, 780.0f), Vector2(0.0f, 0.0f), Vector2(64.0f, 64.0f), Vector2(32.0f, 32.0f), Vector2(1.0f, 1.0f), b_mAngle, 255);
	else if (amd.second == BulletType::T_TrakingBullet)
		renderer->draw2D("misaile", Vector2(70.0f, 780.0f), Vector2(0.0f, 0.0f), Vector2(64.0f, 64.0f), Vector2(32.0f, 32.0f), Vector2(1.0f, 1.0f), b_mAngle, 255);

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

		//ゲームパッド入力
		/*if (input->getGamePad_L_SticNum_X(0) >6)
		{
			b_mVelocity.x = 6;
		}
		else if(input->getGamePad_L_SticNum_X(0) < 4)
		{
			b_mVelocity.x = -6;
		}
		if (input->getGamePad_L_SticNum_Y(0) > 6)
		{
			b_mVelocity.y = 6;
		}
		else if (input->getGamePad_L_SticNum_Y(0) < 4)
		{
			b_mVelocity.y = -6;
		}*/

		//上下左右移動
		if (input->isKeyState(KEYCORD::ARROW_UP))     b_mVelocity.y = -6;
		if (input->isKeyState(KEYCORD::ARROW_DOWN))   b_mVelocity.y =  6;
		if (input->isKeyState(KEYCORD::ARROW_RIGHT))  b_mVelocity.x =  6;
		if (input->isKeyState(KEYCORD::ARROW_LEFT))   b_mVelocity.x = -6;
		if (input->isKeyDown(KEYCORD::SPACE))// || input->isGamePadBottonDown(GAMEPAD_KEYCORD::BUTTON_A, 0))
		{
			Shot(Vector2(b_mPosittion.x, b_mPosittion.y+64.0f));
			SupportShot();
		}
		//死亡処理
		if (b_mHp <= 0)
		{
			Sound::getInstance().playSE("burst02");
			b_mIsDeath = true;
			//b_mEndFlag = true;
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
	if (!mSubVec[0] == BulletType::None && mSubVec[1] == BulletType::None)
	{
		if (input->isKeyDown(KEYCORD::C))  // || input->isGamePadBottonDown(GAMEPAD_KEYCORD::BUTTON_X, 0))
		{
			//爆弾生成処理
			charaManager->add(new Bom(mSubPos[0], charaManager));
			mSubVec[0] = BulletType::None;   //無しに変更する
			amd.first = BulletType::None;   //無しに変更する
			ArmedRankCheck();
		}
	}
}

void Player::bom2()
{
	//0番目がNoneなら通る
	if (mSubVec[1] == BulletType::None) return;
	if (input->isKeyDown(KEYCORD::C))// || input->isGamePadBottonDown(GAMEPAD_KEYCORD::BUTTON_X, 0))
	{
		//爆弾生成処理
		charaManager->add(new Bom(mSubPos[1], charaManager));
		mSubVec[1] = BulletType::None;   //無しに変更する
		amd.second = BulletType::None;   //無しに変更する
		ArmedRankCheck();

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
			subShotCnt = 0;
		}
		break;
	case ArmedRank::S_Rank://レートが上がるだけ
		if (subShotCnt > 5)
		{
			charaManager->add(new Bullet(Vector2(b_mPosittion.x, b_mPosittion.y + 40.0f), charaManager, b_mType, 0.0f));
			//charaManager->add(new AngleBullet(b_mPosittion, charaManager, b_mType, 90.0f));
			Sound::getInstance().playSE("shot");
			subShotCnt = 0;
		}
		break;
	case ArmedRank::M_Rank://レートが上がるだけ
		if (subShotCnt > 5)
		{
			charaManager->add(new Bullet(Vector2(b_mPosittion.x, b_mPosittion.y + 40.0f), charaManager, b_mType, 0.0f));
			Sound::getInstance().playSE("shot");
			subShotCnt = 0;
		}
		break;
	case ArmedRank::B_Rank://レートが上がるだけ
		if (subShotCnt > 5)
		{
			charaManager->add(new Bullet(Vector2(b_mPosittion.x, b_mPosittion.y + 40.0f), charaManager, b_mType, 0.0f));
			Sound::getInstance().playSE("shot");
			subShotCnt = 0;
		}
		break;
	case ArmedRank::SS_Rank://ショットガン
		if (subShotCnt > 5)
		{
			charaManager->add(new Shotgun(Vector2(b_mPosittion.x -34.0f, b_mPosittion.y + 40.0f), *charaManager, b_mType, 0.0f));
			Sound::getInstance().playSE("shot");
			subShotCnt = 0;
		}
		break;
	case ArmedRank::MM_Rank://ホーミングミサイル
		if (subShotCnt > 20)
		{
			charaManager->add(new TrakingBullet(Vector2(b_mPosittion.x+30, b_mPosittion.y + 40.0f), charaManager, b_mType, 90.0f));
			charaManager->add(new TrakingBullet(Vector2(b_mPosittion.x, b_mPosittion.y + 40.0f), charaManager, b_mType, 90.0f));
			charaManager->add(new TrakingBullet(Vector2(b_mPosittion.x-30, b_mPosittion.y + 40.0f), charaManager, b_mType, 90.0f));
			Sound::getInstance().playSE("shot");
			subShotCnt = 0;
		}
		break;
	case ArmedRank::BB_Rank://レーザー
		if (subShotCnt > 2)
		{
			charaManager->add(new LaserBullet(Vector2(b_mPosittion.x, b_mPosittion.y + 40.0f), charaManager, b_mType, 90.0f));
			subShotCnt = 0;
		}
		
		break;
	case ArmedRank::SM_Rank://ロックオンマシンガン
		if (subShotCnt > 5)
		{
			charaManager->add(new TrakingBullet(Vector2(b_mPosittion.x, b_mPosittion.y + 40.0f), charaManager, b_mType, 90.0f));
			Sound::getInstance().playSE("shot");
			subShotCnt = 0;
		}
		break;
	case ArmedRank::SB_Rank://反射ビーム
		if (subShotCnt > 2)
		{
			charaManager->add(new WallReflectionBullet(Vector2(b_mPosittion.x - 32, b_mPosittion.y + 40.0f) + Vector2(32.0f, 32.0f), charaManager, b_mType, 90 - 50));
			charaManager->add(new WallReflectionBullet(Vector2(b_mPosittion.x - 32, b_mPosittion.y + 40.0f) + Vector2(32.0f, 32.0f), charaManager, b_mType, 90 + 50));
			subShotCnt = 0;
		}
		
		break;
	case ArmedRank::MB_Rank:
		if (subShotCnt > 5)
		{
			charaManager->add(new Bullet(Vector2(b_mPosittion.x - 5, b_mPosittion.y + 40.0f), charaManager, b_mType, 0.0f));
			charaManager->add(new Bullet(Vector2(b_mPosittion.x, b_mPosittion.y + 40.0f), charaManager, b_mType, 0.0f));
			charaManager->add(new Bullet(Vector2(b_mPosittion.x + 5, b_mPosittion.y + 40.0f), charaManager, b_mType, 0.0f));
			Sound::getInstance().playSE("shot");
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

void Player::SupportShot()
{
	if (amd.first == BulletType::T_Bullet || amd.first == BulletType::T_AngleBullet)
	{
		if (support1 > 7)
		{
			charaManager->add(new Bullet(Vector2(mSubPos[0].x, mSubPos[0].y + 40.0f), charaManager, b_mType, 0.0f));
			support1 = 0;
		}
	}
	else if (amd.first == BulletType::T_TrakingBullet)
	{
		if (support1 > 20)
		{
			charaManager->add(new TrakingBullet(Vector2(mSubPos[0].x, mSubPos[0].y + 40.0f), charaManager, b_mType, -90.0f));
			support1 = 0;
		}
	}
	else if (amd.first == BulletType::T_LaserBullet)
	{
		if (support1 > 3)
		{
			charaManager->add(new LaserBullet(Vector2(mSubPos[0].x, mSubPos[0].y + 40.0f), charaManager, b_mType, 90.0f));
			support1 = 0;
		}
	}

	if (amd.second == BulletType::T_Bullet || amd.second == BulletType::T_AngleBullet)
	{
		if (support2 > 7)
		{
			charaManager->add(new Bullet(Vector2(mSubPos[1].x, mSubPos[1].y + 40.0f), charaManager, b_mType, 0.0f));
			support2 = 0;
		}
	}
	else if (amd.second == BulletType::T_TrakingBullet)
	{
		if (support2 > 20)
		{
			charaManager->add(new TrakingBullet(Vector2(mSubPos[1].x, mSubPos[1].y + 40.0f), charaManager, b_mType, -90.0f));
			support2 = 0;
		}
	}
	else if (amd.second == BulletType::T_LaserBullet)
	{
		if (support2 > 3)
		{
			charaManager->add(new LaserBullet(Vector2(mSubPos[1].x, mSubPos[1].y + 40.0f), charaManager, b_mType, 90.0f));
			support2 = 0;
		}
	}
}


