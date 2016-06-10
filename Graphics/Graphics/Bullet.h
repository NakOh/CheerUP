#pragma once
#ifndef  __BULLET_H__
#define __BULLET_H__

#include "Object.h"


class Bullet : public GameObject {
private:
	int myTime;
public:
	bool isDead = false;
	virtual void update(int delta);

	void checkColl();
	Bullet(Model* model, GameObjectManager* manager);
};


#endif // ! __BULLET_H__
