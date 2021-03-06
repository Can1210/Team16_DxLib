#pragma once

#ifndef _CHARACTORMANAGER_H_
#define _CHARACTORMANAGER_H_
#include <vector>
#include "BaseObject.h"
#include"../../Support/CWindow.h"
//オブジェクトの管理
class CharactorManager
{
public:
	CharactorManager();
	~CharactorManager();

	//プレイヤーを検索
	Vector2 searchPlayer();

	//リストのクリア
	void clear();
	//リストへの追加
	void add(BaseObject* addObj);
	//更新
	void update(float deltaTime);

#pragma region update分割
	void addList_update();
	void objectsManager_update(float deltaTime);
	void removeList_update();
#pragma endregion
	//描画
	void draw(Renderer* renderer, Renderer3D* renderer3D);
	//現在使われているリストの取得
	std::vector<BaseObject*> getUseList();
	//プレイヤーの位置を取得する
	Vector2 getPlayerPosition()const;
	//プレイヤーのバレットのダメージを渡す。後でまた変えるかも
	float getPlayerBulletDamage();

	bool getIsBossEed();
	bool getIsPlayerEed();


	//プレイヤーに必要なUI関係ー間に合わせで申し訳ございません
	void setSub1(std::string itemName);
	void setSub2(std::string itemName);
	std::string getSub1();
	std::string getSub2();

	void setPlayerHp(float hp);
	float getHp();

private:
	std::vector<BaseObject*> mObjectsList;        //オブジェクトのリスト
	std::vector<BaseObject*> mAddObjectsList;     //追加するオブジェクト

	bool playerEnd;
	bool bossEnd;

	std::string mSub1 = "none";
	std::string mSub2 = "none";
	float mPlayerHp = 3;

};

#endif // !_CHARACTORMANAGER_H_