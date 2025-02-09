#include "BST.h"
#include <iostream>

using namespace std;

// Constructor
BST::BST() {
    root = nullptr;
}

// Insert an actor into the BST
// pre : item contains valid actor data
// post: item is inserted into the BST in the correct position
void BST::insert(ItemType item) {
    insert(root, item);
}
//Helper function
// pre : item contains valid actor data, node may be nullptr
// post: inserts the item into the BST while maintaining BST properties
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
// pre : BST is not empty
// post: prints all actors in ascending order of ID
void BST::displaySorted() {
    inorder(root);
}

// Helper function for inorder traversal
// pre : node is not nullptr
// post: prints the actor's ID, name, and birth year in sorted order
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
// pre : BST is not empty
// post: none
// return: pointer to the BinaryNode containing the actor with the given ID
BinaryNode* BST::search(int id) {
    return search(root, id);
}

// Helper function for searching
// pre : BST is not empty, node may be nullptr
// post: none
// return: pointer to the BinaryNode containing the actor with the given ID
BinaryNode* BST::search(BinaryNode* node, int id) {
    if (!node || node->item.getId() == id) return node;
    if (id < node->item.getId()) return search(node->left, id);
    return search(node->right, id);
}

// Update an actor's details
// pre : BST contains the actor with the given ID
// post: updates the actor's name and birth year if provided
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
// pre : BST is not empty, minBirth and maxBirth are valid
// post: stores actors within the birth year range in the provided array
void BST::collectActorsInRange(BinaryNode* node, int minBirth, int maxBirth, BinaryNode* actors[], int& count) {
    if (!node) return;

    collectActorsInRange(node->left, minBirth, maxBirth, actors, count);

    if (node->item.getBirth() >= minBirth && node->item.getBirth() <= maxBirth) {
        actors[count++] = node; 
    }

    collectActorsInRange(node->right, minBirth, maxBirth, actors, count);
}


// Collect all actors with a rating greater than 0 into an ArrayList
// pre : BST is not empty
// post: stores all actors with a rating > 0 in the provided ArrayList
void BST::collectAllActors(BinaryNode* node, ArrayList<Actor>& temp)
{
    if (!node) return;
    collectAllActors(node->left, temp);
    // Check if actor's rating is greater than 0 before adding
    if (node->item.getRating() > 0) {
        temp.add(node->item);  // Add the actor to the arrayList
    }
    collectAllActors(node->right, temp);
}

// Display top 5 highest-rated actors
// pre : BST is not empty
// post: prints the top 5 actors sorted by rating in descending order
void BST::displayActorsByRating()
{
    ArrayList<Actor> temp;
    // Collect all actors into the array
    collectAllActors(root, temp);

    // Sort the array by rating (descending order)
    temp.mergeSortRating();

    // Print top 5 highest-rated actors
    cout << "Top 5 Highest Rated Actors:\n";
    for (int i = 0; i < 5 && temp.get(i).getRating() != 0; i++) {
        cout << "ID: " << temp.get(i).getId()
            << " | Name: " << temp.get(i).getName()
            << " | Rating: " << temp.get(i).getRating() << endl;
    }  
}


// Merge function for Merge Sort
// pre : actors array is divided into two sorted halves
// post: merges the two halves into a sorted array based on birth year
void merge(BinaryNode* actors[], int left, int mid, int right) {
    int leftSize = mid - left + 1;
    int rightSize = right - mid;

    BinaryNode** leftArr = new BinaryNode * [leftSize];
    BinaryNode** rightArr = new BinaryNode * [rightSize];


    for (int i = 0; i < leftSize; i++)
        leftArr[i] = actors[left + i];
    for (int i = 0; i < rightSize; i++)
        rightArr[i] = actors[mid + 1 + i];

    int i = 0, j = 0, k = left;
    while (i < leftSize && j < rightSize) {
        if (leftArr[i]->item.getBirth() <= rightArr[j]->item.getBirth()) {
            actors[k] = leftArr[i];
            i++;
        }
        else {
            actors[k] = rightArr[j];
            j++;
        }
        k++;
    }

    while (i < leftSize) {
        actors[k] = leftArr[i];
        i++;
        k++;
    }

    while (j < rightSize) {
        actors[k] = rightArr[j];
        j++;
        k++;
    }

    delete[] leftArr;
    delete[] rightArr;
}

// Merge Sort function
// pre : actors array contains unsorted actors
// post: actors array is sorted by birth year in ascending order
void mergeSort(BinaryNode* actors[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(actors, left, mid);
        mergeSort(actors, mid + 1, right);
        merge(actors, left, mid, right);
    }
}

// pre : actors array contains unsorted actors
// post: actors array is sorted by birth year in ascending order
void BST::sortActorsByAge(BinaryNode* actors[], int count) {
    if (count > 1)
        mergeSort(actors, 0, count - 1);
}


// Display actors in a given age range (sorted by age)
// pre : minAge and maxAge are valid, BST is not empty
// post: prints actors born within the specified age range sorted by age
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

// Get all actors into an ArrayList
// pre : BST is not empty
// post: stores all actors in the provided ArrayList
void BST::getActorsInList(ArrayList<Actor>& actors) {
    inOrderTraversal(root, actors);
}

// pre : BST is not empty
// post: adds all actors to the provided ArrayList in sorted order
void BST::inOrderTraversal(BinaryNode* node, ArrayList<Actor>& actors) {
    if (node == nullptr) {
        return;
    }
    // Traverse left subtree
    inOrderTraversal(node->left, actors);
    // Add the current actor to the list
    actors.add(node->item);
    // Traverse right subtree
    inOrderTraversal(node->right, actors);
}