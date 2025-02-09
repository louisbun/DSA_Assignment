#pragma once

#include<iostream>
using namespace std;
#include "BinaryNode.h"
#include "ArrayList.h"
class BST
{
private:
	BinaryNode* root;		// root of the BST

	

public:
	// constructor
	BST();

	// search an item in the binary search tree
	BinaryNode* search(int id);
	BinaryNode* search(BinaryNode* root, int id);

	// insert an item to the binary search tree
	void insert(ItemType item);
	void insert(BinaryNode*& root, ItemType item);


	// traverse the binary search tree in inorder
	void displaySorted();
	void inorder(BinaryNode* t);

	// Update an actor's details
	void updateActor(int id, string newName, int newBirth);

	//Display in ascending order of age
	void displayActorsByAgeRange(int minAge, int maxAge);
	void collectActorsInRange(BinaryNode* node, int minBirth, int maxBirth, BinaryNode* actors[], int& count);
	void sortActorsByAge(BinaryNode* actors[], int count);
	
	//collecting the actors into the ArrayList to be displayed alphabetically
	void getActorsInList(ArrayList<Actor>& actors);
	void inOrderTraversal(BinaryNode* node, ArrayList<Actor>& actors);

	void displayActorsByRating();
	void collectAllActors(BinaryNode* node, ArrayList<Actor>& temp);

	
};
