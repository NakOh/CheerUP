
#include "EnemyBullet.h"

void EnemyBullet::update(int delta) {
	this->transform.Translation(0, -0.003f * delta, -0.003f * delta * 0.3f);
	this->myTime += delta;
	if (4000 < myTime) {
		isDead = true;
	}
}


EnemyBullet::EnemyBullet(Model* model, GameObjectManager* manager) {
	init_GameObject(model, manager, 0);
}
