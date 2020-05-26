#include "DeathPoint.h"



DeathPoint::DeathPoint()
{
}


DeathPoint::~DeathPoint()
{
}

void DeathPoint::initialize()
{
	mUp    = 0.0f;
	mDown  = 0.0f;
	mLeft  = 0.0f;
	mRight = 0.0f;
}

float DeathPoint::getUp() const
{
	return mUp;
}

float DeathPoint::getDown() const
{
	return mDown;
}

float DeathPoint::getLeft() const
{
	return mLeft;
}

float DeathPoint::getRight() const
{
	return mRight;
}

float DeathPoint::getCenter() const
{
	return mCenter;
}

float DeathPoint::cameraVely() const
{
	return mVely;
}

void DeathPoint::setUp(float pos)
{
	mUp = pos;
}

void DeathPoint::setDown(float pos)
{
	mDown = pos;
}

void DeathPoint::setLeft(float pos)
{
	mLeft = pos;
}

void DeathPoint::setRight(float pos)
{
	mRight = pos;
}

void DeathPoint::setCenter(float pos)
{
	mCenter = pos;
}

void DeathPoint::cameraVely(float pos)
{
	mVely = pos;
}



