#pragma once
#ifndef _RENDERER3D_H_
#define _RENDERER3D_H_
#include "../Math/Vector3.h"
#include "../Math/Vector2.h"
#include "Loader/TextureLoad.h"


//3D•`‰æ
class Renderer3D
{
public:
	Renderer3D();
	~Renderer3D();

	void draw3DTexture(std::string textureName,
		Vector3 position,
		Vector2 drawPos,
		Vector2 textureSize,
		float scale,
		float angle,
		int alpha = 255,
		Vector2 centerPos = Vector2(0.5f, 0.5f),
		bool isTransparency = true);


};

#endif // !_RENDERER3D_H_