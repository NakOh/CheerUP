#include "GameObjectManager.h"


Manager::Manager() {
	pool = std::vector<GameObject>();
}
void Manager::Add(GameObject* obj) {
	pool.push_back(*obj);
}
void Manager::Add(const char* path, bool objFile) {
	Add(new GameObject(path, objFile));
}
void Manager::Render() {
	for (int i = 0; i < pool.size(); i++) {
		//pool.at(i).Draw()
	}
}
void Manager::Update() {

}
