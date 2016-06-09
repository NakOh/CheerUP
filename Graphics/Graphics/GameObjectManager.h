#ifndef _GAMEOBJECTMANAGER_H_
#define _GAMEOBJECTMANAGER_H_


#include <stdio.h>
#include "shader.hpp"
#include "Enemy.h"
#include "MyCharacter.h"
#include "Bullet.h"
#include "EnemyBullet.h"
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
	Map* map2;
	Map* map;

	ShaderID shader;
	Model* model;
	Model* mapModel;
	Model* sphereModel;
	
	EnemyVar enemyVar;
	
	void eBulletDestroy();
	void myBulletDestroy();

	void enemyDestroy();
	void enemyCreate(int delta);
	void enemyShoot(int delta);

public:
	LinkedList *eBullet;
	LinkedList *myBullet;
	LinkedList *enemys;

	Light* light;
	Camera* camera;
	MyCharacter* myChar;
	

	void addBullet();
	GameObjectManager();
	void render();
	void update(int delta);

	void enemyUpdate(int delta);
};

#endif // !_GAMEOBJECTMANAGER_H_