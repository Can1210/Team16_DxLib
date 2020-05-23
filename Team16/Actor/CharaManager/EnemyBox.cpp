#include "EnemyBox.h"
#include "../../GameBase/WindowInfo.h"
#include "../Enemies/Enemy.h"
#include "../../Support/CWindow.h"

//�R���X�g���N�^
EnemyBox::EnemyBox(CharactorManager & charactorMnager, Camera & camera, unsigned int enemyNumber, Vector2 position):
	m_pCharactorManager(&charactorMnager),
	m_pCamera(&camera),
	mEnemyNum(enemyNumber)
{
	b_mPosittion = position;
}
//�f�X�X�g���N�^
EnemyBox::~EnemyBox()
{
}
void EnemyBox::initialize()
{
	b_mIsDeath = false;
}
//�X�V
void EnemyBox::update(float deltaTime)
{
	checkDistance();
}
//�{�Ԃ͖���
void EnemyBox::draw(Renderer * renderer, Renderer3D * renderer3D)
{
	//�e�X�g�`��
	renderer3D->draw3DTexture("player", Vector3(b_mPosittion.x, b_mPosittion.y, 0.0f), Vector2(0.0f, 0.0f), Vector2(64.0f, 64.0f), 96.0f, 0.0f);
}
//����
void EnemyBox::hit(BaseObject & other)
{
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
		m_pCharactorManager->add(new Enemy(b_mPosittion, m_pCharactorManager));
		break;
	default:
		break;
	}
}
//�J�����Ƃ̋����𒲂ׂ� Y�̋�������
void EnemyBox::checkDistance()
{
	float distance = 100.0f;// = Vector2((mPosition - Vector2(m_pCamera->getPosition().x, m_pCamera->getPosition().y))).length();// = a.y - mPosition.y;

	//�J�����Ƃ̋������`��͈́i�c�j��菬�����Ȃ����琶������
	if (distance <= WindowInfo::WindowHeight)
	{
		//spawn();
		//b_mIsDeath = true;      //���������玩��������
	}
}

void EnemyBox::setPosition(Vector2 position)
{
	b_mPosittion = position;
}
