//#pragma once
//#include <iostream>
//#include <vector>
//#include <unordered_map>
//#include <set>
//using namespace std;
//
//class Cast {
//private:
//    unordered_map<int, vector<int>> actorToMovies; // Maps actor_id → list of movie_ids
//    unordered_map<int, vector<int>> movieToActors; // Maps movie_id → list of actor_ids
//
//public:
//    // Insert relationship between actor and movie
//    void addActorToMovie(int actorID, int movieID);
//
//    // Display all movies an actor starred in (sorted alphabetically)
//    void displayMoviesByActor(int actorID);
//
//    // Display all actors in a movie (sorted alphabetically)
//    void displayActorsByMovie(int movieID);
//
//    // Display all actors that a particular actor knows
//    void displayKnownActors(int actorID);
//};

#pragma once
#include <iostream>
using namespace std;
#include "ActorBST.h"

// Linked list node for storing movie IDs
struct MovieNode {
    int movieID;
    MovieNode* next;
    MovieNode(int id) : movieID(id), next(nullptr) {}
};

// Linked list node for storing actor IDs
struct ActorNode {
    int actorID;
    ActorNode* next;
    ActorNode(int id) : actorID(id), next(nullptr) {}
};

// Linked list for storing all movies an actor has acted in
struct ActorMovieList {
    int actorID;
    MovieNode* movieHead;
    ActorMovieList* next;
    ActorMovieList(int id) : actorID(id), movieHead(nullptr), next(nullptr) {}
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
    void addActorToMovie(int actorID, int movieID);
    void displayMoviesByActor(int actorID);
    void displayActorsByMovie(int movieID);
    void displayKnownActors(int actorID, ActorBST& actorTree);
};
