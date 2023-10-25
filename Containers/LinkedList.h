#include <iostream>
#include "Node.h"

#pragma once
using namespace std;

template <class Number>
class LinkedList
{
    Node <Number> *head;
	Node <Number> *tail;
	unsigned length;
public:
	void push(int index, Number value);
    void pop(int index);
	void change(int index, Number value);
	unsigned getLength();
	Number peek(int index);
	friend ostream& operator << (ostream& st, LinkedList <Number> l);
	LinkedList(unsigned length, Number *values);
	LinkedList(const LinkedList <Number> &l);
	LinkedList();
	~LinkedList();
};

template <class Number>
LinkedList<Number>::LinkedList(unsigned length, Number* values) {
	this->length = 0;
	for (int i = 0; i < length; i++)
		push(0, values[i]);
}

template <class Number>
LinkedList<Number>::LinkedList(const LinkedList<Number> & l) {
	length = l.length;
	head = nullptr;
	tail = nullptr;
	if (!length) {
		return;
	}
	Node<Number>* currNode = nullptr;
	Node<Number>* currNodeL = l.head;
	Node<Number>* prevNode = nullptr;
	for (int i = 0; i < length; i++) {
		currNode = new Node<Number>(currNodeL->value);
		if (!i)
			head = currNode;
		currNode->prev = prevNode;
		if (prevNode)
			prevNode->next = currNode;
		prevNode = currNode;
		currNodeL = currNodeL->next;
	}
	tail = currNode;
}

template <class Number>
LinkedList<Number>::LinkedList() {
	head = nullptr;
	tail = nullptr;
	length = 0;
}

template <class Number>
LinkedList<Number>::~LinkedList() {
	while (length)
		pop(0);
}

template <class Number>
ostream& operator << (ostream& st, LinkedList<Number> l) {
	for (int i = 0; i < (int)l.getLength() - 1; i++) {
		st << l.peek(i) << "---";
	}
	if ((int)l.getLength() - 1 >= 0)
		st << l.peek(l.getLength() - 1);
	return st;
}

template <class Number>
void LinkedList<Number>::push(int index, Number value) {
	Node<Number>* currNode = new Node<Number>(value);
	Node<Number>* nextNode = head;
	for (int i = 0; i < index; i++) {
		nextNode = nextNode->next;
	}
	currNode->next = nextNode;
	if (nextNode) {
		currNode->prev = nextNode->prev;
		nextNode->prev = currNode;
	}
	else {
		currNode->prev = tail;
	}
	if (currNode->prev)
		currNode->prev->next = currNode;
	if (index == 0)
		head = currNode;
	if (index == length)
		tail = currNode;
	length++;
}

template <class Number>
void LinkedList<Number>::pop(int index) {
	Node<Number>* currNode = head;
	for (int i = 0; i < index; i++) {
		currNode = currNode->next;
	}
	if (index == 0)
		head = currNode->next;
	if (index == length - 1)
		tail = currNode->prev;
	if (currNode->next)
		currNode->next->prev = currNode->prev;
	if (currNode->prev)
		currNode->prev->next = currNode->next;
	delete currNode;
	length--;
}

template <class Number>
void LinkedList<Number>::change(int index, Number value) {
	Node<Number>* currNode = head;
	for (int i = 0; i < index; i++)
		currNode = currNode->next;
	currNode->value = value;
}

template <class Number>
Number LinkedList<Number>::peek(int index) {
	Node <Number>* currNode = head;
	for (int i = 0; i < index; i++)
		currNode = currNode->next;
	if (!currNode)
		return 0; 
	return currNode->value;
}

template <class Number>
unsigned LinkedList<Number>::getLength() {
	return length;
}

