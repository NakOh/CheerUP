#include "Rock.h"


void Rock::update(int delta) {

}


Rock::Rock(Model* model, GameObjectManager* manager)
{
	init_GameObject(model, manager, TAG_ROCK);
	float pos = 2.5f - ((float)(rand() % 100)) / 20;
	transform.SetPosition(pos, 5, 6);
}



Rock::~Rock()
{
}
