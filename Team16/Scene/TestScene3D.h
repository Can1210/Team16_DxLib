#pragma once
#include "BaseScene.h"
#include"../Actor/CharaManager/EnemySpawn.h"
#include"../Actor/CharaManager/CharactorManager.h"
#include"../Actor/Player/Player.h"
#include "../Actor/CharaManager/MapSpawn.h"
#include"../Device/Camera.h"

class TestScene3D : public BaseScene
{
public:
	TestScene3D(Input* input);
	~TestScene3D();

	virtual void initialize() override;
	virtual void update(float deltaTime) override;
	virtual void draw(Renderer* renderer, Renderer3D* renderer3D) override;
	virtual void shutdown() override;
	virtual bool isEnd() override;
	virtual std::string nextScene() override;
private:
	CharactorManager* charaManager;
	MapSpawn* mapSpawn;
	Camera* camera;
	Player* player;

};

