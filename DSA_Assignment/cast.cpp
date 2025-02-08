//#include "cast.h"
//
//// Constructor
//Cast::Cast() {
//    actorMovieHead = nullptr;
//    movieActorHead = nullptr;
//}
//
//// Helper function to find an actor in actorMovieHead
//ActorMovieList* findActor(int actorID, ActorMovieList*& head) {
//    ActorMovieList* temp = head;
//    while (temp) {
//        if (temp->actorID == actorID) return temp;
//        temp = temp->next;
//    }
//    return nullptr;
//}
//
//// Helper function to find a movie in movieActorHead
//MovieActorList* findMovie(int movieID, MovieActorList*& head) {
//    MovieActorList* temp = head;
//    while (temp) {
//        if (temp->movieID == movieID) return temp;
//        temp = temp->next;
//    }
//    return nullptr;
//}
//
//// Add an actor-movie relationship
//void Cast::addActorToMovie(int actorID, int movieID) {
//    // Add movie to actor's list
//    ActorMovieList* actor = findActor(actorID, actorMovieHead);
//    if (!actor) {
//        actor = new ActorMovieList(actorID);
//        actor->next = actorMovieHead;
//        actorMovieHead = actor;
//    }
//
//    // Insert movie ID in actor's movie list
//    MovieNode* newMovie = new MovieNode(movieID);
//    newMovie->next = actor->movieHead;
//    actor->movieHead = newMovie;
//
//    // Add actor to movie's list
//    MovieActorList* movie = findMovie(movieID, movieActorHead);
//    if (!movie) {
//        movie = new MovieActorList(movieID);
//        movie->next = movieActorHead;
//        movieActorHead = movie;
//    }
//
//    // Insert actor ID in movie's actor list
//    ActorNode* newActor = new ActorNode(actorID);
//    newActor->next = movie->actorHead;
//    movie->actorHead = newActor;
//}
//
//// Display all movies an actor starred in
//void Cast::displayMoviesByActor(int actorID) {
//    ActorMovieList* actor = findActor(actorID, actorMovieHead);
//    if (!actor) {
//        cout << "Actor not found or has no movies.\n";
//        return;
//    }
//
//    cout << "Movies starred in:\n";
//    MovieNode* temp = actor->movieHead;
//    while (temp) {
//        cout << "- Movie ID: " << temp->movieID << endl;
//        temp = temp->next;
//    }
//}
//
//// Display all actors in a movie
//void Cast::displayActorsByMovie(int movieID) {
//    MovieActorList* movie = findMovie(movieID, movieActorHead);
//    if (!movie) {
//        cout << "Movie not found or has no actors.\n";
//        return;
//    }
//
//    cout << "Actors in Movie ID " << movieID << ":\n";
//    ActorNode* temp = movie->actorHead;
//    while (temp) {
//        cout << "- Actor ID: " << temp->actorID << endl;
//        temp = temp->next;
//    }
//}
//
//void Cast::displayKnownActors(int actorID, ActorBST& actorTree) {
//    Actor* mainActor = actorTree.search(actorID);
//    if (!mainActor) {
//        cout << "Actor not found.\n";
//        return;
//    }
//
//    string mainActorName = mainActor->getName();
//    cout << "Actors known by " << mainActorName << ":\n";
//
//    struct KnownActorNode {
//        int actorID;
//        KnownActorNode* next;
//        KnownActorNode(int id) : actorID(id), next(nullptr) {}
//    };
//
//    KnownActorNode* knownActors = nullptr;
//
//    // Collect first-level connections
//    ActorMovieList* actor = findActor(actorID, actorMovieHead);
//    if (!actor) {
//        cout << mainActorName << " has no known connections.\n";
//        return;
//    }
//
//    for (MovieNode* movie = actor->movieHead; movie; movie = movie->next) {
//        MovieActorList* movieEntry = findMovie(movie->movieID, movieActorHead);
//        for (ActorNode* coActor = movieEntry->actorHead; coActor; coActor = coActor->next) {
//            if (coActor->actorID != actorID) {
//                // Check if already in the list
//                KnownActorNode* temp = knownActors;
//                bool exists = false;
//                while (temp) {
//                    if (temp->actorID == coActor->actorID) {
//                        exists = true;
//                        break;
//                    }
//                    temp = temp->next;
//                }
//                if (!exists) {
//                    KnownActorNode* newNode = new KnownActorNode(coActor->actorID);
//                    newNode->next = knownActors;
//                    knownActors = newNode;
//                }
//            }
//        }
//    }
//
//    // Collect second-level connections
//    for (KnownActorNode* firstLevel = knownActors; firstLevel; firstLevel = firstLevel->next) {
//        ActorMovieList* firstLevelActor = findActor(firstLevel->actorID, actorMovieHead);
//        if (firstLevelActor) {
//            for (MovieNode* movie = firstLevelActor->movieHead; movie; movie = movie->next) {
//                MovieActorList* movieEntry = findMovie(movie->movieID, movieActorHead);
//                for (ActorNode* coActor = movieEntry->actorHead; coActor; coActor = coActor->next) {
//                    if (coActor->actorID != actorID && coActor->actorID != firstLevel->actorID) {
//                        // Check if already in the list
//                        KnownActorNode* temp = knownActors;
//                        bool exists = false;
//                        while (temp) {
//                            if (temp->actorID == coActor->actorID) {
//                                exists = true;
//                                break;
//                            }
//                            temp = temp->next;
//                        }
//
//                        // Add only if not in the list
//                        if (!exists) {
//                            KnownActorNode* newNode = new KnownActorNode(coActor->actorID);
//                            newNode->next = knownActors;
//                            knownActors = newNode;
//                        }
//                    }
//                }
//            }
//        }
//    }
//
//    // Print combined list
//    for (KnownActorNode* temp = knownActors; temp; temp = temp->next) {
//        Actor* actor = actorTree.search(temp->actorID);
//        if (actor) cout << "- " << actor->getName() << " (ID: " << temp->actorID << ")\n";
//    }
//
//    // Free memory
//    while (knownActors) {
//        KnownActorNode* temp = knownActors;
//        knownActors = knownActors->next;
//        delete temp;
//    }
//}
//

#include "cast.h"

// Constructor
Cast::Cast() {
    actorMovieHead = nullptr;
    movieActorHead = nullptr;
}

// Helper function to find an actor in actorMovieHead
ActorMovieList* findActor(BinaryNode* actor, ActorMovieList*& head) {
    ActorMovieList* temp = head;
    while (temp) {
        if (temp->actor == actor) 
            return temp;
        temp = temp->next;
    }
    return nullptr;
}

// Helper function to find a movie in movieActorHead
MovieActorList* findMovie(int movieID, MovieActorList*& head) {
    MovieActorList* temp = head;
    while (temp) {
        if (temp->movieID == movieID) return temp;
        temp = temp->next;
    }
    return nullptr;
}

// Add an actor-movie relationship
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

// Display all movies an actor starred in
void Cast::displayMoviesByActor(BinaryNode* actor, List<Movie> movieList) {
    if (!actor) {
        cout << "Actor not found.\n";
        return;
    }

    ActorMovieList* actorEntry = findActor(actor, actorMovieHead);
    if (!actorEntry) {
        cout << actor->item.getName() << " has no movies.\n";
        return;
    }

    cout << "Movies starred in by " << actor->item.getName() << ":\n";
    MovieNode* temp = actorEntry->movieHead;
    while (temp) {
        int index = movieList.search(temp->movieID);
        Movie movie = movieList.get(index);
        cout << "- Movie ID: " << temp->movieID << "\tTitle:" << movie.getTitle() <<endl;
        temp = temp->next;
    }
}

// Display all actors in a movie
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

    // Collect first-level connections
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

    // Print combined list
    for (KnownActorNode* temp = knownActors; temp; temp = temp->next) {
        cout << "- " << temp->actor->item.getName() << " (ID: " << temp->actor->item.getId() << ")\n";
    }

    // Free memory
    while (knownActors) {
        KnownActorNode* temp = knownActors;
        knownActors = knownActors->next;
        delete temp;
    }
}

