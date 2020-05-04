#include "Renderer3D.h"



Renderer3D::Renderer3D()
{
}


Renderer3D::~Renderer3D()
{
}

void Renderer3D::draw3DTexture(std::string textureName, Vector3 position, Vector2 drawPos, Vector2 textureSize, float scale, float angle, int alpha, Vector2 centerPos, bool isTransparency)
{
	//指定した画像を切り取って新しい画像を作成（指定した画像は切り取られてはいない）
	int cutTexture = DerivationGraph(
		(int)drawPos.x, (int)drawPos.y,
		(int)textureSize.x, (int)textureSize.y, TextureLoad::getInstance().set(textureName));

	//ラジアンを度に変換
	float deg = angle * (DX_PI_F / 180.0f);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);  //ブレンドモードをαに設定
	DrawBillboard3D(VGet(position.x, position.y, position.z),
		centerPos.x,
		centerPos.y,
		scale,
		deg,
		cutTexture,
		isTransparency);
	DeleteGraph(cutTexture);  //作ったものを消去
}
