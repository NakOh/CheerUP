
#include "MyCharacter.h"
#include "GameObjectManager.h"

Input::Input() {
	left = right = up = down = false;
}

void MyCharacter::update(int delta) {	
	skill_Timer += delta;

	if (input.up)		velocity.y += 0.005 * delta;
	if (input.down)		velocity.y -= 0.005 * delta;
	if (input.left)		velocity.x -= 0.005 * delta;
	if (input.right)	velocity.x += 0.005 * delta;

	if (velocity.y > 1)		velocity.y = 1;
	if (velocity.y < -1)	velocity.y = -1;
	if (velocity.x > 1)		velocity.x = 1;
	if (velocity.x < -1)	velocity.x = -1;

	transform.Translation(velocity.x * delta * 0.005, velocity.y * delta * 0.005, velocity.y * delta * 0.005 * 0.3);

	for (int i = 0; i < delta; i++) {
		velocity.x *= 0.995;
		velocity.y *= 0.995;
		checkColl();
	}

}

void MyCharacter::checkColl() {
	Node* head = manager->eBullet->head;

	//printf("size : %d\n", manager->eBullet->size);
	for (int i = 0; i < manager->eBullet->size; i++) {
		if (head->get()->transform.position.isColl(transform.position, 0.2)) {
			isDead = true;
			break;
		} else {
			head = head->next;
		}
	}
}


MyCharacter::MyCharacter(Model* model, GameObjectManager* manager) {
	init_GameObject(model, manager, TAG_PLAYER);
	transform.SetPosition(0, -1.6, 4.02);
	//myChar->transform.Rotation(0, 0, 90.f);
	velocity = Vec4();
	transform.Rotation(-PI * 0.4017f, PI * 0.5f, 0);
	input = Input();
}
