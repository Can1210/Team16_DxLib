#include "BaseObject.h"


//�R���X�g���N�^
BaseObject::BaseObject()
{
}

//�f�X�X�g���N�^
BaseObject::~BaseObject()
{
}
//�~���m�̓����蔻��
bool BaseObject::circle_circle_Collision(BaseObject& other)
{
	//�����Ƒ���̋������v�Z
	float length = Vector2((b_mPosittion - other.b_mPosittion)).length();
	float radiusSum = b_mCircleSize + other.b_mCircleSize;     //��̔��a�𑫂�
	//��������̔��a���傫����Γ������Ă���
	if (length <= radiusSum)
	{
		return true;
	}
	return false;
}

bool BaseObject::getIsDeath() const
{
	return b_mIsDeath;
}

void BaseObject::setIsDeath(bool isDeath)
{
	b_mIsDeath = isDeath;
}

Type BaseObject::getType() const
{
	return b_mType;
}

Vector2 BaseObject::getPpstion() const
{
	return b_mPosittion;
}

float BaseObject::getCircleSize() const
{
	return b_mCircleSize;
}

