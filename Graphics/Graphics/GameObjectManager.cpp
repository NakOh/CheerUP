#include "GameObjectManager.h"


GameObjectManager::GameObjectManager() {
	eBullet = new LinkedList();
	myBullet = new LinkedList();
	enemys = new LinkedList();

	shader = ShaderID();
	model = new Model("models/flight.dat");

	light = new Light();
	camera = new Camera();
	light->Init(8, 20, -15);
	camera->Init();

	Enemy* obj;
	obj = new Enemy(model, this);
	obj->transform.SetPosition(0, 0, 3);
	obj->transform.Scalelation(2, 2, 2);
	obj->transform.Rotation(100, 0, 0);
	enemys->addFront(obj);
}

void GameObjectManager::addBullet() {
	Bullet* bullet = new Bullet(model, this);
	bullet->transform.SetPosition(1, 0, 3);
	myBullet->addFront(bullet);
}

void GameObjectManager::render() {
	if(eBullet != nullptr)  for (int i = 0; i < eBullet->size; i++)		shader.render(*(eBullet->at(i)->get()), 0);
	if (myBullet != nullptr) for (int i = 0; i < myBullet->size; i++)	shader.render(*(myBullet->at(i)->get()), 0);
	if (enemys != nullptr) for (int i = 0; i < enemys->size; i++)		shader.render(*(enemys->at(i)->get()), 0);
}
void GameObjectManager::update(int delta) {
	if (eBullet != nullptr)  for (int i = 0; i < eBullet->size; i++)		eBullet->at(i)->get()->update(delta);
	if (myBullet != nullptr)  for (int i = 0; i < myBullet->size; i++)		myBullet->at(i)->get()->update(delta);
	if (enemys != nullptr)  for (int i = 0; i < enemys->size; i++)		enemys->at(i)->get()->update(delta);
}
