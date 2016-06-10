#pragma once
#ifndef  __MYCHARACTER_H__
#define __MYCHARACTER_H__

#include "Object.h"

class Input {
public:
	bool left, right, up, down;
	Input();
};

class MyCharacter : public GameObject {
private:
	int skill_Timer = 0;

	void update_velocity(int delta);

public:
	Input input;
	Vec4 velocity;

	virtual void update(int delta);
	MyCharacter(Model* model, GameObjectManager* manager);
	bool isDead = false;
	void checkColl();
};

#endif // ! __ENEMY_H__
