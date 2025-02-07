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
T& List<T>::getReference(int index) {
	if (index < 0 || index >= size) {
		throw out_of_range("Index out of bounds");  // error handling
	}

	Node* current = firstNode;
	for (int i = 0; i < index; i++) {
		current = current->next;
	}
	return current->item;
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

template<class T>
void List<T>::replace(int index, T item) {
	if (index < 0 || index >= size) {
		cout << "Invalid index!" << endl;
		return;
	}

	Node* current = firstNode;
	for (int i = 0; i < index; i++) {
		current = current->next;
	}

	current->item = item;  // Replace the item at the given index
}


template<class T>
void List<T>::mergeSort() {
	firstNode = mergeSort(firstNode); 
}

template<class T>
struct List<T>::Node* List<T>::mergeSort(Node* head) {
	if (head == nullptr || head->next == nullptr) {
		return head;  // Base case: single element or empty list is already sorted
	}

	// Step 1: Split the list into two halves
	Node* mid = getMiddle(head);
	Node* left = head;
	Node* right = mid->next;
	mid->next = nullptr;  // Split the list

	// Step 2: Recursively sort the two halves
	left = mergeSort(left);
	right = mergeSort(right);

	// Step 3: Merge the two sorted halves
	return merge(left, right);
}

// Helper function to find the middle of the list
template<class T>
struct List<T>::Node* List<T>::getMiddle(Node* head) {
	if (head == nullptr) {
		return nullptr;
	}

	Node* slow = head;
	Node* fast = head;

	// Move fast by 2 and slow by 1
	while (fast->next != nullptr && fast->next->next != nullptr) {
		fast = fast->next->next;
		slow = slow->next;
	}

	return slow;
}

// Merge two sorted lists into one sorted list
template<class T>
struct List<T>::Node* List<T>::merge(Node* left, Node* right) {
	if (left == nullptr) return right;
	if (right == nullptr) return left;

	Node* mergedHead = nullptr;

	// Compare nodes and merge
	if (left->item.getYear() < right->item.getYear()) {
		mergedHead = left;
		mergedHead->next = merge(left->next, right);
	}
	else {
		mergedHead = right;
		mergedHead->next = merge(left, right->next);
	}

	return mergedHead;
}