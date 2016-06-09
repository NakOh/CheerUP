
#include "Enemy.h"
#include <ctime>

void Enemy::update(int delta) {
	if (type == TYPE_ATTACK) {
		//���� ���� ���� (���� ��ġ ������ ��� �޾ƿ;� ��µ�..?
		transform.Translation(0, -0.001 * delta, -0.001 * delta * 0.4);
	}
	else if (type == TYPE_DEFENSE) {
		//���� �̻� �����ٰ� �ٽ� �ڷ� ���ƿ��� ������
		if (transform.position.y < 1) {
			speed = -speed;
		}
		if (transform.position.y > 5) {
			speed = -speed;
		}
		transform.Translation(0, -0.001 * delta * speed, -0.001 * delta * 0.4);
	}
	else if (type == TYPE_MIX) {
		transform.Translation(0, -0.001 * delta, -0.001 * delta * 0.4);
	}
	else {
		transform.Translation(0, -0.001 * delta, -0.001 * delta * 0.4);
	}
	timer += delta;
	if (20000 < timer) {
		isDead = true;
	}

}



Enemy::Enemy(Model* model, GameObjectManager* manager) {
	init_GameObject(model, manager, TAG_ENEMY);
	float pos = 2.5f - ((float)(rand() % 100)) / 20;
	bullet_createMaxTimer = rand() % 1000 + 1000; //���⼭ �ٲٸ� �Ѿ� �ֱⰡ �޶�����.
	type = rand() % 3;
	transform.SetPosition(pos, 5, 6);
	transform.Rotation(-PI * 0.4f, -PI * 0.5f, 0);
}

