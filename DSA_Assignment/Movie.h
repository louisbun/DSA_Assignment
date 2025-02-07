#pragma once
#include <iostream>
#include "BST.h"
using namespace std;

class Movie
{
	// atributes
private:
	int id;
	string title;
	string plot;
	int year;
	BST actors;

public:
	// getters and setters
	int getId();
	string getTitle();
	string getPlot();
	int getYear();
	BST& getActors();

	void setId(int id);
	void setTitle(string title);
	void setPlot(string plot);
	void setYear(int year);

	// constructors
	Movie();
	Movie(int id, string title, string plot, int year);

	//methods


};

