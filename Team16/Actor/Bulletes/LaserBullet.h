#pragma once
#include"../CharaManager/CharactorManager.h"
#include"../CharaManager/BaseObject.h"

class LaserBullet : public BaseObject
{
public:
	LaserBullet(Vector2 pos, CharactorManager* c, Type t, float angle);
	LaserBullet(Vector2 pos, CharactorManager* c, Type t, float angle,bool hitSound);
	~LaserBullet();
	//‰Šú‰»
	virtual void initialize()override;
	//XV
	virtual void update(float deltaTime)override;
	//•`‰æ
	virtual void draw(Renderer* renderer, Renderer3D* renderer3D)override;
	//“–‚½‚è‚½‚Ìˆ—
	virtual void hit(BaseObject& other) override;
private:

	//’e‚Ìƒ^ƒCƒv•ª‚¯
	void setBulletType();
	Vector2 RotationZ(float ang);//z²‰ñ“]‚Ì¬•ª‚¾‚¯

private:
	CharactorManager* charaManager;
	Type b_SetType;
	float PI = 3.141592653589793f;//‰~ü—¦
	float bulletAngle;			  //bullet‚ÌŠp“x

	bool hits;
};