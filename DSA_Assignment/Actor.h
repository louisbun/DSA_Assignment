#pragma once
#include <iostream>
using namespace std;

class Actor
{
private:
	// attributes
	int id;
	string name;
	int birth;
	Actor* left;
	Actor* right; 

public:
	// getters and setters
	int getId();
	string getName();
	int getBirth();

	void setId(int id);
	void setName(string name);
	void setBirth(int birth);

	// Public BST Pointers
	Actor* getLeft();
	Actor* getRight();
	void setLeft(Actor* node);
	void setRight(Actor* node);

	// constructors
	Actor();
	Actor(int id, string name, int birth);

	// methods

};