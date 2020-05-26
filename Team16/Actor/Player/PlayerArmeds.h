#pragma once
#include "../Item/Item.h"

//���������N
enum ArmedRank {
	S_Rank,				//�m�[�}���V���b�g�̃��[�gUP
	M_Rank,				//�m�[�}���V���b�g�̃��[�gUP
	B_Rank,				//�m�[�}���V���b�g�̃��[�gUP
	SS_Rank,			//�V���b�g�K��
	MM_Rank,			//�z�[�~���O
	BB_Rank,			//���[�U�[
	SM_Rank,			//���b�N�I���}�V���K��
	SB_Rank,			//���˃r�[��
	MB_Rank,			//
	NoneRank
};

//���� 	�\����
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
	//�����p�^�[���Ƃ��̃����N	�O���[�o���ϐ�
	const Armed gArmeds[25] = {
	{BulletType::None,BulletType::None,ArmedRank::NoneRank},

	{BulletType::T_Bullet, BulletType::None,ArmedRank::S_Rank},
	{BulletType::None,BulletType::T_Bullet,ArmedRank::S_Rank},

	{BulletType::T_TrakingBullet,BulletType::None,ArmedRank::M_Rank},
	{BulletType::None,BulletType::T_TrakingBullet,ArmedRank::M_Rank},

	{BulletType::T_LaserBullet,BulletType::None,ArmedRank::B_Rank},
	{BulletType::None,BulletType::T_LaserBullet,ArmedRank::B_Rank},

	{BulletType::T_Bullet,BulletType::T_Bullet,ArmedRank::SS_Rank},//�V���b�g�K��
	{BulletType::T_TrakingBullet,BulletType::T_TrakingBullet,ArmedRank::MM_Rank},//�z�[�~���O
	{BulletType::T_LaserBullet,BulletType::T_LaserBullet,ArmedRank::BB_Rank},//�r�[��

	{BulletType::T_Bullet,BulletType::T_TrakingBullet,ArmedRank::SM_Rank},
	{BulletType::T_TrakingBullet,BulletType::T_Bullet,ArmedRank::SM_Rank},//���b�N�I���}�V���K��

	{BulletType::T_Bullet,BulletType::T_LaserBullet,ArmedRank::SB_Rank},
	{BulletType::T_LaserBullet,BulletType::T_Bullet,ArmedRank::SB_Rank},//���˃r�[��

	{BulletType::T_TrakingBullet,BulletType::T_LaserBullet,ArmedRank::MB_Rank},
	{BulletType::T_LaserBullet,BulletType::T_TrakingBullet,ArmedRank::MB_Rank},// 16��

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