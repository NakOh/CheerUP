#pragma once
#ifndef __LINKEDLIST_H__
#define __LINKEDLIST_H__
class GameObject;


class Node{
private:
	GameObject* data;
	bool isData;
public:
	Node* prev;
	Node* next;

	void remove();

	bool hasData();
	void set(GameObject* go);
	GameObject* get();
	void deleteData();
	Node();
	~Node();
	Node(GameObject* go);
};



class LinkedList {
public:
	int size;
	Node* head;
	LinkedList();
	~LinkedList();
	//num ��° Node* �ڿ� ���δ�.
	void add(int num, GameObject* obj);
	void addFront(GameObject* obj);
	void addBack(GameObject* obj);
	Node* at(int num);

	//0 ���� ����.
	void remove(int at);
};

#endif
