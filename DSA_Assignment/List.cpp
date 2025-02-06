#include "List.h"

template class List<Movie>;

template<class T>
//constructor 
List<T>::List() {
	firstNode = NULL;
	size = 0;
}

template<class T>
//destructor
List<T>::~List() {
	Node* current = firstNode;
	while (current != nullptr) {
		Node* nextNode = current->next;
		delete current;
		current = nextNode;
	}
	firstNode = nullptr;
}

template<class T>
bool List<T>::add(T item) {
	Node* newNode = new Node;
	newNode->item = item;
	newNode->next = NULL;
	if (size == 0) {
		firstNode = newNode;
	}
	else {
		Node* current = firstNode;
		while (current->next != NULL) {
			current = current->next;
		}
		current->next = newNode;
	}
	size++;
	return true;
}

template<class T>
bool List<T>::add(int index, T item) {
	if (index < size && index >= 0) {
		Node* newNode = new Node;
		newNode->item = item;
		newNode->next = NULL;

		if (index == 0) {
			newNode->next = firstNode;
			firstNode = newNode;
		}
		else {
			Node* current = new Node;
			current = firstNode;
			for (int i = 1; i < index; i++) {
				current = current->next;
			}
			newNode->next = current->next;
			current->next = newNode;
		}
		size++;
		return true;
	}
	return false;
}

template<class T>
void List<T>::remove(int index) {
	if (index >= 0 && index < size) {
		if (index == 0) {
			firstNode = firstNode->next;
		}
		else {
			Node* current = firstNode;
			for (int i = 1; i < index; i++) {
				current = current->next;
			}
			current->next = current->next->next;
		}
		size--;
	}
}

template<class T>
T List<T>::get(int index) {
	if (index >= 0 && index < size) {
		Node* current = firstNode;
		for (int i = 0; i < index; i++) {
			current = current->next;
		}
		return current->item;
	}
	return T();
}

template<class T>
bool List<T>::isEmpty() {
	if (size == 0) {
		return true;
	}
	return false;
}

template<class T>
int List<T>::getLength() {
	return size;
}

template<class T>
void List<T>::print() {
	Node* current = firstNode;

	while (current != NULL) {
		cout << current->item.getTitle() << endl;
		current = current->next;
	}
}