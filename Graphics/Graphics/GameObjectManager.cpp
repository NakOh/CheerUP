#include "GameObjectManager.h"


GameObjectManager::GameObjectManager() {
	eBullet = new LinkedList();
	myBullet = new LinkedList();
	enemys = new LinkedList();

	enemyVar = EnemyVar();

	shader = ShaderID();
	model = new Model("models/flight.dat");

	light = new Light();
	camera = new Camera();
	light->Init(8, 20, -15);
	camera->Init();
}

void GameObjectManager::enemyDestroy() {

	bool reFind = true;

	while (reFind) {
		reFind = false;
		Node* head = enemys->head;
		for (int i = 0; i < enemys->size; i++) {
			if (((Enemy*)head->get())->isDead) {
				enemys->remove(i);
				reFind = true;
				break;
			} else {
				head = head->next;
			}
		}
	}
}

void GameObjectManager::enemyUpdate(int delta) {
	enemyVar.createTimer += delta;
	if (enemyVar.createTimer > enemyVar.createMaxTimer) {
		Enemy* obj;
		obj = new Enemy(model, this);
		enemys->addBack(obj);

		enemyVar.createTimer -= enemyVar.createMaxTimer;
	}
	enemyDestroy();
}

void GameObjectManager::addBullet() {
	Bullet* bullet = new Bullet(model, this);
	bullet->transform.SetPosition(1, 0, 3);
	myBullet->addFront(bullet);
}

void GameObjectManager::render() {
	if(eBullet != nullptr)		for (int i = 0; i < eBullet->size; i++)		shader.render(*(eBullet->at(i)->get()), TEXTURE_CODE_PLAYER);
	if (myBullet != nullptr)	for (int i = 0; i < myBullet->size; i++)	shader.render(*(myBullet->at(i)->get()), TEXTURE_CODE_BULLET);
	if (enemys != nullptr)		for (int i = 0; i < enemys->size; i++)		shader.render(*(enemys->at(i)->get()), TEXTURE_CODE_ENEMY);
}

void GameObjectManager::update(int delta) {
	if (eBullet != nullptr)  for (int i = 0; i < eBullet->size; i++)		eBullet->at(i)->get()->update(delta);
	if (myBullet != nullptr)  for (int i = 0; i < myBullet->size; i++)		myBullet->at(i)->get()->update(delta);
	if (enemys != nullptr)  for (int i = 0; i < enemys->size; i++)			enemys->at(i)->get()->update(delta);
	enemyUpdate(delta);
}
