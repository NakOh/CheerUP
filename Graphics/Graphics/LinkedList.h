#pragma once

class GameObject;
class Node {
public:
	Node* prev;
	Node* next;

	GameObject* data;
};

class List {
public:
	Node* head;
};

class LinkedList
{
private:
	int size;

public:
	List* createList();
	void insertNodeAfter(Node* node, GameObject* data);
	int getSize();
	void removeNode(Node* node, bool deleteData);
	void removeList(List* list, bool deleteData);
};

