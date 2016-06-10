
#include "Bullet.h"
#include "GameObjectManager.h"

void Bullet::update(int delta) {
	this->transform.Translation(getMoveMaping(0, 0.005 * delta));
	this->myTime += delta;
	if (4000 < myTime) {
		isDead = true;
	}
	checkColl();
}


Bullet::Bullet(Model* model, GameObjectManager* manager) {
	init_GameObject(model, manager, 0);
}


void Bullet::checkColl() {
	Node* head = manager->enemys->head;
	int size = manager->enemys->size;
	//printf("size : %d\n", manager->eBullet->size);
	for (int i = 0; i < size; i++) {
		if (head->get()->transform.position.isColl(transform.position, 0.2)) {
			((Enemy*)(head->get()))->isDead = true;
			isDead = true;
			break;
		} else {
			head = head->next;
		}
	}
}
