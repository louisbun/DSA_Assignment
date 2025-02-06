#include "BST.h"
#include <iostream>

using namespace std;

// Constructor
BST::BST() {
    root = nullptr;
}

// Insert an actor into the BST
void BST::insert(ItemType item) {
    insert(root, item);
}

void BST::insert(BinaryNode*& node, ItemType item) {
    if (!node) {
        node = new BinaryNode(item);
        return;
    }

    if (item.getId() < node->item.getId()) {
        insert(node->left, item);
    }
    else {
        insert(node->right, item);
    }
}

// Inorder traversal (sorted by ID)
void BST::displaySorted() {
    inorder(root);
}

void BST::inorder(BinaryNode* node) {
    if (node) {
        inorder(node->left);
        cout << "ID: " << node->item.getId()
            << " | Name: " << node->item.getName()
            << " | Birth Year: " << node->item.getBirth() << endl;
        inorder(node->right);
    }
}

// Search for an actor by ID
BinaryNode* BST::search(int id) {
    return search(root, id);
}

BinaryNode* BST::search(BinaryNode* node, int id) {
    if (!node || node->item.getId() == id) return node;
    if (id < node->item.getId()) return search(node->left, id);
    return search(node->right, id);
}

// Update an actor's details
void BST::updateActor(int id, string newName, int newBirth) {
    BinaryNode* actorNode = search(id);
    if (!actorNode) {
        cout << "Actor not found.\n";
        return;
    }

    if (!newName.empty()) actorNode->item.setName(newName);
    if (newBirth != -1) actorNode->item.setBirth(newBirth);

    cout << "Actor updated successfully!\n";
}

// Collect actors in an array based on birth year range
void BST::collectActorsInRange(BinaryNode* node, int minBirth, int maxBirth, BinaryNode* actors[], int& count) {
    if (!node) return;

    collectActorsInRange(node->left, minBirth, maxBirth, actors, count);

    if (node->item.getBirth() >= minBirth && node->item.getBirth() <= maxBirth) {
        actors[count++] = node;  // Store BinaryNode in array
    }

    collectActorsInRange(node->right, minBirth, maxBirth, actors, count);
}

// Sort actors by birth year using Bubble Sort
void BST::sortActorsByAge(BinaryNode* actors[], int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (actors[j]->item.getBirth() > actors[j + 1]->item.getBirth()) {
                BinaryNode* temp = actors[j];
                actors[j] = actors[j + 1];
                actors[j + 1] = temp;
            }
        }
    }
}

// Display actors in a given age range (sorted by age)
void BST::displayActorsByAgeRange(int minAge, int maxAge) {
    int currentYear = 2024;
    int minBirth = currentYear - maxAge;
    int maxBirth = currentYear - minAge;

    const int MAX_ACTORS = 15000;  // Assume max 15000 actors
    BinaryNode* actors[MAX_ACTORS];
    int count = 0;

    collectActorsInRange(root, minBirth, maxBirth, actors, count);
    sortActorsByAge(actors, count);

    cout << "Actors born between " << minBirth << " and " << maxBirth << " (sorted by age):\n";
    for (int i = 0; i < count; i++) {
        cout << "ID: " << actors[i]->item.getId()
            << " | Name: " << actors[i]->item.getName()
            << " | Birth Year: " << actors[i]->item.getBirth() << endl;
    }
}
