#include "EnemyBox.h"
#include "../../GameBase/WindowInfo.h"
#include "../../Support/CWindow.h"
//敵
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

//コンストラクタ
EnemyBox::EnemyBox(CharactorManager & charactorMnager, unsigned int enemyNumber, Vector2 position):
	m_pCharactorManager(&charactorMnager),
	mEnemyNum(enemyNumber)
{
	b_mPosittion = position;
}
//デスストラクタ
EnemyBox::~EnemyBox()
{
}
void EnemyBox::initialize()
{
	b_mIsDeath = false;
	b_mNoDeathArea = true;
	b_mType = Type::SPWAN;
}
//更新
void EnemyBox::update(float deltaTime)
{
	checkDistance();
}
//本番は無し
void EnemyBox::draw(Renderer * renderer, Renderer3D * renderer3D)
{
}
//無し
void EnemyBox::hit(BaseObject & other)
{
}
//生成
void EnemyBox::spawn()
{

	//とりあえず置いといた
	//敵番号を調べて何を生成するかを決める
	switch (mEnemyNum)
	{
	case 0:     //0番は空
		break;
	case 1:     //1番は普通の敵
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
//カメラとの距離を調べる Yの距離だけ
void EnemyBox::checkDistance()
{
	//絶対値にする
	float distance = std::abs(Vector2((Vector2(0.0f, b_mPosittion.y) - Vector2(0, Camera::getInstance().getPosition().y))).length());

	//カメラとの距離が描画範囲（縦）より小さくなったら生成する
	if (distance <= 600.0f)
	{
		spawn();
		b_mIsDeath = true;      //生成したら自分を消す
	}
}

void EnemyBox::setPosition(Vector2 position)
{
	b_mPosittion = position;
}
