#include "GameObjectManager.h"

GameObjectManager::GameObjectManager() {
	eBullet = new LinkedList();
	myBullet = new LinkedList();
	enemys = new LinkedList();



	enemyVar = EnemyVar();

	shader = ShaderID();
	model = new Model("models/flight.dat");
	mapModel = new Model("models/basicMap.dat");
	sphereModel = new Model("models/sphere.dat");

	map = new Map(mapModel, this);
	map2 = new Map(mapModel, this);
	map2->transform.SetPosition(0, 3, 7);

	light = new Light();
	camera = new Camera();
	light->Init(8, 20, -15);
	camera->Init();

	myChar = new MyCharacter(model, this);
}

void GameObjectManager::enemyCreate(int delta) {
	enemyVar.createTimer += delta;
	if (enemyVar.createTimer > enemyVar.createMaxTimer) {
		Enemy* obj;
		obj = new Enemy(model, this);		
		enemys->addBack(obj);
		enemyVar.createTimer -= enemyVar.createMaxTimer;
	}
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
			}
			else {
				head = head->next;
			}
		}
	}
}

void GameObjectManager::enemyShoot(int delta) {
	if (enemys != nullptr) {
		for (int i = 0; i < enemys->size; i++) {
			if (dynamic_cast<Enemy*>(enemys->get(i))->bullet_createTimer > dynamic_cast<Enemy*>(enemys->get(i))->bullet_createMaxTimer) {
				Bullet* bullet = new Bullet(sphereModel, this);
				eBullet->addFront(bullet);
				Vec4 pos = enemys->get(i)->transform.position;
				bullet->transform.SetPosition(pos.x, pos.y, pos.z);
				dynamic_cast<Enemy*>(enemys->get(i))->bullet_createTimer -= dynamic_cast<Enemy*>(enemys->get(i))->bullet_createMaxTimer;
			}
			else {
				dynamic_cast<Enemy*>(enemys->get(i))->bullet_createTimer += delta;
			}
		}
	}
}

void GameObjectManager::enemyUpdate(int delta) {
	enemyCreate(delta);
	enemyShoot(delta);
	enemyDestroy();
}

void GameObjectManager::addBullet() {
	Bullet* bullet = new Bullet(model, this);
	Vec4 pos = myChar->transform.position;
	bullet->transform.SetPosition(pos.x, pos.y, pos.z);
	myBullet->addFront(bullet);
}

void GameObjectManager::render() {
	if(eBullet != nullptr)		for (int i = 0; i < eBullet->size; i++)		shader.render(*(eBullet->get(i)), TEXTURE_CODE_PLAYER, false);
	if (myBullet != nullptr)	for (int i = 0; i < myBullet->size; i++)	shader.render(*(myBullet->get(i)), TEXTURE_CODE_BULLET, false);
	if (enemys != nullptr)		for (int i = 0; i < enemys->size; i++)		shader.render(*(enemys->get(i)), TEXTURE_CODE_ENEMY, false);
	shader.render(*map, TEXTURE_CODE_BASIC_MAP, true);
	shader.render(*map2, TEXTURE_CODE_BASIC_MAP, true);
}

void GameObjectManager::update(int delta) {
	if (eBullet != nullptr)  for (int i = 0; i < eBullet->size; i++)		eBullet->at(i)->get()->update(-delta);
	if (myBullet != nullptr)  for (int i = 0; i < myBullet->size; i++)		myBullet->at(i)->get()->update(delta);
	if (enemys != nullptr)  for (int i = 0; i < enemys->size; i++)			enemys->at(i)->get()->update(delta);
	enemyUpdate(delta);
	map->update(delta);
	map2->update(delta);
	myChar->update(delta);
}
