#include "Player.h"
#include"../../Device/Sound.h"


Player::Player(Vector2 pos, CharactorManager *c) :mTimer(new Timer())
{
	charaManager = c;
	b_mPosittion = pos;
	input = new Input;
}

Player::~Player()
{
	delete input;
	delete mTimer;
}

bool Player::SubNull()//サブがいるか
{
	for (auto object : charaManager->getUseList())
	{
		if (object->getType() == Type::SUB_PLAYER)
		{
			object->setIsDeath(true);
		}
	}
	return false;
}

void Player::initialize()
{

	
	input->init();
	b_mCircleSize = 16.0f;
	b_mType = Type::PLAYER;
	b_mHp = 300;
	b_mSpeed = 40.0f;
	mTimer->initialize();
	shotcnt = 0;
	subShotCnt = 7;
	r = 0;
	b = 255;
}

void Player::update(float deltaTime)
{

	b_mVelocity = Vector2(0, 0);
	input->update();
	mTimer->update(deltaTime);

	//無敵時間
	if (DamgeFlag&&mTimer->timerSet(2))
	{
		DamgeFlag = FALSE;
	}
	if (input->isKeyState(KEYCORD::SPACE))
	{
		subShotCnt++;
		if (subShotCnt > 7)
		{
			Shot(Vector2(b_mPosittion.x, b_mPosittion.y));
			subShotCnt = 0;
		}
		
		b_mSpeed = 20.0f;
	}
	else
	{
		b_mSpeed = 40.0f;
	}
	

	if (b_mType == Type::PLAYER && !b_mEndFlag)
	{

		if (input->isKeyState(KEYCORD::ARROW_UP))
		{
			b_mVelocity.y -= 6;
		}
		if (input->isKeyState(KEYCORD::ARROW_DOWN))
		{
			b_mVelocity.y += 6;
		}
		if (input->isKeyState(KEYCORD::ARROW_RIGHT))
		{
			b_mVelocity.x += 6;
		}
		if (input->isKeyState(KEYCORD::ARROW_LEFT))
		{
			b_mVelocity.x -= 6;
		}
		if (input->isKeyDown(KEYCORD::SPACE))
		{
			Shot(Vector2(b_mPosittion.x, b_mPosittion.y));
		}

		if (b_mHp <= 0)
		{
			Sound::getInstance().playSE("burst02");
			b_mEndFlag = true;
		}
		
		b_mPosittion += b_mVelocity*deltaTime*b_mSpeed;

	}
}

void Player::draw(Renderer * renderer, Renderer3D* renderer3D)
{

	if (b_mType == Type::PLAYER && !b_mEndFlag)
	{
		if (DamgeFlag)
		{
			b_mArpha = 155;
		}
		else
		{
			b_mArpha = 255;
		}
		
		DrawBox(0,0,shotcnt,100, GetColor(r, 0, b), TRUE);
		if (shotcnt == 100)
		{
			r = 255;
			b = 0;
		}
		DrawCircle(b_mPosittion.x + 64 / 2, b_mPosittion.y + 16, b_mCircleSize, GetColor(0, 0, 255), FALSE);
		renderer->draw2D("player", Vector2(b_mPosittion.x, b_mPosittion.y), Vector2(0, 0), Vector2(64, 64), Vector2(32, 32), Vector2(1.0f, 1.0f), b_mAngle, b_mArpha);
		renderer->drawNumber("hpNumber", Vector2(150, 10), b_mHp, 0, Vector2(0, 0), Vector2(1, 1), 0.0f, 255);
	}
	if (b_mType == Type::SUB_PLAYER)
	{
		renderer->draw2D("player", Vector2(b_mPosittion.x, b_mPosittion.y), Vector2(0, 0), Vector2(64, 64), Vector2(32, 32), Vector2(1.0f, 1.0f), b_mAngle, b_mArpha);
	}

	if (b_mEndFlag)
	{
		renderer->drawText("Font", "GAMEOVER", Vector2(100, 450), Vector2(0, 0), Vector2(1, 1), 0.0f, 255);
	}


}

void Player::Shot(Vector2 pos)
{
	charaManager->add(new Bullet(pos, charaManager, b_mType,0.0f));
	Sound::getInstance().playSE("shot");
}

void Player::TShot(Vector2 pos,float deltaTime)
{
	//charaManager->add(new TrakingBullet(pos, charaManager, b_mType, 70.0f));
	charaManager->add(new TrakingBullet(pos, charaManager, b_mType, 90.0f));
	//charaManager->add(new TrakingBullet(pos, charaManager, b_mType, 110.0f));
}

void Player::hit(BaseObject & other)
{
	if (!DamgeFlag)
	{
		if (other.getType() == Type::ENEMY_BULLET)
		{
			Sound::getInstance().playSE("hit");
			b_mHp -= 1;
			DrawCircle(b_mPosittion.x + 64 / 2, b_mPosittion.y + 16, b_mCircleSize, GetColor(255, 255, 0), TRUE);
			mTimer->initialize();
			DamgeFlag = TRUE;
		
		}

		if (other.getType() == Type::ENEMY)
		{
			Sound::getInstance().playSE("hit");
			b_mHp -= 1;
			DrawCircle(b_mPosittion.x + 64 / 2, b_mPosittion.y + 16, b_mCircleSize, GetColor(255, 255, 0), TRUE);
			mTimer->initialize();
			DamgeFlag = TRUE;
			
		}
	}
	if (other.getType() == ITEM)
	{
		SubNull();
	}


}

