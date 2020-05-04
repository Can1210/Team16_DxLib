#include "EnemyBox.h"
#include "../../GameBase/WindowInfo.h"
#include "../Enemies/Enemy.h"
#include "../../Support/CWindow.h"

//�R���X�g���N�^
EnemyBox::EnemyBox(CharactorManager & charactorMnager, Camera & camera, unsigned int enemyNumber, Vector2 position):
	m_pCharactorManager(&charactorMnager),
	m_pCamera(&camera),
	mEnemyNum(enemyNumber),
	mPosition(position)
{
	mIsDeath = false;   //�ŏ���false
}
//�f�X�X�g���N�^
EnemyBox::~EnemyBox()
{
}
//�X�V
void EnemyBox::update(float deltaTime)
{
	checkDistance();
}
//�e�X�g�p
void EnemyBox::draw(Renderer * renderer, Renderer3D * renderer3D)
{
	//�e�X�g�`��
	renderer3D->draw3DTexture("player", Vector3(mPosition.x, mPosition.y, 0), Vector2(0, 0), Vector2(64, 64), 64.0, 0);
}
//����
void EnemyBox::spawn()
{
	//�G�ԍ��𒲂ׂĉ��𐶐����邩�����߂�
	switch (mEnemyNum)
	{
	case 0:     //0�Ԃ͋�
		break;
	case 1:     //1�Ԃ͕��ʂ̓G
		m_pCharactorManager->add(new Enemy(mPosition, m_pCharactorManager));
		break;
	default:
		break;
	}
}
//�J�����Ƃ̋����𒲂ׂ� Y�̋�������
void EnemyBox::checkDistance()
{
	float distance = m_pCamera->getPosition().y - mPosition.y;

	//�J�����Ƃ̋������`��͈́i�c�j��菬�����Ȃ����琶������
	if (distance <= WindowInfo::WindowHeight)
	{
		
		//spawn();
		//mIsDeath = true;      //���������玩��������
	}
}

//����ł��邩�̏�Ԃ��擾
bool EnemyBox::getIsDeath() const
{
	return mIsDeath;
}
//����ł��邩�����߂�
void EnemyBox::setIsDeath(bool isDeath)
{
	mIsDeath = isDeath;
}

Vector2 EnemyBox::getPosition() const
{
	return mPosition;
}

void EnemyBox::setPosition(Vector2 position)
{
	mPosition = position;
}
