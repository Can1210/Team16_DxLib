#include"TrakingBullet.h"
#include"../../GameBase/WindowInfo.h"
#include<math.h>

TrakingBullet::TrakingBullet(Vector2 pos, CharactorManager * c, Type t, float angle)
{
	b_mPosittion = Vector2(pos);
	b_mVelocity = Vector2(0, 0);
	b_SetType = t;
	b_mCircleSize = 4.0f;

	bulletAngle = angle;
	charaManager = c;
	playerPos = pos;

	setBulletType();
}

TrakingBullet::~TrakingBullet()
{
}

void TrakingBullet::setBulletType()
{
	switch (b_SetType)
	{
	case PLAYER:
		b_mType = Type::PLAYER_BULLET;
		break;
	case SUB_PLAYER1:
		b_mType = Type::PLAYER_BULLET;
		break;
	case ENEMY:
		b_mType = Type::ENEMY_BULLET;
		break;
	case BOSS:
		b_mType = Type::ENEMY_BULLET;
		break;
	default:
		break;
	}
}

void TrakingBullet::initialize()
{
	setBulletType();
	b_mVelocity = RotationZ(bulletAngle);
	isFound = false;//敵を見つけていない
	getOtherPos();
}

void TrakingBullet::update(float deltaTime)
{
	if (b_mType == Type::PLAYER_BULLET)
	{
		if (!isFound)//見つけてない
		{
			//b_mVelocity = RotationZ(bulletAngle);
			//getOtherPos();
		}
		else if (isFound)
		{
			if (!obj)
			{
				isFound = false;
				b_mIsDeath = true;
				return;
			}

			if (obj->getType() == Type::ITEM)
			{
				b_mVelocity = RotationZ(bulletAngle);
			}

			if (!obj->getIsDeath())
			{
				b_mVelocity = traking();
			}
			else if (obj->getIsDeath())
			{//敵がいないのに自分が生成されている場合死ぬ
				isFound = false;
			}
		}
		b_mPosittion += b_mVelocity * 200.0f *deltaTime;
	}
	else if (b_mType == Type::ENEMY_BULLET)
	{
		float length = Vector2((b_mPosittion - charaManager->getPlayerPosition())).length();
		if (length > 64.0f * 1.0f && !isFound)
		{
			Vector2 v;
			v = b_mPosittion - charaManager->getPlayerPosition();
			b_mVelocity = -v.normalize();
		}
		else
		{
			isFound = true;
		}
		b_mPosittion += b_mVelocity * 170.0f * deltaTime;
	}

	if (b_mPosittion.y > WindowInfo::WindowHeight
		|| b_mPosittion.y < 0
		|| b_mPosittion.x > WindowInfo::WindowWidth
		|| b_mPosittion.x < 0)
	{
		b_mIsDeath = true;
	}
}

void TrakingBullet::draw(Renderer * renderer, Renderer3D * renderer3D)
{
	renderer->draw2D("bullet", Vector2(b_mPosittion.x, b_mPosittion.y), Vector2(0, 0), Vector2(64, 64), Vector2(32, 32), Vector2(1.0f, 1.0f), b_mAngle, 255);

	if (b_mType == Type::ENEMY_BULLET)
	{
		b_mAngle = 180.0f;
	}
}

void TrakingBullet::hit(BaseObject & other)
{
	if (b_mType == ENEMY_BULLET && other.getType() == Type::PLAYER)
	{
		b_mIsDeath = true;
	}
	if (b_mType == PLAYER_BULLET && other.getType() == Type::ENEMY || other.getType() == Type::BOSS)
	{
		b_mIsDeath = true;
	}
	if (b_mType == PLAYER_BULLET && other.getType() == Type::ENEMY_BULLET || b_mType == ENEMY_BULLET && other.getType() == Type::PLAYER_BULLET)
	{
		b_mIsDeath = true;
	}
	DrawCircle((int)(b_mPosittion.x + 64.0f / 2), (int)(b_mPosittion.y + 64.0f / 2), (int)b_mCircleSize, GetColor(255, 255, 0), TRUE);
}


void TrakingBullet::getOtherPos()//ターゲットを定める
{
	std::vector<BaseObject*> objs = charaManager->getUseList();
	std::size_t size = objs.size();//リストの大きさ最大値
	Vector2 otherPos;//ターゲットのポジション
	Vector2 v;
	float l = 5000.0f;
	for (int i = 0; i < size; i++)
	{
		if (objs[i]->getType() == Type::ENEMY && b_mType == Type::PLAYER_BULLET)//自分がプレイヤーの弾だったら
		{
			otherPos = objs[i]->getPpstion();
			float length = Vector2((b_mPosittion - otherPos)).length();
			if (length < abs(l))
			{
				l = length;
				obj = objs[i];//その時近かったターゲットのオブジェを入れる
				isFound = true;//敵を見つけた
			}
		}
	}
}

Vector2 TrakingBullet::traking()
{
	Vector2 v = Vector2(0, 0);
	v = b_mPosittion - obj->getPpstion();
	v = -v.normalize();
	return v;
}

Vector2 TrakingBullet::RotationZ(float ang)
{
	Vector2 v;
	ang = ang + 45.0f;
	ang = ang * PI / 180.0f;

	float sin = sinf(ang);
	float cos = cosf(ang);

	float x = cos + sin;
	float y = -(sin)+cos;
	v = Vector2(x, y);
	return v;
}
