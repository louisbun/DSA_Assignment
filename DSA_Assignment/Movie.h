#pragma once
#include <iostream>
using namespace std;

class Movie
{
	// atributes
private:
	int id;
	string title;
	string plot;
	int year;

public:
	// getters and setters
	int getId();
	string getTitle();
	string getPlot();
	int getYear();

	void setId(int id);
	void setTitle(string title);
	void setPlot(string plot);
	void setYear(int year);

	// constructors
	Movie();
	Movie(int id, string title, string plot, int year);

	//methods


};

