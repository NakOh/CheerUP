
#include "Enemy.h"
#include "GameObjectManager.h"
#include <ctime>

void Enemy::update(int delta) {
	if (type == TYPE_ATTACK) {
		//나를 향해 돌진 (나의 위치 정보를 계속 받아와야 대는데..?
		transform.Translation(frontVec * delta);
	}
	else if (type == TYPE_DEFENSE) {
		//일정 이상 나갔다가 다시 뒤로 돌아오는 식으로
		transform.Translation(getMoveMaping(0, -0.00001 * delta * (800 - timer)));
		transform.Rotation(0, -_gradient, 0);
		Vec4 charPos = manager->myChar->transform.position;
		Vec4 minus = transform.position - charPos;
		float theta = minus.x / minus.y;
		_gradient = atan(theta);
		if (transform.position.y < charPos.y)	_gradient -= PI;
		transform.Rotation(0, _gradient, 0);
	}
	else if (type == TYPE_MIX) {
		transform.Translation(getMoveMaping(0, -0.001 * delta));
	}
	else {
		transform.Translation(getMoveMaping(0, -0.001 * delta));
	}
	timer += delta;
	if (deadTime < timer) {
		isDead = true;
	}
	update_shoot(delta);
}

void Enemy::addBullet(Vec4 vec) {
	EnemyBullet* bullet = new EnemyBullet(vec, manager->models.sphere, manager);
	manager->eBullet->addFront(bullet);
	bullet->transform.SetPosition(transform.position);
	bullet->transform.SetScale(0.2f, 0.2f, 0.2f);
}

void Enemy::update_shoot(int delta) {
	if (type == TYPE_ATTACK) {
	
	} else if (type == TYPE_DEFENSE) {
		if (bullet_createTimer > bullet_createMaxTimer) {
			Vec4 charPos = getReverseMaping(manager->myChar->transform.position);
			Vec4 myPos = getReverseMaping(transform.position);
			Vec4 minus = myPos - charPos;
			minus.z = 0;
			minus.rotZ(-PI * 0.15);
			minus.normalize();
			addBullet(getMoveMaping(minus.x * 3, minus.y * 3));
			minus.rotZ(PI * 0.1);
			minus.normalize();
			addBullet(getMoveMaping(minus.x * 3, minus.y * 3));
			minus.rotZ(PI * 0.1);
			minus.normalize();
			addBullet(getMoveMaping(minus.x * 3, minus.y * 3));
			minus.rotZ(PI * 0.1);
			minus.normalize();
			addBullet(getMoveMaping(minus.x * 3, minus.y * 3));
			minus.rotZ(PI * 0.1);
			minus.normalize();
			addBullet(getMoveMaping(minus.x * 3, minus.y * 3));

			bullet_createTimer -= bullet_createMaxTimer * 2;
		} else {
			bullet_createTimer += delta;
		}
	} else {
		if (bullet_createTimer > bullet_createMaxTimer) {
			EnemyBullet* bullet = new EnemyBullet(manager->models.sphere, manager);
			manager->eBullet->addFront(bullet);
			bullet->transform.SetPosition(transform.position);
			bullet->transform.SetScale(0.2f, 0.2f, 0.2f);
			bullet_createTimer -= bullet_createMaxTimer;
		} else {
			bullet_createTimer += delta;
		}
	}
}



void Enemy::initType(int type) {
	this->type = type;
	if (type == TYPE_ATTACK) {
		Vec4 charPos = manager->myChar->transform.position;
		charPos = transform.position - charPos;
		transform.Rotation(0, charPos.x / charPos.y, 0);
		charPos.normalize();
		frontVec = charPos * 0.005;
	}else if (type == TYPE_DEFENSE) {
		bullet_createMaxTimer = 800;
		deadTime = 2000;
	}
}

Enemy::Enemy(Model* model, GameObjectManager* manager) {
	init_GameObject(model, manager, TAG_ENEMY);
	float pos = 2.5f - ((float)(rand() % 100)) / 20;
	bullet_createMaxTimer = rand() % 1000 + 1000; //여기서 바꾸면 총알 주기가 달라진다.
	transform.SetPosition(getMaping(pos, 5));
	transform.Rotation(-PI * 0.4f, -PI * 0.5f, 0);
	initType(TYPE_DEFENSE);

}

