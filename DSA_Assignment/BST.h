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
	// pre : BST is not empty
	// post: none
	// return: pointer to the BinaryNode containing the actor with the given ID
	BinaryNode* search(int id);
	BinaryNode* search(BinaryNode* root, int id);

	// Insert an actor into the BST
	// pre : item contains valid actor data
	// post: item is inserted into the BST in the correct position
	void insert(ItemType item);
	void insert(BinaryNode*& root, ItemType item);


	// Inorder traversal (sorted by ID)
	// pre : BST is not empty
	// post: prints all actors in ascending order of ID
	void displaySorted();
	void inorder(BinaryNode* t);

	// Update an actor's details
	// pre : BST contains the actor with the given ID
	// post: updates the actor's name and birth year if provided
	void updateActor(int id, string newName, int newBirth);

	//Display in ascending order of age
	// pre : BST is not empty, minBirth and maxBirth are valid
	// post: stores actors within the birth year range in the provided array
	void displayActorsByAgeRange(int minAge, int maxAge);
	void collectActorsInRange(BinaryNode* node, int minBirth, int maxBirth, BinaryNode* actors[], int& count);
	void sortActorsByAge(BinaryNode* actors[], int count);
	
	//collecting the actors into the ArrayList to be displayed alphabetically
	// pre : BST is not empty
	// post: stores all actors in the provided ArrayList
	void getActorsInList(ArrayList<Actor>& actors);
	void inOrderTraversal(BinaryNode* node, ArrayList<Actor>& actors);

	// Display top 5 highest-rated actors
	// pre : BST is not empty
	// post: prints the top 5 actors sorted by rating in descending order
	void displayActorsByRating();
	void collectAllActors(BinaryNode* node, ArrayList<Actor>& temp);

	
};
