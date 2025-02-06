#pragma once
#include "Actor.h"

typedef Actor ItemType;
struct BinaryNode
{
	ItemType item;	      // data item
	BinaryNode* left;	// pointer pointing to left subtree
	BinaryNode* right;   // pointer pointing to right subtree

	// Constructor to initialize the node with an item
	BinaryNode(const ItemType& newItem)
		: item(newItem), left(nullptr), right(nullptr) {}
};
