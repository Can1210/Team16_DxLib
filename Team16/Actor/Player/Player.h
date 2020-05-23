#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "../../Device/Input.h"
#include"../CharaManager/BaseObject.h"
#include"../CharaManager/CharactorManager.h"
#include "../Item/Item.h"

class Player :public BaseObject
{
	//一番最初の操作キャラ、ボム使用時にこれに戻る
public:
	Player(Vector2 pos, CharactorManager *c);
	~Player();

	// BaseObject を介して継承されました
	virtual void initialize() override;

	virtual void update(float deltaTime) override;

	virtual void draw(Renderer * renderer, Renderer3D* renderer3D) override;

	virtual void hit(BaseObject & other) override;
	//移動
	void move();
	//射撃
	void Shot(Vector2 pos);
	
#pragma region 弾関係
	void bom1();
	void bom2();
	//サブの射撃
	void SubShots(unsigned int num);
	//ボムエネミーの射撃
	void bomShot();
	void circle();
	void laser();
	void platoon();
	void homing();
	void threeWay();
	void ufo();

#pragma endregion

private:
	bool DamgeFlag;
	Input* input;
	CharactorManager* charaManager;
	Timer *mTimer;
	int shotcnt;
	int subShotCnt;//合体射撃のレート
	int r, b;
	//サブウェポン関係
	std::vector<BulletType> mSubVec;
	std::vector<std::string> mSubName;
	std::vector<Vector2> mSubPos;
};


#endif // !_PLAYER_H_