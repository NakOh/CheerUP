
#include "Enemy.h"
#include <ctime>

void Enemy::update(int delta) {
	transform.Translation(0, -0.001 * delta, -0.001 * delta * 0.4);
	timer += delta;
	if (20000 < timer) {
		isDead = true;
	}	
}



Enemy::Enemy(Model* model, GameObjectManager* manager) {
	init_GameObject(model, manager, TAG_ENEMY);
	float pos = 2.5f - ((float)(rand() % 100))/ 20; 
	bullet_createMaxTimer = rand() % 1000 + 100; //여기서 바꾸면 총알 주기가 달라진다.
	transform.SetPosition(pos, 5, 6);
	transform.Rotation(-PI * 0.4f, -PI * 0.5f, 0);
}

