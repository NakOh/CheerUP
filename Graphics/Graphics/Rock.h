#pragma once
#ifndef __Rock_H__
#define __Rock_H__

#include "Object.h"

class Rock : public GameObject{

public:

	virtual void update(int delta);
	Rock(Model* model, GameObjectManager* manager);
};
#endif 
