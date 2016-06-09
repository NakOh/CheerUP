#pragma once
#ifndef  __BULLET_H__
#define __BULLET_H__

#include "Object.h"


class Bullet : public GameObject {
private:
	int myTime;
public:
	virtual void update(int delta);
	Bullet(Model* model, GameObjectManager* manager);
};


#endif // ! __BULLET_H__
