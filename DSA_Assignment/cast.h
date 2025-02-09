#pragma once
#include <iostream>
#include "BST.h"
#include "BinaryNode.h"
#include "List.h"

using namespace std;


struct MovieNode {
    int movieID;
    MovieNode* next;
    MovieNode(int id) : movieID(id), next(nullptr) {}
};


struct ActorNode {
    BinaryNode* actor;
    ActorNode* next;
    ActorNode(BinaryNode* actorNode) : actor(actorNode), next(nullptr) {}
};


struct ActorMovieList {
    BinaryNode* actor;
    MovieNode* movieHead;
    ActorMovieList* next;
    ActorMovieList(BinaryNode* actorNode) : actor(actorNode), movieHead(nullptr), next(nullptr) {}
};


struct MovieActorList {
    int movieID;
    ActorNode* actorHead;
    MovieActorList* next;
    MovieActorList(int id) : movieID(id), actorHead(nullptr), next(nullptr) {}
};


class Cast {
private:
    ActorMovieList* actorMovieHead; // Stores actors & their movies
    MovieActorList* movieActorHead; // Stores movies & their actors

public:
    Cast();

    // Add an actor-movie relationship
    // pre : actor is a valid BinaryNode pointer, movieID is a valid integer
    // post: updates actorMovieHead and movieActorHead to include the new relationship
    void addActorToMovie(BinaryNode* actor, int movieID);

    // Display all movies of a given actor
    // pre : actor is a valid BinaryNode pointer, movieList contains valid movies
    // post: prints all movies associated with the given actor in sorted order
    void displayMoviesByActor(BinaryNode* actor, List<Movie>& movieList);

    // Display all actors in a movie
    // pre : movieID is a valid integer
    // post: prints all actors associated with the given movie
    void displayActorsByMovie(int movieID);

    // Display all actors that a particular actor knows
    // pre : actor is a valid BinaryNode pointer, actorTree contains all actors
    // post: prints a list of actors the given actor has worked with
    void displayKnownActors(BinaryNode* actor, BST& actorTree);
};

