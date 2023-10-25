#pragma once

template <typename Number>
class Node {
public:
	Node* next = nullptr;
	Node* prev = nullptr;
	Number value;
	Node(Number value) {
		this->value = value;
	}
};