#pragma once
#include<iostream>
using namespace std;

#include"Node.h"

template <typename T>
class Linked_List
{
private:
	Node<T>* Head;	//Pointer to the head of the list
	//You can add tail pointer too (depending on your problem)
public:


	Linked_List()
	{
		Head = nullptr;
	}

	//List is being desturcted ==> delete all items in the list
	~Linked_List()
	{
		DeleteAll();
	}
	////////////////////////////////////////////////////////////////////////




	void DeleteAll()
	{
		Node<T>* P = Head;
		while (Head)
		{
			P = Head->getNext();
			delete Head;
			Head = P;
		}
	}



	
	void insert(const T& data) {
		if (!Head) {

			Head = new Node<T>(data);
			Head->setNext(NULL);
			return;
		}
		Node<T>* newNode = new Node<T>(data);
		newNode->setNext(Head);
		Head = newNode;
	}
	//[4] DeleteFirst
	//Deletes the first node in the list
	bool deleting (int t)
	{
		if (!Head) return false;
		if (*Head->getItem() == t) {

			Node<T>* n = Head;
			Head = Head->getNext();
			delete n;
			return true;

		}
		Node<T>* temp = Head->getNext();
		Node<T>* prev = Head;

		while (temp)
		{
			if (*temp->getItem() == t)
			{

				Node<T>* n = temp;
				prev->setNext(temp->getNext());
				delete n;
				return true;
			}
			temp = temp->getNext();
			prev = prev->getNext();

		}
		return false;
	}

	///////// GET_COUNT
	int get_count() {
		if (Head == NULL)return 0;
		Node<T>* p = Head;
		int count = 0;
		while (p)
		{
			count++;
			p = p->getNext();

		}
		return count;
	}


	//////////is empty
	bool is_empty() { return(Head == NULL); }
	T* search(int data) {
		if (!Head) return NULL;
		Node<T>* temp = Head;
		while (temp) {

			if (*temp->getItem() == data) {
				T l = temp->getItem();
				return &l;

			}
			temp = temp->getNext();
		}
		return NULL;


	}



	bool remove(int t)
	{
		if (!Head) return false;
		if (*Head->getItem() == t) {

			Node<T>* n = Head;
			Head = Head->getNext();
			return true;

		}
		Node<T>* temp = Head->getNext();
		Node<T>* prev = Head;

		while (temp)
		{
			if (*temp->getItem() == t)
			{

				Node<T>* n = temp;
				prev->setNext(temp->getNext());
				return true;
			}
			temp = temp->getNext();
			prev = prev->getNext();

		}
		return false;
	}

	//[1]InsertEnd 
	//inserts a new node at end if the list
	void enqueue(const T& data) {
		Node<T>* newNode = new Node<T>(data);
		Node<T>* p = Head;
		if (Head == NULL)Head = newNode;
		else {
			while (p->getNext()) { p = p->getNext(); }
			p->setNext(newNode);
		}
	}
	//[4] DeleteFirst
	//Deletes the first node in the list
	bool dequeue(T& t) {
		if (Head == NULL)return false;
		Node<T>* p = Head;
		t = Head->getItem();
		Head = Head->getNext();
		return true;
	}

	bool  peek(T& t)
	{
		if (is_empty()) return false;
		t = Head->getItem();
		return true;
	}

};