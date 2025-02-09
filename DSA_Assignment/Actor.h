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
	float rating;
	float totalRating;
	int ratingCount;

public:
	// getters and setters
	int getId();
	string getName();
	int getBirth();
	float getRating();
	float getTotalRating();
	int getRatingCount();

	void setId(int id);
	void setName(string name);
	void setBirth(int birth);


	// constructors
	Actor();
	Actor(int id, string name, int birth);

	// methods
	void addRating(float newRating);
};