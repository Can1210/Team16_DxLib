#include "SelectEnemy.h"
#include "../../Scene/Title.h"


SelectEnemy::SelectEnemy(Vector2 pos, CharactorManager * c,int num)
{
	m_pCharaManager = c;
	b_mPosittion = pos;
	mStageNum = num;
}

SelectEnemy::~SelectEnemy()
{
}

void SelectEnemy::initialize()
{
	b_mHp = 3;
	b_mCircleSize = 16.0f;
	b_mType = Type::ENEMY;
	b_mAngle = 180.0f;
	b_mSpeed = 60.0f;
	b_mArpha = 255;
}

void SelectEnemy::update(float deltaTime)
{
	b_mVelocity = Vector2(0, 0);
	if (b_mHp <= 0)
	{
		Title::choiceScene(mStageNum);
		b_mIsDeath = true;
	}
	b_mVelocity.y -= 1.655f;
	b_mPosittion -= b_mVelocity * b_mSpeed * deltaTime;
}

void SelectEnemy::draw(Renderer * renderer, Renderer3D * renderer3D)
{
	renderer3D->draw3DTexture("enemy", Vector3(b_mPosittion.x, b_mPosittion.y, 0.0f), Vector2(0.0f, 0.0f), Vector2(64.0f, 64.0f), 96.0f, b_mAngle);
}

void SelectEnemy::hit(BaseObject & other)
{
	if (other.getType() == Type::PLAYER_BULLET&&b_mType == Type::ENEMY)
	{
		b_mHp -= m_pCharaManager->getPlayerBulletDamage();
	}
}
