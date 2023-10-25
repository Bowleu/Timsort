#include "LinkedList.h"
#pragma once

template <class Number>
class stack : private LinkedList<Number>
{
public:
	stack() : LinkedList<Number>() {};
	stack(const stack<Number>& s) : LinkedList(s) {};
	stack(unsigned length, Number* values) : LinkedList(length, values) {};
	friend ostream& operator << (ostream& st, stack <Number> l);
	void push(Number value);
	void pop();
	unsigned getLength();
	Number peek();
};

template <class Number>
ostream& operator << (ostream& st, stack<Number> l) {
	for (int i = 0; i < (int)l.getLength() - 1; i++) {
		st << l.LinkedList<Number>::peek(i) << "---";
	}
	if ((int)l.getLength() - 1 >= 0)
		st << l.LinkedList<Number>::peek(l.getLength() - 1);
	return st;
}

template <class Number>
void stack<Number>::push(Number value) {
	this->LinkedList<Number>::push(0, value);
}

template <class Number>
void stack<Number>::pop() {
	this->LinkedList<Number>::pop(0);
}

template <class Number>
Number stack<Number>::peek() {
	return this->LinkedList<Number>::peek(0);
}

template <class Number>
unsigned stack<Number>::getLength() {
	return this->LinkedList<Number>::getLength();
}
