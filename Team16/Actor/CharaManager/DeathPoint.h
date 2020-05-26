#pragma once
#ifndef _DEATHPOINT_H_
#define _DEATHPOINT_H_
#include "../../Support/Singleton.h"
#include "../../Math/Vector2.h"
//���S�G���A
class DeathPoint :public Singleton<DeathPoint>
{
protected:
	DeathPoint();
	virtual~DeathPoint();
public:
	friend class Singleton<DeathPoint>;   //Singleton�ł̃C���X�^���X�쐬�͋���
	//������
	void initialize();
	//���ꂼ��̈ʒu�����炤
	float getUp()    const;
	float getDown()  const;
	float getLeft()  const;
	float getRight() const;
	float getCenter() const;
	float cameraVely()const;

	void setUp   (float pos);
	void setDown (float pos);
	void setLeft (float pos);
	void setRight(float pos);
	void setCenter(float pos);
	void cameraVely(float pos);


private:
	float mUp;
	float mDown;
	float mLeft;
	float mRight;
	float mCenter;
	float mVely;


};


#endif // !_DEATHPOINT_H_