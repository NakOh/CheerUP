
#include "Bullet.h"

void Bullet::update(int delta) {
	this->transform.Translation(0.001f * delta, 0, 0);
	this->myTime += delta;
	printf("%d\n", myTime);
}


Bullet::Bullet(Model* model, GameObjectManager* manager) {
	init_GameObject(model, manager, 0);
}
