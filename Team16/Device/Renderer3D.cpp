#include "Renderer3D.h"



Renderer3D::Renderer3D()
{
}


Renderer3D::~Renderer3D()
{
}

void Renderer3D::draw3DTexture(std::string textureName, Vector3 position, Vector2 drawPos, Vector2 textureSize, float scale, float angle, int alpha, Vector2 centerPos, bool isTransparency)
{
	//�w�肵���摜��؂����ĐV�����摜���쐬�i�w�肵���摜�͐؂����Ă͂��Ȃ��j
	int cutTexture = DerivationGraph(
		(int)drawPos.x, (int)drawPos.y,
		(int)textureSize.x, (int)textureSize.y, TextureLoad::getInstance().set(textureName));

	//���W�A����x�ɕϊ�
	float deg = angle * (DX_PI_F / 180.0f);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);  //�u�����h���[�h�����ɐݒ�
	DrawBillboard3D(VGet(position.x, position.y, position.z),
		centerPos.x,
		centerPos.y,
		scale,
		deg,
		cutTexture,
		isTransparency);
	DeleteGraph(cutTexture);  //��������̂�����
}
