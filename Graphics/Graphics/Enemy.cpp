
#include "Enemy.h"

void Enemy::update(int delta) {

}


Enemy::Enemy(Model* model, GameObjectManager* manager) {
	init_GameObject(model, manager, TAG_ENEMY);
}
