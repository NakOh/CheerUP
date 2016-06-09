
#include "Enemy.h"

void Enemy::update(float delta) {

}


Enemy::Enemy(Camera* camera, Light* light) {
	init_GameObject("models/flight.dat", camera, light, 0);
}
