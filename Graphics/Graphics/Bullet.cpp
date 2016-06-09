
#include "Bullet.h"

void Bullet::update(float delta) {

}


Bullet::Bullet(Camera* camera, Light* light) {
	init_GameObject("models/flight.dat", camera, light, 0);
}
