#include "Player.h"



Player::Player(Vector2 pos, CharactorManager *c)
{
	charaManager = c;
	b_mPosittion = pos;
}

Player::~Player()
{
	delete input;
	delete rend;
}

void Player::initialize()
{

	MoveFlag = FALSE;
	input = new Input;
	input->init();
	rend = new Renderer;
	b_mCircleSize = 16.0f;
	b_mType = Type::PLAYER;
	b_mHp = 100;
}

void Player::update(float deltaTime)
{

	b_mVelocity = Vector2(0, 0);
	input->update();



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

		if (input->isKeyDown(KEYCORD::X))
		{
			CShot(Vector2(b_mPosittion.x, b_mPosittion.y));
		}
		b_mPosittion += b_mVelocity;

	}
}

void Player::draw(Renderer * renderer, Renderer3D* renderer3D)
{

	if (b_mType == Type::PLAYER && !b_mEndFlag)
	{
		DrawCircle(b_mPosittion.x + 64 / 2, b_mPosittion.y + 16, b_mCircleSize, GetColor(0, 0, 255), FALSE);
		rend->draw2D("player", Vector2(b_mPosittion.x, b_mPosittion.y), Vector2(0, 0), Vector2(64, 64), Vector2(32, 32), Vector2(1.0f, 1.0f), b_mAngle, 255);
		rend->drawNumber("hpNumber", Vector2(150, 10), b_mHp, 0, Vector2(0, 0), Vector2(1, 1), 0.0f, 255);
	}
	else
	{
		DrawCircle(b_mPosittion.x + 64 / 2, b_mPosittion.y + 16, b_mCircleSize, GetColor(255, 0, 0), FALSE);
	}


	if (b_mEndFlag)
	{
		rend->drawText("Font", "GAMEOVER", Vector2(100, 450), Vector2(0, 0), Vector2(1, 1), 0.0f, 255);
	}
}

void Player::Shot(Vector2 pos)
{
	charaManager->add(new Bullet(pos, charaManager, b_mType));

}

void Player::CShot(Vector2 pos)
{
	charaManager->add(new ChangeBullet(pos, charaManager));
}


void Player::hit(BaseObject & other)
{
	if (other.getType() == Type::ENEMY_BULLET)
	{
		b_mHp -= 10;
		DrawCircle(b_mPosittion.x + 64 / 2, b_mPosittion.y + 16, b_mCircleSize, GetColor(255, 255, 0), TRUE);

	}
	if (other.getType() == Type::ENEMY)
	{
		b_mHp -= 1;
		DrawCircle(b_mPosittion.x + 64 / 2, b_mPosittion.y + 16, b_mCircleSize, GetColor(255, 255, 0), TRUE);
	}
	if (b_mHp <= 0)
	{
		b_mEndFlag = true;
	}

}

bool Player::getIsDeath() const
{
	return b_mIsDeath;
}

Type Player::getType() const
{
	return b_mType;
}

Vector2 Player::getPpstion() const
{
	return Vector2();
}

float Player::getCircleSize() const
{
	return b_mCircleSize;
}

Type Player::ChangeType()
{
	return b_mType;
}


