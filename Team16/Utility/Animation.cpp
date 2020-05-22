#include "Animation.h"




//コンストラクタ
Animation::Animation(Vector2 drawSize, Vector2 textureSize, float changeTime):
	mDrawSize(drawSize),
	mTextureSize(textureSize),
	m_pTimer(new Timer()),
	mChangeTime(changeTime)
{
}
//デスストラクタ
Animation::~Animation()
{
	delete m_pTimer;
}
//初期化
void Animation::initialize()
{
	m_pTimer->initialize();
}
//更新
void Animation::update(float deltaTime)
{
	changeAnimation(deltaTime);
}
//アニメーション切り替え
void Animation::changeAnimation(float deltaTime)
{
	m_pTimer->update(deltaTime);   //更新
	//タイマーのセット
	if (m_pTimer->timerSet(mChangeTime))
	{
		//左上座標がテクスチャサイズよりでかくなったら位置を0に戻す
		if ((mLeftSize.x + mDrawSize.x) >= mTextureSize.x)
		{
			mLeftSize.x = 0;
		}
		else
		{
			//左上座標を変更する
			mLeftSize.x += mDrawSize.x;
		}
	}
}
//左上座標の取得
Vector2 Animation::getLeftSize() const
{
	return mLeftSize;
}

//描画サイズの取得
Vector2 Animation::getDrawSize() const
{
	return mDrawSize;
}
