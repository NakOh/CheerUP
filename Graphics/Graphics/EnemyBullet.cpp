
#include "EnemyBullet.h"

void EnemyBullet::update(int delta) {
	this->transform.Translation(getMoveMaping(0.001 * delta * vec.x, 0.001 * delta * vec.y));
	this->myTime += delta;
	if (4000 < myTime) {
		isDead = true;
	}
}


EnemyBullet::EnemyBullet(Model* model, GameObjectManager* manager) {
	init_GameObject(model, manager, 0);
	vec = Vec4(0, -0.003, 0, 0);
}

EnemyBullet::EnemyBullet(Vec4 vec, Model* model, GameObjectManager* manager) {
	init_GameObject(model, manager, 0);
	this->vec = vec;
}
