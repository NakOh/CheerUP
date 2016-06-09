
#include "MyCharacter.h"

void MyCharacter::update(int delta) {	
	skill_Timer += delta;
}


MyCharacter::MyCharacter(Model* model, GameObjectManager* manager) {
	init_GameObject(model, manager, TAG_PLAYER);
	transform.SetPosition(0, -1.5, 3);
	//myChar->transform.Rotation(0, 0, 90.f);
	transform.Rotation(-PI * 0.4f, -PI * 0.5f, 90.f);
}
