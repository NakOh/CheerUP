#pragma once
#ifndef  __ENEMY_H__
#define __ENEMY_H__

#include "Object.h"

class Enemy : public GameObject {
private:
	int timer = 0;

public:
	virtual void update(int delta);
	Enemy(Model* model, GameObjectManager* manager);
	bool isDead = false;
	int bullet_createTimer = 0;
	int bullet_createMaxTimer;
};

#endif // ! __ENEMY_H__
