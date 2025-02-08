#include "Movie.h"

Movie::Movie() {
	id = 0;
	title = "unknown";
	plot = "unknown";
	year = 0;
	rating = 0;
	ratingCount = 0;
	totalRating = 0;
}

Movie::Movie(int id, string title, string plot, int year) {
	this->id = id;
	this->title = title;
	this->plot = plot;
	this->year = year;
	rating = 0;
	ratingCount = 0;
	totalRating = 0;
}

int Movie::getId() { return id; }
string Movie::getTitle() { return title; }
string Movie::getPlot() { return plot; }
int Movie::getYear() { return year; }
BST& Movie::getActors() { return actors; }
float Movie::getRating() { return rating; }
float Movie::getTotalRating() { return totalRating; }
int Movie::getRatingCount() { return ratingCount; }

void Movie::setId(int id) { this->id = id; }
void Movie::setTitle(string title) { this->title = title; }
void Movie::setPlot(string plot) { this->plot = plot; }
void Movie::setYear(int year) { this->year = year; }

//rating method
void Movie::addRating(float newRating) {

	totalRating += newRating;
	ratingCount++;

	// Update the average rating
	rating = totalRating / ratingCount;
}