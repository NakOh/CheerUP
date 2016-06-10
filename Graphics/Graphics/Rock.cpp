#include "Rock.h"


void Rock::update(int delta) {
	timer += delta;
	if (30000 < timer) {
		isDead = true;
	}
	transform.Translation(getMoveMaping(0, -0.0005 * delta));

	transform.Rotation(randRot.x * delta, randRot.y* delta, randRot.z* delta);
}


Rock::Rock(Model* model, GameObjectManager* manager)
{
	init_GameObject(model, manager, TAG_ROCK);
	float posX = 2.5f - ((float)(rand() % 100)) / 20;
	float posY = 0.5f - ((float)(rand() % 100)) / 100;
	float posZ = 1.0f - ((float)(rand() % 100)) / 50;
	float scales = ((float)(rand() % 100)) / 100 + 0.3;
	transform.SetPosition(posX, posY + 7, posZ + 8);
	transform.SetScale(scales, scales, scales);
	randRot.x = (0.5f - ((float)(rand() % 100)) / 100) * 0.001;
	randRot.y = (0.5f - ((float)(rand() % 100)) / 100) * 0.001;
	randRot.z = (0.5f - ((float)(rand() % 100)) / 100) * 0.001;
}


