//	This is an updated version of code originally
//  created by Frank M. Carrano and Timothy M. Henry.
//  Copyright (c) 2017 Pearson Education, Hoboken, New Jersey.

/** ADT stack: Array-based implementation.
@file ArrayStack.h */

#ifndef __stack
#define __stack
#include<iostream>
using namespace std;


//Unless spesificed by the stack user, the default size is 100
template<typename T>
class Stack 
{
private:
	T* items;		// Array of stack items
	int      top;                   // Index to top of stack
	const int STACK_SIZE;

public:

	Stack(int MaxSize=1000) : STACK_SIZE(MaxSize)
	{
		items = new T[STACK_SIZE];
		top = -1;
	}  // end default constructor

	//Function getCapacity() returns the stack max size
	//added for array implementaion only
	int getCapacity()
	{
		return STACK_SIZE;
	}

	bool isEmpty() const
	{
		return top == -1;
	}  // end isEmpty

	bool push(const T& newEntry)
	{
		if (top == STACK_SIZE - 1) return false;	//Stack is FULL

		top++;
		items[top] = newEntry;
		return true;
	}  // end push

	bool pop(T& TopEntry)
	{
		if (isEmpty()) return false;

		TopEntry = items[top];
		top--;
		return true;
	}  // end pop

	bool peek(T& TopEntry) const
	{
		if (isEmpty()) return false;

		TopEntry = items[top];
		return true;
	}  // end peek

	   //Destructor
	~Stack()
	{
		delete[]items;
	}

	//Copy constructor
	Stack(const Stack<T>& S) :STACK_SIZE(S.STACK_SIZE)
	{
		items = new T[STACK_SIZE];
		for (int i = 0; i <= S.top; i++)
			items[i] = S.items[i];
		top = S.top;
	}

	void print()
	{
		Stack<T>temp1;
		Stack<T>temp2;
		T x;
		while (!this->isEmpty())
		{
			pop(x);
			cout << x << ",";
			temp1.push(x);
		}

		while (!temp1.isEmpty())
		{
			temp1.pop(x);
			temp2.push(x);
		}
		while (!temp2.isEmpty())
		{
			temp2.pop(x);
			this->push(x);
		}
	}
}; // end ArrayStack

#endif