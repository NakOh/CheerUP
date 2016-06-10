#pragma once
#ifndef __Rock_H__
#define __Rock_H__

#include "Object.h"

class Rock : public GameObject{
private:
	int timer = 0;
	Vec4 randRot;
public:
	bool isDead = false;
	virtual void update(int delta);
	Rock(Model* model, GameObjectManager* manager);
};
#endif 
