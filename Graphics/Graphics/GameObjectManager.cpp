#include "GameObjectManager.h"


Manager::Manager() {
	list = new LinkedList();
	 //pool = list->createList();	
}
void Manager::Add(GameObject* obj) {
	list->addBack(obj);
	//list->insertNodeAfter(pool->head, obj);
}
void Manager::Render() {
	for (int i = 0; i < list->size; i++) {
		list->at(i)->get()->draw();
	}
}
void Manager::Update() {
	for (int i = 0; i < list->size; i++) {
		
	}
}

int Manager::getObjectSize() {
	return list->size;
}
