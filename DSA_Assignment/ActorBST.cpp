#include "ActorBST.h"
#include <iostream>

using namespace std;

ActorBST::ActorBST() {
    root = nullptr;
}

Actor* ActorBST::insert(Actor* node, int id, string name, int birth) {
    if (!node) return new Actor(id, name, birth);
    if (id < node->getId()) {
        node->setLeft(insert(node->getLeft(), id, name, birth));
    }
    else {
        node->setRight(insert(node->getRight(), id, name, birth));
    }
    return node;
}

void ActorBST::insert(int id, string name, int birth) {
    root = insert(root, id, name, birth);
}

void ActorBST::inorder(Actor* node) {
    if (node) {
        inorder(node->getLeft());
        cout << node->getId() << " - " << node->getName() << " (" << node->getBirth() << ")\n";
        inorder(node->getRight());
    }
}

void ActorBST::displaySorted() {
    inorder(root);
}

Actor* ActorBST::search(Actor* node, int id) {
    if (!node || node->getId() == id) return node;
    if (id < node->getId()) return search(node->getLeft(), id);
    return search(node->getRight(), id);
}

Actor* ActorBST::search(int id) {
    return search(root, id);
}

void ActorBST::updateActor(int id, string newName, int newBirth) {
    Actor* actor = search(id);
    if (!actor) {
        cout << "Actor not found.\n";
        return;
    }

    if (!newName.empty()) actor->setName(newName);
    if (newBirth != -1) actor->setBirth(newBirth);

    cout << "Actor updated successfully!\n";
}

//void displayActorsByAgeRangeHelper(Actor* node, int minBirth, int maxBirth) {
//    if (!node) return;
//
//    displayActorsByAgeRangeHelper(node->getLeft(), minBirth, maxBirth);
//
//    if (node->getBirth() >= minBirth && node->getBirth() <= maxBirth) {
//        cout << "ID: " << node->getId()
//            << " | Name: " << node->getName()
//            << " | Birth Year: " << node->getBirth() << endl;
//    }
//
//    displayActorsByAgeRangeHelper(node->getRight(), minBirth, maxBirth);
//}
//
//void ActorBST::displayActorsByAgeRange(int minAge, int maxAge) {
//    int currentYear = 2024;
//    int minBirth = currentYear - maxAge;
//    int maxBirth = currentYear - minAge;
//
//    cout << "Actors born between " << minBirth << " and " << maxBirth << ":\n";
//    displayActorsByAgeRangeHelper(root, minBirth, maxBirth);
//}

// Helper function to collect actors in an array (instead of printing immediately)
void collectActorsInRange(Actor* node, int minBirth, int maxBirth, Actor* actors[], int& count) {
    if (!node) return;

    collectActorsInRange(node->getLeft(), minBirth, maxBirth, actors, count);

    if (node->getBirth() >= minBirth && node->getBirth() <= maxBirth) {
        actors[count++] = node;  // Store actor in array
    }

    collectActorsInRange(node->getRight(), minBirth, maxBirth, actors, count);
}

// Helper function to sort actors by birth year (bubble sort)
void sortActorsByAge(Actor* actors[], int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (actors[j]->getBirth() > actors[j + 1]->getBirth()) {
                Actor* temp = actors[j];
                actors[j] = actors[j + 1];
                actors[j + 1] = temp;
            }
        }
    }
}

// Function to display actors in a given age range (sorted by age)
void ActorBST::displayActorsByAgeRange(int minAge, int maxAge) {
    int currentYear = 2024;
    int minBirth = currentYear - maxAge;
    int maxBirth = currentYear - minAge;

    const int MAX_ACTORS = 15000;  // Assume max 15000 actors
    Actor* actors[MAX_ACTORS];
    int count = 0;

    collectActorsInRange(root, minBirth, maxBirth, actors, count);
    sortActorsByAge(actors, count);

    cout << "Actors born between " << minBirth << " and " << maxBirth << " (sorted by age):\n";
    for (int i = 0; i < count; i++) {
        cout << "ID: " << actors[i]->getId()
            << " | Name: " << actors[i]->getName()
            << " | Birth Year: " << actors[i]->getBirth() << endl;
    }
}