#pragma once
#ifndef  __ENEMY_H__
#define __ENEMY_H__

#include "Object.h"

class Enemy : public GameObject {
private:
	int timer = 0;
	int deadTime = 20000;

	float _gradient;

	void initType(int type);

	void update_shoot(int delta);

	Vec4 frontVec;

	void addBullet(Vec4 vec);

public:
	int type;
	virtual void update(int delta);
	Enemy(Model* model, GameObjectManager* manager);
	bool isDead = false;
	int bullet_createTimer = 0;
	int bullet_createMaxTimer;
};

#endif // ! __ENEMY_H__
