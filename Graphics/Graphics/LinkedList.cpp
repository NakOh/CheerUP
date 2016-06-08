#include "LinkedList.h"

#include <iostream>

List* LinkedList:: createList() {

	Node* head = new Node;
	head->prev = head;
	head->next = head;
	head->data = 0;
	size = 1;
	List* list = new List;
	list->head = head;

	return list;
}

void LinkedList::insertNodeAfter(Node* node, GameObject* data) {

	Node* before = node;
	Node* after = node->next;

	Node* newNode = new Node;
	newNode->data = data;
	newNode->next = after;
	newNode->prev = before;

	after->prev = newNode;
	before->next = newNode;

	size++;
}

void LinkedList::removeNode(Node* node, bool deleteData) {

	Node* before = node->prev;
	Node* after = node->next;

	before->next = after;
	after->prev = before;

	if (deleteData)
		delete node->data;
	delete node;

	size--;
}

void LinkedList::removeList(List* list, bool deleteData) {

	Node* current = list->head;

	do {
		Node* next = current->next;
		if (deleteData)
			delete current->data;
		delete current;

		current = next;

	} while (current != list->head);

	delete list;
	size = 0;
}

int LinkedList::getSize() {
	return size;
}