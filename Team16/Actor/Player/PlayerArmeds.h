#pragma once
#include "../Item/Item.h"

//武装ランク
enum ArmedRank {
	S_Rank,				//ノーマルショットのレートUP
	M_Rank,				//ノーマルショットのレートUP
	B_Rank,				//ノーマルショットのレートUP
	SS_Rank,			//ショットガン
	MM_Rank,			//ホーミング
	BB_Rank,			//レーザー
	SM_Rank,			//ロックオンマシンガン
	SB_Rank,			//反射ビーム
	MB_Rank,			//
	NoneRank
};

//武装 	構造体
struct Armed
{
	BulletType first; BulletType second; ArmedRank rank;
};

class PlayerArneds
{
public:
	PlayerArneds();
	~PlayerArneds();

	const int sizeMax = 25;
	//武装パターンとそのランク	グローバル変数
	const Armed gArmeds[25] = {
	{BulletType::None,BulletType::None,ArmedRank::NoneRank},

	{BulletType::T_Bullet, BulletType::None,ArmedRank::S_Rank},
	{BulletType::None,BulletType::T_Bullet,ArmedRank::S_Rank},

	{BulletType::T_TrakingBullet,BulletType::None,ArmedRank::M_Rank},
	{BulletType::None,BulletType::T_TrakingBullet,ArmedRank::M_Rank},

	{BulletType::T_LaserBullet,BulletType::None,ArmedRank::B_Rank},
	{BulletType::None,BulletType::T_LaserBullet,ArmedRank::B_Rank},

	{BulletType::T_Bullet,BulletType::T_Bullet,ArmedRank::SS_Rank},//ショットガン
	{BulletType::T_TrakingBullet,BulletType::T_TrakingBullet,ArmedRank::MM_Rank},//ホーミング
	{BulletType::T_LaserBullet,BulletType::T_LaserBullet,ArmedRank::BB_Rank},//ビーム

	{BulletType::T_Bullet,BulletType::T_TrakingBullet,ArmedRank::SM_Rank},
	{BulletType::T_TrakingBullet,BulletType::T_Bullet,ArmedRank::SM_Rank},//ロックオンマシンガン

	{BulletType::T_Bullet,BulletType::T_LaserBullet,ArmedRank::SB_Rank},
	{BulletType::T_LaserBullet,BulletType::T_Bullet,ArmedRank::SB_Rank},//反射ビーム

	{BulletType::T_TrakingBullet,BulletType::T_LaserBullet,ArmedRank::MB_Rank},
	{BulletType::T_LaserBullet,BulletType::T_TrakingBullet,ArmedRank::MB_Rank},// 16個

	{BulletType::T_AngleBullet,BulletType::None,ArmedRank::M_Rank},
	{BulletType::None,BulletType::T_AngleBullet,ArmedRank::M_Rank},//18
	{BulletType::T_AngleBullet,BulletType::T_AngleBullet,ArmedRank::SS_Rank},//19

	{BulletType::T_AngleBullet,BulletType::T_TrakingBullet,ArmedRank::SM_Rank},
	{BulletType::T_TrakingBullet,BulletType::T_AngleBullet,ArmedRank::SM_Rank},//21

	{BulletType::T_AngleBullet,BulletType::T_LaserBullet,ArmedRank::SB_Rank},
	{BulletType::T_LaserBullet,BulletType::T_AngleBullet,ArmedRank::SB_Rank},//23

	{BulletType::T_AngleBullet,BulletType::T_Bullet,ArmedRank::SM_Rank},
	{BulletType::T_Bullet,BulletType::T_AngleBullet,ArmedRank::SM_Rank},//25
	};

private:

};