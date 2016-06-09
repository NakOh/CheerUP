#ifndef _GAMEOBJECTMANAGER_H_
#define _GAMEOBJECTMANAGER_H_


#include <stdio.h>
#include "shader.hpp"
#include "Enemy.h"
#include "Bullet.h"
#include "Matrix.h"
#include "Light.h"
#include <math.h>
#include <stdlib.h>
#include "vector" 
#include "LinkedList.h"

class Manager {
private:
	LinkedList *list;
public:
	Manager();
	void Add(GameObject* obj);
	void Render();
	void Update();
	int getObjectSize();

};

#endif // !_GAMEOBJECTMANAGER_H_