#include "GameObjectManager.h"


GameObjectManager::GameObjectManager(Camera* camera, Light* light) {
	eBullet = new LinkedList();
	myBullet = new LinkedList();
	enemys = new LinkedList();

	this->light = light;
	this->camera = camera;

	Enemy* obj;
	obj = new Enemy(this->camera, this->light);
	obj->transform.SetPosition(0, 0, 3);
	obj->transform.Scalelation(2, 2, 2);
	obj->transform.Rotation(100, 0, 0);
	enemys->addFront(obj);
}

void GameObjectManager::addBullet() {
	Bullet* bullet = new Bullet(camera, light);
	bullet->transform.SetPosition(1, 0, 3);
	myBullet->addFront(bullet);
}

void GameObjectManager::render() {
	if(eBullet != nullptr)  for (int i = 0; i < eBullet->size; i++)		eBullet->at(i)->get()->draw();
	if (myBullet != nullptr) for (int i = 0; i < myBullet->size; i++)	myBullet->at(i)->get()->draw();
	if (enemys != nullptr) for (int i = 0; i < enemys->size; i++)		enemys->at(i)->get()->draw();
}
void GameObjectManager::update(int delta) {
	if (eBullet != nullptr)  for (int i = 0; i < eBullet->size; i++)		eBullet->at(i)->get()->update(delta);
	if (myBullet != nullptr)  for (int i = 0; i < myBullet->size; i++)		myBullet->at(i)->get()->update(delta);
	if (enemys != nullptr)  for (int i = 0; i < enemys->size; i++)		enemys->at(i)->get()->update(delta);
}
