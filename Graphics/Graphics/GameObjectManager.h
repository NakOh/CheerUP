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

class Manager {
private:
public:
	std::vector<GameObject> pool;
	Manager();
	void Add(GameObject* obj);
	void Add(const char* path, bool objFile);
	void Render();
	void Update();

};

#endif // !_GAMEOBJECTMANAGER_H_