#include "CharactorManager.h"


//コンストラクタ
CharactorManager::CharactorManager()
{
}

//デスストラクタ
CharactorManager::~CharactorManager()
{
	//追加するオブジェクトが残っていたら、メモリを解放する
	for (auto obj : mAddObjectsList)
	{
		if (obj != nullptr)
			delete obj;
	}
	mAddObjectsList.clear();      //空にする

	//オブジェクトがnullになったらそのメモリを解放
	for (auto object : mObjectsList)
	{
		if (object != nullptr)
			delete object;
	}
	mObjectsList.clear();

}

//リストのクリア
void CharactorManager::clear()
{
	//リストの中を空にする
	mObjectsList.clear();
	mAddObjectsList.clear();
}
//リストへの追加
void CharactorManager::add(BaseObject * addObj)
{
	mAddObjectsList.emplace_back(addObj);
}
//更新
void CharactorManager::update(float deltaTime)
{
	addList_update();
	objectsManager_update(deltaTime);
	removeList_update();
}
#pragma region update分割

//追加リストの更新処理
void CharactorManager::addList_update()
{
	for (auto addObj : mAddObjectsList)
	{
		mObjectsList.emplace_back(addObj);
		addObj->initialize();             //初期化
	}
	mAddObjectsList.clear();              //空にする
}
//オブジェクトリストの管理更新
void CharactorManager::objectsManager_update(float deltaTime)
{
	for (auto object1 : mObjectsList)
	{
		//オブジェクト1がnullか死んでいたらスキップ
		if (object1 == nullptr || object1->getIsDeath()) continue;
		object1->update(deltaTime);   //オブジェクト1を更新
		for (auto object2 : mObjectsList)
		{
			//オブジェクト2が「null,死んでいる,オブジェクト1,2」が同じならスキップ
			if (object2 == nullptr ||
				object2->getIsDeath() ||
				object1 == object2)
				continue;
			//円同士の当たり判定を調べて当たっていたら両方のhitを呼ぶ
			if (object1->circle_circle_Collision(*object2))
			{
				object1->hit(*object2);
				object2->hit(*object1);

			}
		}
	}

}
//オブジェクトの削除更新
void CharactorManager::removeList_update()
{
	auto itr = mObjectsList.begin();
	while (itr != mObjectsList.end())
	{
		//オブジェクトがnullか死んでいたら削除
		if (*itr == nullptr || (*itr)->getIsDeath())
		
			itr = mObjectsList.erase(itr);
		else
			itr++;        //次へ
	}
}
#pragma endregion
//描画
void CharactorManager::draw(Renderer * renderer, Renderer3D* renderer3D)
{
	for (auto object : mObjectsList)
	{
		if (object == nullptr) continue;  //オブジェクトがnullならスキップ
		//オブジェクトが死んでなければ描画、死んでたらスキップ
		if (!object->getIsDeath())
			object->draw(renderer, renderer3D);
		else
			continue;
	}
}
//現在使われているオブジェクトのリスト取得
std::vector<BaseObject*> CharactorManager::getUseList()
{
	return mObjectsList;
}
//プレイヤーの位置を取得する
Vector2 CharactorManager::getPlayerPosition() const
{
	for (auto object : mObjectsList)
	{
		if (!object->getType == Type::PLAYER) continue;    //プレイヤーでなければスキップ
		return object->getPpstion();
	}
	//プレイヤーがいなければ0を返す
	return Vector2(0,0);
}
