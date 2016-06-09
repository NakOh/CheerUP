
#include "MyCharacter.h"

void MyCharacter::update(int delta) {	
	skill_Timer += delta;
}


MyCharacter::MyCharacter(Model* model, GameObjectManager* manager) {
	init_GameObject(model, manager, TAG_PLAYER);
	transform.SetPosition(0, 5, 6);
	transform.Rotation(-PI * 0.4f, -PI * 0.5f, 0);
}
