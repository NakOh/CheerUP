
#include "Enemy.h"

void Enemy::update(int delta) {

}


Enemy::Enemy(Camera* camera, Light* light) {
	init_GameObject("models/flight.dat", camera, light, TAG_ENEMY);
}
