#pragma once
#ifndef _GAMEMANAGER_H_
#define _GAMEMANAGER_H_
#include "../Support/Singleton.h"
#include "../Device/Renderer.h"
#include "../Device/Renderer3D.h"
#include "../Device/Input.h"

//ゲーム全体管理  シングルトン
class GameManager :public Singleton<GameManager>
{
protected:
	GameManager();
	virtual ~GameManager();
public:
	friend class Singleton<GameManager>;        //Singletonでのインスタンス作成は許可

	//初期化
	void initialize(Input* input);
	void sceneInitialize(Input* input);     //シーンの初期化

	//更新
	void update();
private:
	Renderer* m_pRenderer;        //レンダラー（シングルトンでもよかったけど頻繁に使うしコードが長くなるから引数に置くことにする）
	Renderer3D* m_pRenderer3D;    //3D描画
};

#endif // !_GAMEMANAGER_H_