#include "Movie.h"

Movie::Movie() {
	id = 0;
	title = "unknown";
	plot = "unknown";
	year = 0;
}

Movie::Movie(int id, string title, string plot, int year) {
	this->id = id;
	this->title = title;
	this->plot = plot;
	this->year = year;
}

int Movie::getId() { return id; }
string Movie::getTitle() { return title; }
string Movie::getPlot() { return plot; }
int Movie::getYear() { return year; }

void Movie::setId(int id) { this->id = id; }
void Movie::setTitle(string title) { this->title = title; }
void Movie::setPlot(string plot) { this->plot = plot; }
void Movie::setYear(int year) { this->year = year; }
