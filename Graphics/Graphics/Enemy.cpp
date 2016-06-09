
#include "Enemy.h"

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
	transform.SetPosition(pos, 5, 6);
	transform.Rotation(-PI * 0.4f, -PI * 0.5f, 0);
}
