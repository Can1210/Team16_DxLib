//#include "ShotgunBullet.h"
//#include"../../GameBase/WindowInfo.h"
////コンストラクタ
//ShotgunBullet::ShotgunBullet(Vector2 pos, CharactorManager* c, Type t, float angle)
//{
//	b_mPosittion = Vector2(pos) +Vector2(27.5f,0.0f);    //位置調整
//	b_mVelocity = Vector2(0, 0);
//	m_SetType = t;
//	b_mCircleSize = 4.0f;
//	m_pCharaManager = c;
//
//	bulletAngle = angle;
//	b_mSpeed = 300.0f;
//	mMaxTime = 0.1f;
//}
////デスストラクタ
//ShotgunBullet::~ShotgunBullet()
//{
//}
////タイプ付与
//void ShotgunBullet::setBulletType()
//{
//
//	switch (m_SetType)
//	{
//	case PLAYER:
//		b_mType = Type::PLAYER_BULLET;
//		break;
//	case SUB_PLAYER1:
//		b_mType = Type::PLAYER_BULLET;
//		break;
//	case ENEMY:
//		b_mType = Type::ENEMY_BULLET;
//		break;
//	case BOSS:
//		b_mType = Type::ENEMY_BULLET;
//		break;
//	default:
//		break;
//	}
//	//test
//}
////初期化
//void ShotgunBullet::initialize()
//{
//	setBulletType();
//	b_mVelocity = Vector2(0, 0);
//}
////更新
//void ShotgunBullet::update(float deltaTime)
//{
//	deathTime(deltaTime);
//	move(deltaTime);      //移動・死亡処理
//}
//
////描画
//void ShotgunBullet::draw(Renderer * renderer, Renderer3D * renderer3D)
//{
//	Vector2 a = RotationZ(bulletAngle);
//
//
//	float angle = atan2(a.y, a.x)* 180.0f / DX_PI_F;
//
//	renderer->draw2D("bullet1", Vector2(b_mPosittion.x, b_mPosittion.y), Vector2(0, 0), Vector2(12, 16), Vector2(6, 8), Vector2(1.0f, 1.0f), angle - 90.0f, 255);
//
//	if (b_mType == Type::ENEMY_BULLET)
//	{
//		b_mAngle = 180.0f;
//	}
//	else
//	{
//		b_mAngle = 0.0f;
//	}
//}
////当たり判定
//void ShotgunBullet::hit(BaseObject & other)
//{
//	if (b_mType == ENEMY_BULLET && other.getType() == Type::PLAYER)
//	{
//		b_mIsDeath = true;
//
//	}
//	if (b_mType == PLAYER_BULLET && other.getType() == Type::ENEMY || other.getType() == Type::BOSS)
//	{
//		b_mIsDeath = true;
//	}
//	if (b_mType == PLAYER_BULLET && other.getType() == Type::ENEMY_BULLET || b_mType == ENEMY_BULLET && other.getType() == Type::PLAYER_BULLET)
//	{
//		b_mIsDeath = true;
//	}
//}
//
////死亡にかかる時間
//void ShotgunBullet::deathTime(float deltaTime)
//{
//	//時間がたったら死ぬ
//	if (mCurrentTime >= mMaxTime)
//		b_mIsDeath = true;
//	mCurrentTime += deltaTime;
//}
//
//void ShotgunBullet::move(float deltaTime)
//{
//	b_mVelocity = RotationZ(bulletAngle);
//	b_mPosittion += b_mVelocity * deltaTime  * b_mSpeed;
//	//画面外死亡処理
//	if (b_mPosittion.y > WindowInfo::WindowHeight
//		|| b_mPosittion.y<0
//		|| b_mPosittion.x>WindowInfo::WindowWidth
//		|| b_mPosittion.x < 0)
//	{
//		b_mIsDeath = true;
//	}
//}
//
//Vector2 ShotgunBullet::RotationZ(float ang)
//{
//	Vector2 v;
//	ang = ang + 45.0f;
//	ang = ang * PI / 180.0f;
//
//	float sin = sinf(ang);
//	float cos = cosf(ang);
//
//	float x = cos + sin;
//	float y = -(sin)+cos;
//	v = Vector2(x, y);
//	return v;
//}
