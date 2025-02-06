#pragma once
#include "Actor.h"

class ActorBST {
private:
    Actor* root;

    // Helper functions
    Actor* insert(Actor* node, int id, string name, int birth);
    void inorder(Actor* node);
    Actor* search(Actor* node, int id);

public:
    ActorBST();
    void insert(int id, string name, int birth);
    void displaySorted();
    Actor* search(int id);
    void updateActor(int id, string newName, int newBirth);
    void displayActorsByAgeRange(int minAge, int maxAge);

};
