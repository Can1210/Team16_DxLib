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
	case ENEMY:
		b_mType = Type::ENEMY_BULLET;
		break;
	default:
		break;
	}
}

void TrakingBullet::initialize()
{
	setBulletType();
	b_mVelocity = Vector2(0, 0);
	isFound = false;//�G�������Ă��Ȃ�
	getOtherPos();
}

void TrakingBullet::update(float deltaTime)
{
	if (b_mType == Type::PLAYER)
	{
		if (!isFound)//�����ĂȂ�
		{
			b_mVelocity = RotationZ(bulletAngle);
		}
		else if(isFound)
		{
			if (!obj)
				b_mIsDeath = true;

			if (!obj->getIsDeath())
			{
				b_mVelocity = traking();
			}
			else if (obj->getIsDeath() && b_mVelocity.x == 0 && b_mVelocity.y == 0)
			{//�G�����Ȃ��̂Ɏ�������������Ă���ꍇ����
				b_mIsDeath = true;
			}
		}
		b_mPosittion += b_mVelocity * 5.0f;
	}
	else if (b_mType == Type::ENEMY_BULLET)
	{
		Vector2 v;
		v = b_mPosittion - charaManager->getPlayerPosition();
		b_mVelocity = -v.normalize();
		b_mPosittion += b_mVelocity * 5.0f;
	}

	if (b_mPosittion.y > WindowInfo::WindowHeight
		|| b_mPosittion.y<0
		|| b_mPosittion.x>WindowInfo::WindowWidth
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


void TrakingBullet::getOtherPos()//�^�[�Q�b�g���߂�
{
	std::vector<BaseObject*> objs = charaManager->getUseList();
	std::size_t size = objs.size();//���X�g�̑傫���ő�l
	Vector2 otherPos;//�^�[�Q�b�g�̃|�W�V����
	Vector2 v;
	float x = 5000.0f; float y = 5000.0f;
	//float f = 50000.0f;playerPos.dot(otherPos) > abs(f)f = playerPos.dot(otherPos);
	for (int i = 0; i < size; i++)
	{
		if (objs[i]->getType() == Type::ENEMY && b_mType == Type::PLAYER)//�������v���C���[�̒e��������
		{
			otherPos = objs[i]->getPpstion();
			if (playerPos.x - otherPos.x < abs(x)&& playerPos.y - otherPos.y < abs(y))
			{
				x = playerPos.x - otherPos.x; y = playerPos.y - otherPos.y;
        				obj = objs[i];//���̎��߂������^�[�Q�b�g�̃I�u�W�F������
				isFound = true;//�G��������
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
	ang = ang * PI / 180.0;

	float sin = sinf(ang);
	float cos = cosf(ang);

	float x = cos + sin;
	float y = -(sin) + cos;
	v = Vector2(x, y);
	return v;
}
