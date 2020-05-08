#include "EnemyBox.h"
#include "../../GameBase/WindowInfo.h"
#include "../Enemies/Enemy.h"
#include "../../Support/CWindow.h"

//コンストラクタ
EnemyBox::EnemyBox(CharactorManager & charactorMnager, Camera & camera, unsigned int enemyNumber, Vector2 position):
	m_pCharactorManager(&charactorMnager),
	m_pCamera(&camera),
	mEnemyNum(enemyNumber),
	mPosition(position)
{
	mIsDeath = false;   //最初はfalse
}
//デスストラクタ
EnemyBox::~EnemyBox()
{
}
//更新
void EnemyBox::update(float deltaTime)
{
	checkDistance();
}
//テスト用
void EnemyBox::draw(Renderer * renderer, Renderer3D * renderer3D)
{
	//テスト描画
	renderer3D->draw3DTexture("player", Vector3(mPosition.x, mPosition.y, 0), Vector2(0, 0), Vector2(64, 64), 64.0, 0);
}
//生成
void EnemyBox::spawn()
{
	//敵番号を調べて何を生成するかを決める
	switch (mEnemyNum)
	{
	case 0:     //0番は空
		break;
	case 1:     //1番は普通の敵
		m_pCharactorManager->add(new Enemy(mPosition, m_pCharactorManager));
		break;
	default:
		break;
	}
}
//カメラとの距離を調べる Yの距離だけ
void EnemyBox::checkDistance()
{
	float distance = m_pCamera->getPosition().y - mPosition.y;

	//カメラとの距離が描画範囲（縦）より小さくなったら生成する
	if (distance <= WindowInfo::WindowHeight)
	{
		
		//spawn();
		//mIsDeath = true;      //生成したら自分を消す
	}
}

//死んでいるかの状態を取得
bool EnemyBox::getIsDeath() const
{
	return mIsDeath;
}
//死んでいるかを決める
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
