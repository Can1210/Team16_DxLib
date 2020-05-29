#include "EnemyBox.h"
#include "../../GameBase/WindowInfo.h"
#include "../../Support/CWindow.h"
//�G
#include "../Enemies/Enemy.h"
#include "../Enemies/BomEnemy.h"
#include "../Enemies/CircleMoveEnemy.h"
#include "../Enemies/HomingEnemy.h"
#include "../Enemies/LaserEnemy.h"
#include "../Enemies/PlatoonEnemy.h"
#include "../Enemies/SoldierEnemy.h"
#include "../Enemies/ThreeWayEnemy.h"
#include "../Enemies/UFOEnemy.h"
#include "../Enemies/WallReflectionEnemy.h"
#include "../Enemies/Boss.h"

//�R���X�g���N�^
EnemyBox::EnemyBox(CharactorManager & charactorMnager, unsigned int enemyNumber, Vector2 position):
	m_pCharactorManager(&charactorMnager),
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
	b_mNoDeathArea = true;
	b_mType = Type::SPWAN;
}
//�X�V
void EnemyBox::update(float deltaTime)
{
	checkDistance();
}
//�{�Ԃ͖���
void EnemyBox::draw(Renderer * renderer, Renderer3D * renderer3D)
{
}
//����
void EnemyBox::hit(BaseObject & other)
{
}
//����
void EnemyBox::spawn()
{

	//�Ƃ肠�����u���Ƃ���
	//�G�ԍ��𒲂ׂĉ��𐶐����邩�����߂�
	switch (mEnemyNum)
	{
	case 0:     //0�Ԃ͋�
		break;
	case 1:     //1�Ԃ͕��ʂ̓G
		m_pCharactorManager->add(new Enemy(b_mPosittion, m_pCharactorManager));
		break;
	case 2:     
		m_pCharactorManager->add(new BomEnemy(b_mPosittion, m_pCharactorManager));
		break;
	case 3:     
		m_pCharactorManager->add(new CirecleMoveEnemy(b_mPosittion, m_pCharactorManager));
		break;
	case 4:   
		m_pCharactorManager->add(new HomingEnemy(b_mPosittion, m_pCharactorManager, m_pCharactorManager->getPlayerPosition()));
		break;
	case 5:     
		m_pCharactorManager->add(new LaserEnemy(b_mPosittion, m_pCharactorManager, m_pCharactorManager->getPlayerPosition()));
		break;
	case 6:     
		m_pCharactorManager->add(new PlatoonEnemy(b_mPosittion, m_pCharactorManager, Vector2(0.0f, 500.0f)));
		break;
	case 7:     
		m_pCharactorManager->add(new SoldierEnemy(b_mPosittion, m_pCharactorManager));
		break;
	case 8:     
		m_pCharactorManager->add(new ThreeWayEnemy(b_mPosittion, m_pCharactorManager, 260.0f, 270.0f, 280.0f, Vector2(0.0f, 1000.0f)));
		break;
	case 9:     
		m_pCharactorManager->add(new UFOEnemy(b_mPosittion, m_pCharactorManager));
		break;
	case 10:     
		m_pCharactorManager->add(new WallReflectionEnemy(b_mPosittion, m_pCharactorManager));
		break;
	case 11:
		m_pCharactorManager->add(new Boss(b_mPosittion, m_pCharactorManager));
		break;
	default:
		break;
	}
}
//�J�����Ƃ̋����𒲂ׂ� Y�̋�������
void EnemyBox::checkDistance()
{
	//��Βl�ɂ���
	float distance = std::abs(Vector2((Vector2(0.0f, b_mPosittion.y) - Vector2(0, Camera::getInstance().getPosition().y))).length());

	//�J�����Ƃ̋������`��͈́i�c�j��菬�����Ȃ����琶������
	if (distance <= 600.0f)
	{
		spawn();
		b_mIsDeath = true;      //���������玩��������
	}
}

void EnemyBox::setPosition(Vector2 position)
{
	b_mPosittion = position;
}
