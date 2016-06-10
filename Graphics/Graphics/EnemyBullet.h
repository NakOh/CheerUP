#pragma once
#ifndef  __ENEMY_BULLET_H__
#define __ENEMY_BULLET_H__

#include "Object.h"


class EnemyBullet : public GameObject {
private:
	int myTime;
	Vec4 vec;
public:
	bool isDead = false;
	virtual void update(int delta);
	EnemyBullet(Model* model, GameObjectManager* manager);
	EnemyBullet(Vec4 vec, Model* model, GameObjectManager* manager);
};


#endif // ! __ENEMY_BULLET_H__
#pragma once
