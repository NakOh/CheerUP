#pragma once
#ifndef  __MAP_H__
#define __MAP_H__

#include "Object.h"

class Map : public GameObject {
private:
	int timer = 0;

public:
	virtual void update(int delta);
	Map(Model* model, GameObjectManager* manager);
};

#endif // ! __MAP_H__