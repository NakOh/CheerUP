#pragma once
#ifndef  __ENEMY_H__
#define __ENEMY_H__

#include "Object.h"

class Enemy : public GameObject {
public:
	virtual void update(float delta);
	Enemy(Camera* camera, Light* light);
};


#endif // ! __ENEMY_H__
