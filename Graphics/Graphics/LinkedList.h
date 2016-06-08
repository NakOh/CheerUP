#pragma once

class GameObject;

template <class T>
class Node{
private:
	T* data;
	bool isData;
public:
	Node* prev;
	Node* next;

	void remove();

	bool hasData();
	void set(T* go);
	T* get();
	void deleteData();
	Node();
	~Node();
	Node(T* go);
};


template <class T>
class LinkedList {
public:
	int size;
	Node<T>* head;
	LinkedList();
	~LinkedList();
	//num 번째 Node* 뒤에 붙인다.
	void add(int num, T* obj);
	void addFront(T* obj);
	void addBack(T* obj);
	Node<T>* at(int num);

	//0 부터 시작.
	void remove(int at);
};

