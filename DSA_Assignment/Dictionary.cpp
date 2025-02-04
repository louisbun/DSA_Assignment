#include "Dictionary.h"
#include<iostream>
using namespace std;

Dictionary::Dictionary() {
	size = 0;
	for (int i = 0; i < MAX_SIZE; i++) {
		items[i] = nullptr; // Initialize all buckets to null
	}
}

Dictionary::~Dictionary() {
	for (int i = 0; i < MAX_SIZE; i++) {
		Node* current = items[i];
		while (current != nullptr) {
			Node* temp = current;

			current = current->next;
			delete temp;
		}
	}
	size = 0;
}

int Dictionary::hash(KeyType key) {
	return key % MAX_SIZE;
}

bool Dictionary::add(KeyType newKey, ItemType newItem) {
	int hashValue = hash(newKey);

	Node* newNode = new Node;
	newNode->key = newKey;
	newNode->item = newItem;
	newNode->next = nullptr;

	if (items[hashValue] == NULL) {
		items[hashValue] = newNode;
	}

	else {
		Node* current = items[hashValue];
		Node* prev = nullptr;  // Track the previous node

		while (current != nullptr) {
			if (current->key == newKey) {
				return false;  // Duplicate key found
			}
			prev = current;   // Update the previous node
			current = current->next;
		}

		prev->next = newNode;
	}
	size++;
	return true;
}

void Dictionary::remove(KeyType key) {
	int hashValue = hash(key);

	if (items[hashValue] != nullptr) {
		Node* current = items[hashValue];

		//if item to be remove is the first node 
		if (current->key == key) {
			items[hashValue] = current->next;
			delete current;
			size--;
			return;
		}

		else {
			while (current->next != nullptr) {
				if (current->next && current->next->key == key) {
					Node* temp = current->next;

					current->next = current->next->next;
					delete temp;
					size--;
					return;
				}
				current = current->next;
			}
		}
	}
}

ItemType Dictionary::get(KeyType key) {
	int hashValue = hash(key);
	Node* current = items[hashValue];
	while (current != nullptr) {
		if (current->key == key) {
			return current->item;
		}
		current = current->next;
	}
}

bool Dictionary::isEmpty() {
	return size == 0;
}

int Dictionary::getLength() {
	return size;
}

void Dictionary::print() {
	for (int i = 0; i < MAX_SIZE; i++) {
		Node* current = items[i];
		while (current != nullptr) {
			cout << current->key << " : " << current->item.getName() << endl;
			current = current->next;
		}
	}
}