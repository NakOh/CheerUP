#include "LinkedList.h"

#include <iostream>




void Node::removeBack() {
	if (next != nullptr) {
		Node* remove = next;
		if (next->next != nullptr) {
			next = next->next;
			next->prev = this;
		} else {
			next = nullptr;
		}
		free(remove);
	}
}

bool Node::hasData() {
	return isData;
}


void Node::set(GameObject* go) {
	isData = true;
	data = go;
}


GameObject* Node::get() {
	return data;
}



Node::Node() {
	isData = false;
	prev = nullptr;
	next = nullptr;
	data = nullptr;
}



Node::Node(GameObject* go) {
	isData = true;
	prev = nullptr;
	next = nullptr;
	data = go;
}



void Node::deleteData() {
	if (isData)		free(data);
}



/*
void Node::remove() {
	Node* prevN = nullptr;
	Node* nextN = nullptr;
	if (prev != nullptr) {
		prevN = prev;
		prev->next = nullptr;
	}
	if (next != nullptr) {
		nextN = next;
		next->prev = nullptr;
	}
	if (prevN != nullptr && nextN != nullptr) {
		prevN->next = nextN;
		nextN->prev = prevN;
	}
	deleteData();
}
*/

Node::~Node() {
	deleteData();
}


void LinkedList::add(int num, GameObject* obj) {
	if (num >= size || num < 0)	return;
	Node* target = at(num);
	Node* newN = new Node(obj);
	if(target->next != nullptr)
	newN->next = target->next;
	newN->prev = target;
	target->next = newN;
	size++;
}


LinkedList::LinkedList() {
	size = 0;
	this->head = nullptr;
	printf("Test");
}


LinkedList::~LinkedList() {
	int count = size;
	for (int i = 0; i < count; i++)	remove(0);
}


void LinkedList::addFront(GameObject* obj) {
	Node* newNode = new Node(obj);
	if(this->head != nullptr)	newNode->next = head;
	this->head = newNode;
	size++;
}



void LinkedList::addBack(GameObject* obj) {
	if (head != nullptr) {
		Node* target = at(size-1);
		Node* newNode = new Node(obj);
		target->next = newNode;
		newNode->prev = target;
		size++;
	} else {
		addFront(obj);
	}
}


Node* LinkedList::at(int num) {
	if (num >= size || num < 0)	return new Node();
	Node* target = head;
	for (int i = 0; i < num; i++)
		target = target->next;
	return target;
}

GameObject* LinkedList::get(int num) {
	return at(num)->get();
}


void LinkedList::remove(int at) {
	if (at >= size || at < 0)	return;

	if (at == 0) {
		if (head->next != nullptr) {
			head = head->next;
			head->prev = nullptr;
			size--;
		}
	} else {
		Node* target = head;
		for (int i = 0; i < at - 1; i++)
			target = target->next;
		target->removeBack();
		size--;
	}
}