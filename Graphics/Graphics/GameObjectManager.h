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

class GameObjectManager;

class EnemyVar {
public:
	int createTimer = 0;
	int createMaxTimer = 1000;
	float createRange_X = 8;
	EnemyVar() {}
};

class ShakingVar {
private:
	GameObjectManager* manager;
	bool isShaking = false;
	Vec4 velocity, pos;
	int timer = 0;
	int maxTimer = 500;
public:
	ShakingVar() {}
	ShakingVar(GameObjectManager* manager) {
		this->manager = manager;
		velocity = Vec4();
		pos = Vec4();
	}
	void update(int delta);
	void startShaking() {
		isShaking = true;
	}
};


class ModelBox {
public:
	Model* flight;
	Model* map;
	Model* sphere;
	Model* helly;
	ModelBox();
};


class GameObjectManager {
private:
	Map* map2;
	Map* map;

	ShaderID shader;

	ShakingVar shakingVar;
	EnemyVar enemyVar;
	
	void eBulletDestroy();
	void myBulletDestroy();

	void enemyDestroy();
	void enemyCreate(int delta);

public:
	LinkedList *eBullet;
	LinkedList *myBullet;
	LinkedList *enemys;

	Light* light;
	Camera* camera;
	MyCharacter* myChar;
	
	ModelBox models;

	void addBullet();
	GameObjectManager();
	void render();
	void update(int delta);

	void enemyUpdate(int delta);

	void shakingCamera();
};

#endif // !_GAMEOBJECTMANAGER_H_