#include "CurveBullet.h"
#include"../../GameBase/WindowInfo.h"
#include<math.h>
#include<cmath>
#include <stdlib.h> // rand, srand�֐�
#include <time.h>   // time�֐�

CurveBullet::CurveBullet(Vector2 pos, CharactorManager * c, Type t, float angle, float deltaTime)
{
	b_mPosittion = Vector2(pos);
	b_mVelocity = Vector2(0, 0);
	b_SetType = t;
	b_mCircleSize = 4.0f;

	bulletAngle = angle;
	charaManager = c;
	playerPos = pos;
	rndTime = deltaTime;
}

CurveBullet::~CurveBullet()
{
}

void CurveBullet::setBulletType()
{
	switch (b_SetType)
	{
	case PLAYER:
		b_mType = Type::PLAYER_BULLET;
		break;
	case ENEMY:
		b_mType = Type::ENEMY_BULLET;
		break;
	default:
		break;
	}
}

void CurveBullet::initialize()
{
	setBulletType();
	b_mVelocity = RotationZ(bulletAngle);
	t = 0;
	isFound = false;//�G�������Ă��Ȃ�
	getOtherPos();
	//target1 = Vector2(playerPos.x + GetRandom(-50, 50, rndTime), playerPos.y + GetRandom(-150, -50));//�܂΂�ɂ���̂��ނ���
	//target2 = Vector2(playerPos.x + GetRandom(-100, 100), playerPos.y + GetRandom(-250, -350, rndTime));
	float l1, l2; l1 = 0.3f; l2 = 0.7f;
	int f1, f2; f1 = GetRandom(0, 360, rndTime); f2 = GetRandom(0, 360);
	Vector2 v1, v2; v1 = RotationZ(f1); v2 = RotationZ(f2);
	if (obj  && obj->getPpstion().y < playerPos.y)
	{
		enemyPos = obj->getPpstion();
		target1 = Vector2(VecLerp(playerPos, enemyPos, l1).x, VecLerp(playerPos, enemyPos, l1).y);//�܂΂�ɂ���̂��ނ���
		target2 = Vector2(VecLerp(playerPos, enemyPos, l2).x, VecLerp(playerPos, enemyPos, l2).y);

		//v1 = Vector2(abs(target1.x + v1.x* 10.0f),abs( target1.y + v1.y * 10.0f));
		//v2 = Vector2(abs(target2.x + v2.x* 10.0f),abs( target2.y + v2.y * 10.0f));

		//target1 = Vector2(VecLerp(target1, v1, l1));
		//target2 = Vector2(VecLerp(target2, v2, l2));
	}
}

void CurveBullet::update(float deltaTime)
{
	if (b_mType == Type::PLAYER_BULLET)
	{
		t++;
		if (t > 100.0f)
			t = 0;

		if (!isFound)//�����ĂȂ�
		{
			b_mVelocity = RotationZ(bulletAngle) * 5.0f;
			b_mPosittion += b_mVelocity;
		}
		else if (isFound)
		{
			if (!obj->getIsDeath())
			{
				b_mVelocity = Curve(playerPos, target1, target2, enemyPos, t / 30.0f);
				b_mPosittion = b_mVelocity;
			}
			else if (obj->getIsDeath())
			{//�G�����Ȃ��̂Ɏ�������������Ă���ꍇ����
				b_mIsDeath = true;
			}
		}
		
	}
	else if (b_mType == Type::ENEMY_BULLET)
	{
		b_mVelocity.y += 6.0f;
		b_mPosittion += b_mVelocity;
	}

	if (b_mPosittion.y > WindowInfo::WindowHeight
		|| b_mPosittion.y<0
		|| b_mPosittion.x>WindowInfo::WindowWidth
		|| b_mPosittion.x < 0)
	{
		b_mIsDeath = true;
	}
}

void CurveBullet::draw(Renderer * renderer, Renderer3D * renderer3D)
{
	renderer->draw2D("bullet", Vector2(b_mPosittion.x, b_mPosittion.y), Vector2(0, 0), Vector2(64, 64), Vector2(32, 32), Vector2(1.0f, 1.0f), b_mAngle, 255);
	DrawCircle(target1.x + 32 / 2, target1.y + 16, b_mCircleSize / 2, GetColor(255, 0, 0), FALSE);//����
	DrawCircle(target2.x + 32 / 2, target2.y + 16, b_mCircleSize / 2, GetColor(255, 0, 0), FALSE);
	if (b_mType == Type::ENEMY_BULLET)
	{
		b_mAngle = 180.0f;
	}
}

void CurveBullet::hit(BaseObject & other)
{
	if (b_mType == ENEMY_BULLET && other.getType() == Type::PLAYER)
	{
		b_mIsDeath = true;

	}
	if (b_mType == PLAYER_BULLET && other.getType() == Type::ENEMY)
	{
		b_mIsDeath = true;

	}
	if (b_mType == PLAYER_BULLET && other.getType() == Type::ENEMY_BULLET || b_mType == ENEMY_BULLET && other.getType() == Type::PLAYER_BULLET)
	{
		b_mIsDeath = true;
	}

	DrawCircle(b_mPosittion.x + 64 / 2, b_mPosittion.y + 64 / 2, b_mCircleSize, GetColor(255, 255, 0), TRUE);
}


void CurveBullet::getOtherPos()//�^�[�Q�b�g���߂�
{
	std::vector<BaseObject*> objs = charaManager->getUseList();
	std::size_t size = objs.size();//���X�g�̑傫���ő�l
	Vector2 otherPos;//�^�[�Q�b�g�̃|�W�V����
	Vector2 v;
	float x = 5000.0f; float y = 5000.0f;
	//float f = 50000.0f;playerPos.dot(otherPos) > abs(f)f = playerPos.dot(otherPos);
	for (int i = 0; i < size; i++)
	{
		if (objs[i]->getType() == Type::ENEMY && b_mType == Type::PLAYER_BULLET)//�������v���C���[�̒e��������
		{
			otherPos = objs[i]->getPpstion();
			if (playerPos.x - otherPos.x < abs(x) && playerPos.y - otherPos.y < abs(y))
			{
				x = playerPos.x - otherPos.x; y = playerPos.y - otherPos.y;
				obj = objs[i];//���̎��߂������^�[�Q�b�g�̃I�u�W�F������
				isFound = true;//�G��������
			}
		}
	}
}

int CurveBullet::GetRandom(int min, int max)
{
	unsigned int now = (unsigned int)time(0);
	srand(now);
	rand(); rand(); rand();  rand(); rand();
	return min + (int)(rand()*(max - min + 1.0) / (1.0 + RAND_MAX));
}
int CurveBullet::GetRandom(int min, int max, float t)
{
	unsigned int now = (unsigned int)time(0) / t;
	srand(now);
	rand(); rand(); rand();  rand(); rand();
	return min + (int)(rand()*(max - min + 1.0) / (1.0 + RAND_MAX));
}


Vector2 CurveBullet::traking(Vector2 v1)
{
	Vector2 v = Vector2(0, 0);
	v = b_mPosittion - obj->getPpstion();
	v = -v.normalize();
	v = Vector2(v.x * v1.x, v.y * v1.y);
	return v;
}

Vector2 CurveBullet::VecLerp(Vector2 v1, Vector2 v2, float t)
{
	float x = v1.x + t * (v2.x - v1.x);
	float y = v1.y + t * (v2.y - v1.y);
	Vector2 v = Vector2(x, y);
	return v;
}

Vector2 CurveBullet::Curve(Vector2 v0, Vector2 v1, Vector2 v2, Vector2 v3, float t)
{
	auto a = VecLerp(v0, v1, t);
	auto b = VecLerp(v1, v2, t);
	auto c = VecLerp(v2, v3, t);

	auto d = VecLerp(a, b, t);
	auto e = VecLerp(b, c, t);

	return VecLerp(d, e, t);
}

Vector2 CurveBullet::RotationZ(float ang)
{
	Vector2 v;
	ang = ang + 45.0f;
	ang = ang * PI / 180.0;

	float sin = sinf(ang);
	float cos = cosf(ang);

	float x = cos + sin;
	float y = -(sin)+cos;
	v = Vector2(x, y);
	return v;
}
