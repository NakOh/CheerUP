
#include "Enemy.h"

void Enemy::update(int delta) {

}


Enemy::Enemy(Model* model, Camera* camera, Light* light) {
	init_GameObject(model, camera, light, TAG_ENEMY);
}
