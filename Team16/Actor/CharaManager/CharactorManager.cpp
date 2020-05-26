#include "CharactorManager.h"


//コンストラクタ
CharactorManager::CharactorManager()
{
}

//デスストラクタ
CharactorManager::~CharactorManager()
{
	clear();
}
//プレイヤーの位置を獲得
Vector2 CharactorManager::searchPlayer()
{
	for (auto object : mObjectsList)
	{
		if (object->getType() == Type::PLAYER)
		{
			return object->getPpstion();
		}
		//test
	}
	return Vector2(0, 0);
}

//リストのクリア
void CharactorManager::clear()
{
	//追加するオブジェクトが残っていたら、メモリを解放する
	for (auto obj : mAddObjectsList)
	{
		if (obj != nullptr)
			delete obj;
	}
	mAddObjectsList.clear();      //空にする

	//オブジェクトがnullptrではなかったらそのメモリを解放
	for (auto object : mObjectsList)
	{
		if (object != nullptr)
			delete object;
	}
	mObjectsList.clear();
	playerEnd = false;
	bossEnd = false;
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
		object1->outArea();           //苦し紛れの処理
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
		//nullptrの場合
		if ((*itr) == nullptr)
		{
			itr = mObjectsList.erase(itr);
		}
		else if ((*itr)->getIsDeath())  //オブジェクトがnullか死んでいたら削除
		{
			//ボスかプレイヤーなら
			if ((*itr)->getType() == Type::BOSS)
				bossEnd = true;
			if ((*itr)->getType() == Type::PLAYER)
 				playerEnd = true;

			BaseObject* deleteObj = (*itr);  //消す予定の物を入れる：更新されてしまう
			itr = mObjectsList.erase(itr);   //vecor内から削除
			delete deleteObj;                //解放
		}
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
		if (!object->getType() == Type::PLAYER) continue;    //プレイヤーでなければスキップ
		return object->getPpstion();
	}
	//プレイヤーがいなければ0を返す
	return Vector2(0,0);
}

float CharactorManager::getPlayerBulletDamage()
{
	for (auto object : mObjectsList)
	{
		if (object->getType() != Type::PLAYER_BULLET) continue;    //プレイヤーでなければスキップ
		return object->getBulletDamage();
	}
	return 0.0f;
}
//ボスが死んだかどうか
bool CharactorManager::getIsBossEed()
{
	return bossEnd;
}
//プレイヤーが死んだかどうか
bool CharactorManager::getIsPlayerEed()
{
	return playerEnd;
}
