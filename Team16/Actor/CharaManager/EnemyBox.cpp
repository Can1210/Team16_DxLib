#include "EnemyBox.h"
#include "../../GameBase/WindowInfo.h"
#include "../Enemies/Enemy.h"
#include "../../Support/CWindow.h"

//コンストラクタ
EnemyBox::EnemyBox(CharactorManager & charactorMnager, Camera & camera, unsigned int enemyNumber, Vector2 position):
	m_pCharactorManager(&charactorMnager),
	m_pCamera(&camera),
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
}
//更新
void EnemyBox::update(float deltaTime)
{
	checkDistance();
}
//本番は無し
void EnemyBox::draw(Renderer * renderer, Renderer3D * renderer3D)
{
	//テスト描画
	renderer3D->draw3DTexture("player", Vector3(b_mPosittion.x, b_mPosittion.y, 0.0f), Vector2(0.0f, 0.0f), Vector2(64.0f, 64.0f), 96.0f, 0.0f);
}
//無し
void EnemyBox::hit(BaseObject & other)
{
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
		m_pCharactorManager->add(new Enemy(b_mPosittion, m_pCharactorManager));
		break;
	default:
		break;
	}
}
//カメラとの距離を調べる Yの距離だけ
void EnemyBox::checkDistance()
{
	float distance = 100.0f;// = Vector2((mPosition - Vector2(m_pCamera->getPosition().x, m_pCamera->getPosition().y))).length();// = a.y - mPosition.y;

	//カメラとの距離が描画範囲（縦）より小さくなったら生成する
	if (distance <= WindowInfo::WindowHeight)
	{
		//spawn();
		//b_mIsDeath = true;      //生成したら自分を消す
	}
}

void EnemyBox::setPosition(Vector2 position)
{
	b_mPosittion = position;
}
