#include "GameObjectManager.h"

GameObjectManager::GameObjectManager() {
	eBullet = new LinkedList();
	myBullet = new LinkedList();
	enemys = new LinkedList();


	shakingVar = ShakingVar(this);
	rocks = new LinkedList();


	enemyVar = EnemyVar();
	rockVar = RockVar();
	shader = ShaderID();

	models = ModelBox();

	map = new Map(models.map, this);
	map2 = new Map(models.map, this);
	map2->transform.SetPosition(0, 3, 7);

	light = new Light();
	camera = new Camera();
	light->Init(8, 20, -15);
	camera->Init();

	myChar = new MyCharacter(models.flight, this);
}

void GameObjectManager::enemyCreate(int delta) {
	enemyVar.createTimer += delta;
	if (enemyVar.createTimer > enemyVar.createMaxTimer) {
		Enemy* obj;
		obj = new Enemy(models.flight, this);
		enemys->addBack(obj);
		enemyVar.createTimer -= enemyVar.createMaxTimer;
	}
}

void GameObjectManager::rockCreate(int delta) {
	rockVar.createTimer += delta;
	if (rockVar.createTimer > rockVar.createMaxTimer) {
		Rock* obj;
		obj = new Rock(models.sphere, this);
		obj->transform.SetScale(0.2f, 0.2f, 0.2f);
		rocks->addBack(obj);
		
		rockVar.createTimer -= rockVar.createMaxTimer;
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
				break;
			}
			else {
				head = head->next;
			}
		}
	}
}


void GameObjectManager::eBulletDestroy() {
	bool reFind = true;
	while (reFind) {
		reFind = false;
		Node* head = eBullet->head;
		for (int i = 0; i < eBullet->size; i++) {
			if (((EnemyBullet*)head->get())->isDead) {
				eBullet->remove(i);
				//reFind = true;
				break;
			} else {
				head = head->next;
			}
		}
	}
}

void GameObjectManager::rockDestroy() {
	bool reFind = true;
	while (reFind) {
		reFind = false;
		Node* head = rocks->head;
		for (int i = 0; i < rocks->size; i++) {
			if (((Rock*)head->get())->isDead) {
				rocks->remove(i);
				//reFind = true;
				break;
			}
			else {
				head = head->next;
			}
		}
	}
}

void GameObjectManager::myBulletDestroy() {
	bool reFind = true;
	while (reFind) {
		reFind = false;
		Node* head = myBullet->head;
		for (int i = 0; i < myBullet->size; i++) {
			if (((Bullet*)head->get())->isDead) {
				myBullet->remove(i);
				//reFind = true;
				break;
			} else {
				head = head->next;
			}
		}
	}
}


ModelBox::ModelBox() {
	flight = new Model("models/flight.dat");
	map = new Model("models/basicMap.dat");
	sphere = new Model("models/sphere.dat");
	helly = new Model("models/helly.dat");
}

void GameObjectManager::enemyUpdate(int delta) {
	enemyCreate(delta);
	enemyDestroy();
}

void GameObjectManager::rockUpdate(int delta) {
	rockCreate(delta);
	rockDestroy();
}

void GameObjectManager::addBullet() {
	Bullet* bullet = new Bullet(models.sphere, this);
	Vec4 pos = myChar->transform.position;
	bullet->transform.SetPosition(pos.x, pos.y, pos.z);
	bullet->transform.SetScale(0.2f, 0.2f, 0.2f);
	myBullet->addFront(bullet);
}

void GameObjectManager::render() {
	if(eBullet != nullptr)		for (int i = 0; i < eBullet->size; i++)		shader.render(*(eBullet->get(i)), TEXTURE_CODE_COLOR_RED, true);
	if (myBullet != nullptr)	for (int i = 0; i < myBullet->size; i++)	shader.render(*(myBullet->get(i)), TEXTURE_CODE_COLOR_BLUE, true);
	if (enemys != nullptr)		for (int i = 0; i < enemys->size; i++) {
		if(((Enemy*)(enemys->get(i)))->type == TYPE_DEFENSE)	shader.render(*(enemys->get(i)), TEXTURE_CODE_HELLY, false);
		else shader.render(*(enemys->get(i)), TEXTURE_CODE_ENEMY, false);
	}
	if (rocks != nullptr)		for (int i = 0; i < rocks->size; i++)		shader.render(*(rocks->get(i)), TEXTURE_CODE_ENEMY, false);
	shader.render(*map, TEXTURE_CODE_BASIC_MAP, true);
	shader.render(*map2, TEXTURE_CODE_BASIC_MAP, true);
	shader.render(*myChar, TEXTURE_CODE_PLAYER, false);
}

void GameObjectManager::update(int delta) {

	if (myChar->isDead) {
		shakingVar.startShaking();
		myChar->isDead = false;
	} else {
		if (eBullet != nullptr)  for (int i = 0; i < eBullet->size; i++)		eBullet->at(i)->get()->update(delta);
		if (myBullet != nullptr)  for (int i = 0; i < myBullet->size; i++)		myBullet->at(i)->get()->update(delta);
		if (enemys != nullptr)  for (int i = 0; i < enemys->size; i++)			enemys->at(i)->get()->update(delta);
		if (rocks != nullptr)  for (int i = 0; i < rocks->size; i++)			rocks->at(i)->get()->update(delta);
		enemyUpdate(delta);
		rockUpdate(delta);
		map->update(delta);
		map2->update(delta);
		myChar->update(delta);
		eBulletDestroy();
		myBulletDestroy();
	}
	shakingVar.update(delta);
}

void GameObjectManager::shakingCamera() {
	shakingVar.startShaking();
}

void ShakingVar::update(int delta) {
	if (isShaking) {
		if (timer < maxTimer) {
			float rangeX = 0.005f - (float)(rand() % 100) / 10000;
			pos.x += rangeX;
			manager->camera->pos.x += rangeX;

			float rangeY = 0.005f - (float)(rand() % 100) / 10000;
			pos.y += rangeY;
			manager->camera->pos.y += rangeY;

			timer++;
		} else {
			timer = 0;
			isShaking = false;
			manager->camera->pos.x -= pos.x;
			manager->camera->pos.y -= pos.y;
			pos.x = 0;
			pos.y = 0;
		}
	}
}