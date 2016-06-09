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

class GameObjectManager {
private:
	LinkedList *eBullet;
	LinkedList *myBullet;
	LinkedList *enemys;

	ShaderID shader;
	Model* model;

public:
	Light* light;
	Camera* camera;
	void addBullet();
	GameObjectManager();
	void render();
	void update(int delta);
};

#endif // !_GAMEOBJECTMANAGER_H_