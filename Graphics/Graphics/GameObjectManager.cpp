#include "GameObjectManager.h"


Manager::Manager() {
	list = new LinkedList();
	 //pool = list->createList();	
}
void Manager::Add(GameObject* obj) {
	//list->insertNodeAfter(pool->head, obj);
}
void Manager::Render() {
	//for (int i = 0; i < list->getSize(); i++) {
		//pool->head->data->Draw();
		//camera �� light���� �ʿ��� (���� Main�� ����, �����;ߴ�)
	//}
}
void Manager::Update() {
	list->addFront(new GameObject("models/flight.dat", new Camera(), new Light()));
}

int Manager::getObjectSize() {
	return list->size;
}
