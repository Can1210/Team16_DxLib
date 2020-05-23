#include "Item.h"
#include "../../GameBase/WindowInfo.h"


//コンストラクタ
Item::Item(Vector2 pos, BulletType bulletType, std::string textureName)
{
	b_mPosittion = pos;
	mBulletType = bulletType;
	mTextureName = textureName;

}
//デスストラクタ
Item::~Item()
{
}
//初期化
void Item::initialize()
{
	b_mSpeed = 50.0f;
	b_mVelocity = Vector2(0.0f, 1.0f);  //下方向に移動
	b_mAngle = 180.0f;
	b_mType = Type::ITEM;
	b_mCircleSize = 16.0f;
	b_mIsDeath = false;
}
//更新
void Item::update(float deltaTime)
{
	deathArea();    //エリア外削除
	b_mPosittion += b_mVelocity * deltaTime*b_mSpeed;
}
//描画
void Item::draw(Renderer * renderer, Renderer3D * renderer3D)
{
	DrawCircle((int)(b_mPosittion.x + 64 / 2), (int)(b_mPosittion.y + 64 / 2), 50, GetColor(0, 255, 0), FALSE);  //後々破棄
	renderer->draw2D(mTextureName, Vector2(b_mPosittion.x, b_mPosittion.y), Vector2(0, 0), Vector2(64, 64), Vector2(32, 32), Vector2(1.0f, 1.0f), b_mAngle, 255);
}
//当たり判定
void Item::hit(BaseObject & other)
{
	//プレイヤーでなければリターン
	if (!(other.getType() == Type::PLAYER)) return;

	b_mIsDeath = true;   //プレイヤーに触れたら死亡
}
//死亡エリア
void Item::deathArea()
{
	if (b_mPosittion.y > WindowInfo::WindowHeight
		|| b_mPosittion.x > WindowInfo::WindowWidth
		|| b_mPosittion.x < 0)
	{
		b_mIsDeath = true;
	}
}
//弾の番号取得
BulletType Item::getBulletType() const
{
	return mBulletType;
}

std::string Item::getWeponName() const
{
	return mTextureName;
}
