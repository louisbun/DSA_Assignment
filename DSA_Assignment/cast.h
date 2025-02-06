//#pragma once
//#include <iostream>
//using namespace std;
//#include "ActorBST.h"
//
//// Linked list node for storing movie IDs
//struct MovieNode {
//    int movieID;
//    MovieNode* next;
//    MovieNode(int id) : movieID(id), next(nullptr) {}
//};
//
//// Linked list node for storing actor IDs
//struct ActorNode {
//    int actorID;
//    ActorNode* next;
//    ActorNode(int id) : actorID(id), next(nullptr) {}
//};
//
//// Linked list for storing all movies an actor has acted in
//struct ActorMovieList {
//    int actorID;
//    MovieNode* movieHead;
//    ActorMovieList* next;
//    ActorMovieList(int id) : actorID(id), movieHead(nullptr), next(nullptr) {}
//};
//
//// Linked list for storing all actors in a movie
//struct MovieActorList {
//    int movieID;
//    ActorNode* actorHead;
//    MovieActorList* next;
//    MovieActorList(int id) : movieID(id), actorHead(nullptr), next(nullptr) {}
//};
//
//// Class to manage actor-movie relationships
//class Cast {
//private:
//    ActorMovieList* actorMovieHead; // Stores actors & their movies
//    MovieActorList* movieActorHead; // Stores movies & their actors
//
//public:
//    Cast();
//    void addActorToMovie(int actorID, int movieID);
//    void displayMoviesByActor(int actorID);
//    void displayActorsByMovie(int movieID);
//    void displayKnownActors(int actorID, ActorBST& actorTree);
//};

#pragma once
#include <iostream>
#include "BST.h"
#include "BinaryNode.h"

using namespace std;

// Linked list node for storing movie IDs
struct MovieNode {
    int movieID;
    MovieNode* next;
    MovieNode(int id) : movieID(id), next(nullptr) {}
};

// Linked list node for storing actors (BinaryNode* instead of actorID)
struct ActorNode {
    BinaryNode* actor;
    ActorNode* next;
    ActorNode(BinaryNode* actorNode) : actor(actorNode), next(nullptr) {}
};

// Linked list for storing all movies an actor has acted in
struct ActorMovieList {
    BinaryNode* actor;
    MovieNode* movieHead;
    ActorMovieList* next;
    ActorMovieList(BinaryNode* actorNode) : actor(actorNode), movieHead(nullptr), next(nullptr) {}
};

// Linked list for storing all actors in a movie
struct MovieActorList {
    int movieID;
    ActorNode* actorHead;
    MovieActorList* next;
    MovieActorList(int id) : movieID(id), actorHead(nullptr), next(nullptr) {}
};

// Class to manage actor-movie relationships
class Cast {
private:
    ActorMovieList* actorMovieHead; // Stores actors & their movies
    MovieActorList* movieActorHead; // Stores movies & their actors

public:
    Cast();
    void addActorToMovie(BinaryNode* actor, int movieID);
    void displayMoviesByActor(BinaryNode* actor);
    void displayActorsByMovie(int movieID);
    void displayKnownActors(BinaryNode* actor, BST& actorTree);
};

