#include "Player.h"
#include"../../Scene/GamePlay.h"
//弾
#include"../Bulletes/Bullet.h"
#include"../Bulletes/TrakingBullet.h"
#include"../Bulletes/CurveBullet.h"
#include"../Bulletes/AngleBullet.h"
#include"../Bulletes/LaserBullet.h"
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
}


void Player::initialize()
{
	b_mEndFlag = false;
	b_mCircleSize = 16.0f;
	b_mType = Type::PLAYER;
	b_mHp = 300;
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

}

void Player::update(float deltaTime)
{
	//サブ機の位置
	mSubPos[0] = b_mPosittion + Vector2( 64.0f, 100.0f);
	mSubPos[1] = b_mPosittion + Vector2(-64.0f, 100.0f);

	b_mVelocity = Vector2(0, 0);   //毎回移動量を0にする
	input->update();
	mTimer->update(deltaTime);
	bom2();                        //ここ処理順変えないように
	bom1();						   //ここ処理順変えないように
	//無敵時間
	if (DamgeFlag&&mTimer->timerSet(2))DamgeFlag = FALSE;

	if (input->isKeyState(KEYCORD::SPACE))
	{
		subShotCnt++;
		if (subShotCnt > 20)
		{
			Shot(Vector2(b_mPosittion.x, b_mPosittion.y));
			SubShots(0);
			SubShots(1);
			subShotCnt = 0;
		}

		b_mSpeed = 20.0f;
	}
	else
		b_mSpeed = 60.0f;

	move();
	b_mPosittion += b_mVelocity * deltaTime*b_mSpeed;
}

void Player::draw(Renderer * renderer, Renderer3D* renderer3D)
{

	if (b_mType == Type::PLAYER && !b_mEndFlag)
	{
		if (DamgeFlag) b_mArpha = 155;
		else b_mArpha = 255;

		DrawBox(0,0,shotcnt,100, GetColor(r, 0, b), TRUE);
		if (shotcnt == 100)
		{
			r = 255;
			b = 0;
		}
		DrawCircle((int)(b_mPosittion.x + 64 / 2), (int)(b_mPosittion.y + 16),(int)b_mCircleSize, GetColor(0, 0, 255), FALSE);
		renderer->draw2D("player", Vector2(b_mPosittion.x, b_mPosittion.y), Vector2(0.0f, 0.0f), Vector2(64.0f, 64.0f), Vector2(32.0f, 32.0f), Vector2(1.3f, 1.3f), b_mAngle, b_mArpha);
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
		renderer->draw2D(mSubName[0], mSubPos[0], Vector2(0.0f, 0.0f), Vector2(64.0f, 64.0f), Vector2(32.0f, 32.0f), Vector2(1.3f, 1.3f), b_mAngle, b_mArpha);
	if (!(mSubVec[1] == BulletType::None))
		renderer->draw2D(mSubName[1], mSubPos[1], Vector2(0.0f, 0.0f), Vector2(64.0f, 64.0f), Vector2(32.0f, 32.0f), Vector2(1.3f, 1.3f), b_mAngle, b_mArpha);

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
			Shot(Vector2(b_mPosittion.x, b_mPosittion.y));
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
	charaManager->add(new Bullet(pos, charaManager, b_mType,0.0f));
	Sound::getInstance().playSE("shot");
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
	if (!mSubVec[0] == BulletType::None) return;
	if (input->isKeyDown(KEYCORD::C))
	{
		//爆弾生成処理
		charaManager->add(new Bom(mSubPos[1], charaManager));
		mSubVec[1] = BulletType::None;   //無しに変更する
	}
}
#pragma endregion
