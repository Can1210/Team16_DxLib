#pragma once
#include"DxLib.h"
#include "../../Math/Vector2.h"
#include"../CharaManager/CharactorManager.h"
#include"../../Device/Renderer.h"
#include"../CharaManager/BaseObject.h"
#include"../../Support/CWindow.h"
#include"../../GameBase/WindowInfo.h"



class BomBullet :public BaseObject
{
public:
	BomBullet(Vector2 pos, CharactorManager* c, Type t,float angle);
	~BomBullet();
	//’e‚Ìƒ^ƒCƒv•ª‚¯
	void setBulletType();
	//‰Šú‰»
	virtual void initialize()override;
	//XV
	virtual void update(float deltaTime)override;
	//•`‰æ
	virtual void draw(Renderer* renderer, Renderer3D* renderer3D)override;
	//“–‚½‚è‚½‚Ìˆ—
	virtual void hit(BaseObject& other) override;

private:

	float angle;
	bool Death;
	CharactorManager* charaManager;
	Type b_SetType;
	Timer *mTimer;
	int BomFlag;


	float PI = 3.141592653589793f;//‰~ü—¦
	float bulletAngle;			  //bullet‚ÌŠp“x
	Vector2 RotationZ(float ang);//z²‰ñ“]‚Ì¬•ª‚¾‚¯
};
