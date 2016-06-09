#pragma once
#ifndef  __BULLET_H__
#define __BULLET_H__

#include "Object.h"


class Bullet : public GameObject {
public:
	virtual void update(float delta);
	Bullet(Camera* camera, Light* light);
};


#endif // ! __BULLET_H__
