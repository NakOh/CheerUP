
#include "Bullet.h"

void Bullet::update(float delta) {
	this->transform.Translation(0.001f * delta, 0, 0);
	this->myTime += delta;
	printf("%f", myTime);
}


Bullet::Bullet(Camera* camera, Light* light) {
	init_GameObject("models/flight.dat", camera, light, 0);
}
