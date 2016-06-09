#pragma once
#ifndef  __ENEMY_H__
#define __ENEMY_H__

#include "Object.h"

class Enemy : public GameObject {
public:
	virtual void update(int delta);
	Enemy(Camera* camera, Light* light);
};

class EnemyManager {
	
};


#endif // ! __ENEMY_H__
