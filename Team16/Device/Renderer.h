#pragma once
#ifndef _RENDERER_H_
#define _RENDERER_H_
#include "Loader/TextureLoad.h"
#include "../Math/Vector2.h"

//�`��@�\lib�Ȃ̂�lib�̋@�\�����b�v���邾���ɂ���(2D)
class Renderer
{
public:
	Renderer();
	~Renderer();
	//2D�`��ꖇ�G�p
	/*textureName :�e�N�X�`���̖��O�@position :���W�@drawSize : �摜���̂ǂ�����`�悷�邩�̍�����W�@textureSize :�e�N�X�`���̃T�C�Y�@isTransparency:�����x��L���ɂ��邩�ǂ���(Def ture)�@isTurn:���]���邩�ǂ���(Def false)*/
	void draw2D(std::string textureName,
		Vector2 position,
		Vector2 drawPos,
		Vector2 textureSize,
		bool isTransparency = true,
		bool isTurn = false);
	//2D�`��I�[�o�[���[�h�A�ԗp
	/*textureName :�e�N�X�`���̖��O�@position :���W�@drawSize : �摜���̂ǂ�����`�悷�邩�̍�����W�@textureSize :�ǂ��܂ŕ`�悷�邩�E�����W�@angleCenter�F��]���S�ʒu�@scale�F�g��k���iDef 1.0�����{�j�@angle�F�p�x�i�x���@�@Def 0�j�@alpha�F�����l�iDef 255 min 0,max 255�j�@isTransparency:�����x��L���ɂ��邩�ǂ���(Def ture)�@isTurn:���]���邩�ǂ���(Def false)*/
	void draw2D(std::string textureName,
		Vector2 position,
		Vector2 drawPos,
		Vector2 textureSize,
		Vector2 angleCenter,
		Vector2 scale = Vector2(1.0, 1.0),
		float angle = 0,
		int alpha = 255,
		bool isTransparency = true,
		bool isTurn = false);

	//angleCenter�͌��ߑł��@�傫���͂܂�����Ă��Ȃ�
	/*textureName :�e�N�X�`���̖��O�@position :���W�@number�F�����@digits�F���������@angleCenter�F��]���S�ʒu�@scale�F�g��k���iDef 1.0�����{�j�@angle�F�p�x�i�x���@�@Def 0�j�@alpha�F�����l�iDef 255 min 0,max 255�j*/
	void drawNumber(std::string textureName, Vector2 position, double number, unsigned int digits,
		Vector2 angleCenter = Vector2(0.0, 0.0), Vector2 scale = Vector2(1.0, 1.0), float angle = 0, int alpha = 255);
	
	//�X�R�A�\���p
	/*textureName :�e�N�X�`���̖��O�@position :���W�@number�F�����@�@angleCenter�F��]���S�ʒu�@scale�F�g��k���iDef 1.0�����{�j�@angle�F�p�x�i�x���@�@Def 0�j�@alpha�F�����l�iDef 255 min 0,max 255�j*/
	void drawScoreNumber(std::string textureName, Vector2 position, int number ,
		Vector2 angleCenter = Vector2(0.0, 0.0), Vector2 scale = Vector2(1.0, 1.0), float angle = 0, int alpha = 255);


	//�����`��@�傫���͂܂�����Ă��Ȃ����s�i�D�ł���@�N�����Ԋu�̕���������Ăق���
	/*textureName :�e�N�X�`���̖��O�@writeString�F���e�@position :���W�@angleCenter�F��]���S�ʒu�@scale�F�g��k���iDef 1.0�����{�j�@angle�F�p�x�i�x���@�@Def 0�j�@alpha�F�����l�iDef 255 min 0,max 255�j*/
	void drawText(std::string textureName, std::string writeString, Vector2 position,
		Vector2 angleCenter = Vector2(0, 0), Vector2 scale = Vector2(1.0, 1.0), float angle = 0, int alpha = 255);
	
	//�O�Օ`��
	void lineDraw(std::string textureName,
		Vector2 position,
		Vector2 drawPos,
		Vector2 textureSize,
		Vector2 angleCenter,
		Vector2 velocity,
		int blurCount,
		Vector2 scale = Vector2(1.0, 1.0),
		float angle = 0,
		bool isTransparency = true,
		bool isTurn = false);


private:
	const float mNumTexture_Width  = 24.0f;     //�����摜�̉���
	const float mNumTexture_Height = 40.0f;    //�����摜�̏c��

	//�Œ�l
	const float mFontTexture_Big_Width     = 64.0f;
	const float mFontTexture_Big_Height    = 64.0f;
	const float mFontTexture_Small_Width   = 64.0f;
	const float mFontTexture_Small_Height  = 64.0f;
	const float mFontTexture_Symbol_Width  = 64.0f;
	const float mFontTexture_Symbol_Height = 64.0f;

};

#endif // !_RENDERER_H_

