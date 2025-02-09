#pragma once
#include<iostream>
#include "Actor.h"
#include "Movie.h"
using namespace std;

const int MAX_SIZE2 = 101;
typedef int KeyType;
typedef Actor ItemType;
typedef Movie ItemType2;

struct Node
{
	KeyType	 key;   // search key
	ItemType2 item;	// data item
	Node* next;	// pointer pointing to next item with same search key
};

class Dictionary
{
private:

	Node* items[MAX_SIZE2];
	int  size;			// number of items in the Dictionary

public:

	// constructor
	Dictionary();

	// destructor
	~Dictionary();

	int hash(KeyType key);

	// add a new item with the specified key to the Dictionary
	// pre : none
	// post: new item is added to the Dictionary
	//       size of Dictionary is increased by 1
	bool add(KeyType newKey, ItemType2 newItem);

	// remove an item with the specified key in the Dictionary
	// pre : key must exist in the Dictionary
	// post: item is removed from the Dictionary
	//       size of Dictionary is decreased by 1
	void remove(KeyType key);


	// get an item with the specified key in the Dictionary (retrieve)
	// pre : key must exist in the dictionary
	// post: none
	// return the item with the specified key from the Dictionary
	ItemType2 get(KeyType key);
	ItemType2& getReference(KeyType key);

	// check if the Dictionary is empty
	// pre : none
	// post: none
	// return true if the Dictionary is empty; otherwise returns false
	bool isEmpty();

	// check the size of the Dictionary
	// pre : none
	// post: none
	// return the number of items in the Dictionary
	int getLength();

	//------------------- Other useful functions -----------------

	// display the items in the Dictionary
	void print();

	// void replace(KeyType key, ItemType item);
	// bool contains(KeyType key);

};

