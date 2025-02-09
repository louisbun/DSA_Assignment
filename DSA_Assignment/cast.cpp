#include "cast.h"

// Constructor
Cast::Cast() {
    actorMovieHead = nullptr;
    movieActorHead = nullptr;
}

// function to find an actor in actorMovieHead
// pre : actor is a valid BinaryNode pointer, head points to the start of the list
// post: none
// return: pointer to the ActorMovieList entry if found, otherwise nullptr
ActorMovieList* findActor(BinaryNode* actor, ActorMovieList*& head) {
    ActorMovieList* temp = head;
    while (temp) {
        if (temp->actor == actor) 
            return temp;
        temp = temp->next;
    }
    return nullptr;
}

// function to find a movie in movieActorHead
// pre : movieID is a valid integer, head points to the start of the list
// post: none
// return: pointer to the MovieActorList entry if found, otherwise nullptr
MovieActorList* findMovie(int movieID, MovieActorList*& head) {
    MovieActorList* temp = head;
    while (temp) {
        if (temp->movieID == movieID) return temp;
        temp = temp->next;
    }
    return nullptr;
}

// Add an actor-movie relationship
// pre : actor is a valid BinaryNode pointer, movieID is a valid integer
// post: updates actorMovieHead and movieActorHead to include the new relationship
void Cast::addActorToMovie(BinaryNode* actor, int movieID) {
    if (!actor) return; // Prevent inserting null actors

    // Add movie to actor's list
    ActorMovieList* actorEntry = findActor(actor, actorMovieHead);
    if (!actorEntry) {
        actorEntry = new ActorMovieList(actor);
        actorEntry->next = actorMovieHead;
        actorMovieHead = actorEntry;
    }

    // Insert movie ID in actor's movie list
    MovieNode* newMovie = new MovieNode(movieID);
    newMovie->next = actorEntry->movieHead;
    actorEntry->movieHead = newMovie;

    // Add actor to movie's list
    MovieActorList* movieEntry = findMovie(movieID, movieActorHead);
    if (!movieEntry) {
        movieEntry = new MovieActorList(movieID);
        movieEntry->next = movieActorHead;
        movieActorHead = movieEntry;
    }

    // Insert actor in movie's actor list
    ActorNode* newActor = new ActorNode(actor);
    newActor->next = movieEntry->actorHead;
    movieEntry->actorHead = newActor;
}

// Display all movies of a given actor
// pre : actor is a valid BinaryNode pointer, movieList contains valid movies
// post: prints all movies associated with the given actor in sorted order
void Cast::displayMoviesByActor(BinaryNode* actor, List<Movie>& movieList) {
    if (!actor) {
        cout << "Actor not found.\n";
        return;
    }

    ActorMovieList* actorEntry = findActor(actor, actorMovieHead);
    if (!actorEntry) {
        cout << actor->item.getName() << " has no movies.\n";
        return;
    }

    List<Movie> movieTemp; 
    MovieNode* temp = actorEntry->movieHead;

    while (temp) {
        int index = movieList.search(temp->movieID);
        if (index != -1) {  
            movieTemp.add(movieList.get(index));  
        }
        temp = temp->next;
    }

    // Sort movies by title
    movieTemp.mergeSortByName();

    // Display sorted movies
    cout << "Movies starred in by " << actor->item.getName() << ":\n";
    for (int i = 0; i < movieTemp.getLength(); i++) {
        Movie movie = movieTemp.get(i);
        cout << "- Movie ID: " << movie.getId() << "\tTitle: " << movie.getTitle() << endl;
    }
}


// Display all actors in a movie
// pre : movieID is a valid integer
// post: prints all actors associated with the given movie
void Cast::displayActorsByMovie(int movieID) {
    MovieActorList* movieEntry = findMovie(movieID, movieActorHead);
    if (!movieEntry) {
        cout << "Movie not found or has no actors.\n";
        return;
    }

    cout << "Actors in Movie ID " << movieID << ":\n";
    ActorNode* temp = movieEntry->actorHead;
    while (temp) {
        cout << "- " << temp->actor->item.getName() << " (ID: " << temp->actor->item.getId() << ")\n";
        temp = temp->next;
    }
}

// Display all actors that a particular actor knows
// pre : actor is a valid BinaryNode pointer, actorTree contains all actors
// post: prints a list of actors the given actor has worked with
void Cast::displayKnownActors(BinaryNode* actor, BST& actorTree) {
    if (!actor) {
        cout << "Actor not found.\n";
        return;
    }

    string mainActorName = actor->item.getName();
    cout << "Actors known by " << mainActorName << ":\n";

    struct KnownActorNode {
        BinaryNode* actor;
        KnownActorNode* next;
        KnownActorNode(BinaryNode* act) : actor(act), next(nullptr) {}
    };

    KnownActorNode* knownActors = nullptr;

    // Collect direct connections
    ActorMovieList* actorEntry = findActor(actor, actorMovieHead);
    if (!actorEntry) {
        cout << mainActorName << " has no known connections.\n";
        return;
    }

    for (MovieNode* movie = actorEntry->movieHead; movie; movie = movie->next) {
        MovieActorList* movieEntry = findMovie(movie->movieID, movieActorHead);
        for (ActorNode* coActor = movieEntry->actorHead; coActor; coActor = coActor->next) {
            if (coActor->actor != actor) {
                // Check if already in the list
                KnownActorNode* temp = knownActors;
                bool exists = false;
                while (temp) {
                    if (temp->actor == coActor->actor) {
                        exists = true;
                        break;
                    }
                    temp = temp->next;
                }
                if (!exists) {
                    KnownActorNode* newNode = new KnownActorNode(coActor->actor);
                    newNode->next = knownActors;
                    knownActors = newNode;
                }
            }
        }
    }

    // combine list
    for (KnownActorNode* temp = knownActors; temp; temp = temp->next) {
        cout << "- " << temp->actor->item.getName() << " (ID: " << temp->actor->item.getId() << ")\n";
    }
    while (knownActors) {
        KnownActorNode* temp = knownActors;
        knownActors = knownActors->next;
        delete temp;
    }
}

