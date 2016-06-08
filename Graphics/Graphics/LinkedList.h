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
	//num ��° Node* �ڿ� ���δ�.
	void add(int num, T* obj);
	void addFront(T* obj);
	void addBack(T* obj);
	Node<T>* at(int num);

	//0 ���� ����.
	void remove(int at);
};

