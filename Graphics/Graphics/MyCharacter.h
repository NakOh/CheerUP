#pragma once
#ifndef  __MYCHARACTER_H__
#define __MYCHARACTER_H__

#include "Object.h"

class MyCharacter : public GameObject {
private:
	int skill_Timer = 0;

public:
	virtual void update(int delta);
	MyCharacter(Model* model, GameObjectManager* manager);
	bool isDead = false;
};

#endif // ! __ENEMY_H__
