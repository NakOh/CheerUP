#ifndef _GAMEOBJECTMANAGER_H_
#define _GAMEOBJECTMANAGER_H_


#include <stdio.h>
#include "shader.hpp"
#include "Enemy.h"
#include "Bullet.h"
#include "Map.h"
#include "Matrix.h"
#include "Light.h"
#include <math.h>
#include <stdlib.h>
#include "vector" 
#include "LinkedList.h"

class EnemyVar {
public:
	int createTimer = 0;
	int createMaxTimer = 1000;
	float createRange_X = 8;
	EnemyVar() {}
};

class GameObjectManager {
private:
	LinkedList *eBullet;
	LinkedList *myBullet;
	LinkedList *enemys;

	Map* map2;
	Map* map;

	ShaderID shader;
	Model* model;
	Model* mapModel;
	Model* sphereModel;
	
	EnemyVar enemyVar;
	
	void enemyDestroy();
	void enemyCreate(int delta);

public:
	Light* light;
	Camera* camera;
	void addBullet();
	GameObjectManager();
	void render();
	void update(int delta);

	void enemyUpdate(int delta);
};

#endif // !_GAMEOBJECTMANAGER_H_