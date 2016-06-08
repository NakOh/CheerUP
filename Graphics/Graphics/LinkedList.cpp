#include "LinkedList.h"

#include <iostream>



template <class T>
bool Node<T>::hasData() {
	return isData;
}

template <class T>
void Node<T>::set(T* go) {
	isData = true;
	data = go;
}

template <class T>
T* Node<T>::get() {
	return data;
}


template <class T>
Node<T>::Node() {
	isData = false;
	prev = nullptr;
	next = nullptr;
	data = nullptr;
}


template <class T>
Node<T>::Node(T* go) {
	isData = true;
	prev = nullptr;
	next = nullptr;
	data = go;
}


template <class T>
void Node<T>::deleteData() {
	if (isData)	delete data;
}


template <class T>
void Node<T>::remove() {
	Node<T>* prevN = nullptr;
	Node<T>* nextN = nullptr;
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


template <class T>
Node<T>::~Node() {
	remove();
}

template <class T>
void LinkedList<T>::add(int num, T* obj) {
	if (num >= size || num < 0)	return;
	Node<T>* target = at(num);
	Node<T>* newN = new Node(obj);
	if(target->next != nullptr)
	newN->next = target->next;
	newN->prev = target;
	target->next = newN;
	size++;
}

template <class T>
LinkedList<T>::LinkedList() {
	size = 0;
	this->head = nullptr;
}

template <class T>
LinkedList<T>::~LinkedList() {
	int count = size;
	for (int i = 0; i < count; i++)	remove(0);
}

template <class T>
void LinkedList<T>::addFront(T* obj) {
	Node<T>* newNode = new Node<T>(obj);
	if(this->head != nullptr)	newNode->next = this->head;
	else	newNode->prev = nullptr;
	this->head = newNode;
	size++;
}

template <class T>
void LinkedList<T>::addBack(T* obj) {
	Node<T>* target = head;
	while (target->next != nullptr)
		target = target->next;
	Node<T>* newNode = new Node<T>(obj);
	target->next = newNode;
	newNode->prev = target;
}

template <class T>
Node<T>* LinkedList<T>::at(int num) {
	if (num >= size || num < 0)	return new Node<T>();
	Node<T>* target = head;
	for (int i = 0; i < num; i++)
		target = target->next;
	return target;
}

template <class T>
void LinkedList<T>::remove(int at) {
	if (at >= size || num < 0)	return;

	Node<T>* target = head;

	for (int i = 0; i < at; i++)
		target = target->next;

	if (target->next != nullptr) {
		target->prev->next = target->next;
		target->next->prev = target->prev;
	}
	if (target->hasData())
		target->deleteData();
	delete target;
	size--;
}