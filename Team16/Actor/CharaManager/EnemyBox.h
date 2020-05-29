#pragma once
#ifndef _ENEMY_BOX_H_
#define _ENEMY_BOX_H_
#include "BaseObject.h"
#include "CharactorManager.h"
#include "../../Device/Camera.h"
//“G¶¬” 
class EnemyBox : public BaseObject
{
public:
	EnemyBox(CharactorManager& charactorMnager, unsigned int enemyNumber,Vector2 position);
	~EnemyBox();

	// BaseObject ‚ğ‰î‚µ‚ÄŒp³‚³‚ê‚Ü‚µ‚½
	virtual void initialize() override;

	virtual void update(float deltaTime) override;

	virtual void draw(Renderer * renderer, Renderer3D* renderer3D) override;

	virtual void hit(BaseObject & other) override;
	//“G‚Ì¶¬
	void spawn();
	//ƒJƒƒ‰‚Æ‚Ì‹——£‚ğ‘ª‚é
	void checkDistance();

	void setPosition(Vector2 position);

private:
	CharactorManager* m_pCharactorManager;
	unsigned int mEnemyNum;   //“G‚Ì”Ô†
};
#endif // !_ENEMY_BOX_H_
