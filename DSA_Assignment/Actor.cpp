#include "Actor.h"

Actor::Actor() {
    id = 0;
    name = "unknown";
    birth = 0;
    rating = 0;
    ratingCount = 0;
    totalRating = 0;
}

Actor::Actor(int id, string name, int birth) {
    this->id = id;
    this->name = name;
    this->birth = birth;
    rating = 0;
    ratingCount = 0;
    totalRating = 0;
}

int Actor::getId() { return id; }
string Actor::getName() { return name; }
int Actor::getBirth() { return birth; }
float Actor::getRating() { return rating; }
float Actor::getTotalRating() { return totalRating; }
int Actor::getRatingCount() { return ratingCount; }

void Actor::setId(int id) { this->id = id; }
void Actor::setName(string name) { this->name = name; }
void Actor::setBirth(int birth) { this->birth = birth; }


//rating method
void Actor::addRating(float newRating) {

    totalRating += newRating;
    ratingCount++;

    // Update the average rating
    rating = totalRating / ratingCount;
}

