#include "GameObjectManager.h"


Manager::Manager() {
	 pool = list->createList();	
}
void Manager::Add(GameObject* obj) {
	list->insertNodeAfter(pool->head, obj);
}
void Manager::Add(const char* path, bool objFile) {
	//Add(new GameObject(path, objFile));
}
void Manager::Render() {
	for (int i = 0; i < list->getSize(); i++) {
		//pool->head->data->Draw();
		//camera �� light���� �ʿ��� (���� Main�� ����, �����;ߴ�)
	}
}
void Manager::Update() {

}

int Manager::getObjectSize() {
	return list->getSize();
}
