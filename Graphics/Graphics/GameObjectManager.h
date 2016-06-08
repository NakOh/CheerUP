#ifndef _GAMEOBJECTMANAGER_H_
#define _GAMEOBJECTMANAGER_H_


#include <stdio.h>
#include "shader.hpp"
#include "Object.h"
#include "Matrix.h"
#include "Light.h"
#include <math.h>
#include <stdlib.h>
#include "vector" 
#include "LinkedList.h"

class Manager {
private:
	LinkedList<GameObject> *list;
public:
	Manager();
	void Add(GameObject* obj);
	void Render();
	void Update();
	int getObjectSize();

};

#endif // !_GAMEOBJECTMANAGER_H_