#pragma once
#include"../CharaManager/CharactorManager.h"
#include"../CharaManager/BaseObject.h"

class WallReflectionBullet : public BaseObject
{
public:
	WallReflectionBullet(Vector2 pos, CharactorManager* c, Type t, int angle);
	~WallReflectionBullet();
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
	enum WallType {
		R,
		L,
		None,
	};

	Vector2 RotationZ(float ang);//z²‰ñ“]‚Ì¬•ª‚¾‚¯

private:
	CharactorManager* charaManager;
	Type b_SetType;
	int angle;
	float PI = 3.141592653589793f;//‰~ü—¦
	float bulletAngle;			  //bullet‚ÌŠp“x

	WallType type;
};