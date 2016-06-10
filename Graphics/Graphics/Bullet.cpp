
#include "Bullet.h"

void Bullet::update(int delta) {
	this->transform.Translation(getMoveMaping(0, 0.005 * delta));
	this->myTime += delta;
	if (4000 < myTime) {
		isDead = true;
	}
}


Bullet::Bullet(Model* model, GameObjectManager* manager) {
	init_GameObject(model, manager, 0);
}
