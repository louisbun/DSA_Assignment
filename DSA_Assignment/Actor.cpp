#include "Actor.h"

Actor::Actor() {
    id = 0;
    name = "unknown";
    birth = 0;
    left = right = nullptr;
}

Actor::Actor(int id, string name, int birth) {
    this->id = id;
    this->name = name;
    this->birth = birth;
    left = right = nullptr;
}

int Actor::getId() { return id; }
string Actor::getName() { return name; }
int Actor::getBirth() { return birth; }

void Actor::setId(int id) { this->id = id; }
void Actor::setName(string name) { this->name = name; }
void Actor::setBirth(int birth) { this->birth = birth; }

// BST Pointer Methods
Actor* Actor::getLeft() { return left; }
Actor* Actor::getRight() { return right; }
void Actor::setLeft(Actor* node) { left = node; }
void Actor::setRight(Actor* node) { right = node; }