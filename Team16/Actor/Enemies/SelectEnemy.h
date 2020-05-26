#pragma once
#ifndef _SCLECTENEMY_H_
#define _SCLECTENEMY_H_

#include"../CharaManager/BaseObject.h"
#include"../CharaManager/CharactorManager.h"

//ステージセレクトの時の敵
class SelectEnemy :public BaseObject
{
public:
	SelectEnemy(Vector2 pos, CharactorManager *c,int num);
	~SelectEnemy();

	virtual void initialize() override;

	virtual void update(float deltaTime) override;

	virtual void draw(Renderer * renderer, Renderer3D* renderer3D) override;

	virtual void hit(BaseObject & other) override;

private:
	CharactorManager* m_pCharaManager;
	int mStageNum;
};


#endif // !_SCLECTENEMY_H_