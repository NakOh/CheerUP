
#include "Map.h"

void Map::update(int delta) {
	transform.Translation(0, -0.0005 * delta, -0.0005 * delta * 0.3);
	if (transform.position.y < -12) {
		transform.SetPosition(0, 18, 12);
	}
}


Map::Map(Model* model, GameObjectManager* manager) {
	init_GameObject(model, manager, TAG_BASIC_MAP);
	transform.SetPosition(0, 18, 12);
	transform.SetScale(60, 40, 40);
	transform.Rotation(-PI * 0.4072f, -PI * 0.5f, 0);
}