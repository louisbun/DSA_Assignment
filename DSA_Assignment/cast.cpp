//#include "cast.h"
//#include <algorithm> // Needed for sorting
//using namespace std;
//
//// Add an actor-movie relationship
//void Cast::addActorToMovie(int actorID, int movieID) {
//    actorToMovies[actorID].push_back(movieID);
//    movieToActors[movieID].push_back(actorID);
//}
//
//// Display all movies an actor starred in (sorted alphabetically)
//void Cast::displayMoviesByActor(int actorID) {
//    if (actorToMovies.find(actorID) == actorToMovies.end()) {
//        cout << "Actor not found or has no movies.\n";
//        return;
//    }
//
//    vector<int> movies = actorToMovies[actorID];
//    sort(movies.begin(), movies.end()); // Sort movie IDs alphabetically (assumes movies have unique IDs)
//
//    cout << "Movies starred in:\n";
//    for (int movieID : movies) {
//        cout << "- Movie ID: " << movieID << endl;
//    }
//}
//
//// Display all actors in a movie (sorted alphabetically)
//void Cast::displayActorsByMovie(int movieID) {
//    if (movieToActors.find(movieID) == movieToActors.end()) {
//        cout << "Movie not found or has no actors.\n";
//        return;
//    }
//
//    vector<int> actors = movieToActors[movieID];
//    sort(actors.begin(), actors.end()); // Sort actors alphabetically (by ID)
//
//    cout << "Actors in Movie ID " << movieID << ":\n";
//    for (int actorID : actors) {
//        cout << "- Actor ID: " << actorID << endl;
//    }
//}
//
//// Display all actors that a particular actor knows
//void Cast::displayKnownActors(int actorID) {
//    if (actorToMovies.find(actorID) == actorToMovies.end()) {
//        cout << "Actor not found or has no known connections.\n";
//        return;
//    }
//
//    set<int> knownActors;
//    for (int movieID : actorToMovies[actorID]) {
//        for (int coActorID : movieToActors[movieID]) {
//            if (coActorID != actorID) {
//                knownActors.insert(coActorID);
//            }
//        }
//    }
//
//    cout << "Actors known by Actor ID " << actorID << ":\n";
//    if (knownActors.empty()) {
//        cout << "No known actors found.\n";
//        return;
//    }
//
//    for (int id : knownActors) {
//        cout << "- Actor ID: " << id << endl;
//    }
//}


#include "cast.h"

// Constructor
Cast::Cast() {
    actorMovieHead = nullptr;
    movieActorHead = nullptr;
}

// Helper function to find an actor in actorMovieHead
ActorMovieList* findActor(int actorID, ActorMovieList*& head) {
    ActorMovieList* temp = head;
    while (temp) {
        if (temp->actorID == actorID) return temp;
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
void Cast::addActorToMovie(int actorID, int movieID) {
    // Add movie to actor's list
    ActorMovieList* actor = findActor(actorID, actorMovieHead);
    if (!actor) {
        actor = new ActorMovieList(actorID);
        actor->next = actorMovieHead;
        actorMovieHead = actor;
    }

    // Insert movie ID in actor's movie list
    MovieNode* newMovie = new MovieNode(movieID);
    newMovie->next = actor->movieHead;
    actor->movieHead = newMovie;

    // Add actor to movie's list
    MovieActorList* movie = findMovie(movieID, movieActorHead);
    if (!movie) {
        movie = new MovieActorList(movieID);
        movie->next = movieActorHead;
        movieActorHead = movie;
    }

    // Insert actor ID in movie's actor list
    ActorNode* newActor = new ActorNode(actorID);
    newActor->next = movie->actorHead;
    movie->actorHead = newActor;
}

// Display all movies an actor starred in
void Cast::displayMoviesByActor(int actorID) {
    ActorMovieList* actor = findActor(actorID, actorMovieHead);
    if (!actor) {
        cout << "Actor not found or has no movies.\n";
        return;
    }

    cout << "Movies starred in:\n";
    MovieNode* temp = actor->movieHead;
    while (temp) {
        cout << "- Movie ID: " << temp->movieID << endl;
        temp = temp->next;
    }
}

// Display all actors in a movie
void Cast::displayActorsByMovie(int movieID) {
    MovieActorList* movie = findMovie(movieID, movieActorHead);
    if (!movie) {
        cout << "Movie not found or has no actors.\n";
        return;
    }

    cout << "Actors in Movie ID " << movieID << ":\n";
    ActorNode* temp = movie->actorHead;
    while (temp) {
        cout << "- Actor ID: " << temp->actorID << endl;
        temp = temp->next;
    }
}

// Display all actors that a particular actor knows
//void Cast::displayKnownActors(int actorID) {
//    ActorMovieList* actor = findActor(actorID, actorMovieHead);
//    if (!actor) {
//        cout << "Actor not found or has no known connections.\n";
//        return;
//    }
//
//    // Using a simple linked list instead of a set
//    struct KnownActorNode {
//        int actorID;
//        KnownActorNode* next;
//        KnownActorNode(int id) : actorID(id), next(nullptr) {}
//    };
//
//    KnownActorNode* knownActors = nullptr;
//
//    // Collect known actors (one degree of separation)
//    for (MovieNode* movie = actor->movieHead; movie; movie = movie->next) {
//        MovieActorList* movieEntry = findMovie(movie->movieID, movieActorHead);
//        for (ActorNode* coActor = movieEntry->actorHead; coActor; coActor = coActor->next) {
//            if (coActor->actorID != actorID) {
//                KnownActorNode* newNode = new KnownActorNode(coActor->actorID);
//                newNode->next = knownActors;
//                knownActors = newNode;
//            }
//        }
//    }
//
//    cout << "Actors known by Actor ID " << actorID << ":\n";
//    for (KnownActorNode* temp = knownActors; temp; temp = temp->next) {
//        cout << "- Actor ID: " << temp->actorID << endl;
//    }
//
//    // Clean up memory
//    while (knownActors) {
//        KnownActorNode* temp = knownActors;
//        knownActors = knownActors->next;
//        delete temp;
//    }
//}

//void Cast::displayKnownActors(int actorID) {
//    ActorMovieList* actor = findActor(actorID, actorMovieHead);
//    if (!actor) {
//        cout << "Actor not found or has no known connections.\n";
//        return;
//    }
//
//    struct KnownActorNode {
//        int actorID;
//        KnownActorNode* next;
//        KnownActorNode(int id) : actorID(id), next(nullptr) {}
//    };
//
//    KnownActorNode* knownActors = nullptr;
//    KnownActorNode* secondLevelActors = nullptr;
//
//    // Collect first-level connections (actors in the same movies)
//    for (MovieNode* movie = actor->movieHead; movie; movie = movie->next) {
//        MovieActorList* movieEntry = findMovie(movie->movieID, movieActorHead);
//        for (ActorNode* coActor = movieEntry->actorHead; coActor; coActor = coActor->next) {
//            if (coActor->actorID != actorID) {
//                KnownActorNode* newNode = new KnownActorNode(coActor->actorID);
//                newNode->next = knownActors;
//                knownActors = newNode;
//            }
//        }
//    }
//
//    // Collect second-level connections (one more level)
//    for (KnownActorNode* firstLevel = knownActors; firstLevel; firstLevel = firstLevel->next) {
//        ActorMovieList* firstLevelActor = findActor(firstLevel->actorID, actorMovieHead);
//        if (firstLevelActor) {
//            for (MovieNode* movie = firstLevelActor->movieHead; movie; movie = movie->next) {
//                MovieActorList* movieEntry = findMovie(movie->movieID, movieActorHead);
//                for (ActorNode* coActor = movieEntry->actorHead; coActor; coActor = coActor->next) {
//                    if (coActor->actorID != actorID && coActor->actorID != firstLevel->actorID) {
//                        KnownActorNode* newNode = new KnownActorNode(coActor->actorID);
//                        newNode->next = secondLevelActors;
//                        secondLevelActors = newNode;
//                    }
//                }
//            }
//        }
//    }
//
//    // Print results
//    cout << "Actors directly known by Actor ID " << actorID << ":\n";
//    for (KnownActorNode* temp = knownActors; temp; temp = temp->next) {
//        cout << "- Actor ID: " << temp->actorID << " (Direct Connection)\n";
//    }
//
//    cout << "\nActors known at second level (one more level) by Actor ID " << actorID << ":\n";
//    for (KnownActorNode* temp = secondLevelActors; temp; temp = temp->next) {
//        cout << "- Actor ID: " << temp->actorID << " (Indirect Connection)\n";
//    }
//
//    // Free memory
//    while (knownActors) {
//        KnownActorNode* temp = knownActors;
//        knownActors = knownActors->next;
//        delete temp;
//    }
//    while (secondLevelActors) {
//        KnownActorNode* temp = secondLevelActors;
//        secondLevelActors = secondLevelActors->next;
//        delete temp;
//    }
//}

void Cast::displayKnownActors(int actorID, ActorBST& actorTree) {
    Actor* mainActor = actorTree.search(actorID);
    if (!mainActor) {
        cout << "Actor not found.\n";
        return;
    }

    string mainActorName = mainActor->getName();
    cout << "Actors known by " << mainActorName << ":\n";

    struct KnownActorNode {
        int actorID;
        KnownActorNode* next;
        KnownActorNode(int id) : actorID(id), next(nullptr) {}
    };

    KnownActorNode* knownActors = nullptr;

    // Collect first-level connections
    ActorMovieList* actor = findActor(actorID, actorMovieHead);
    if (!actor) {
        cout << mainActorName << " has no known connections.\n";
        return;
    }

    for (MovieNode* movie = actor->movieHead; movie; movie = movie->next) {
        MovieActorList* movieEntry = findMovie(movie->movieID, movieActorHead);
        for (ActorNode* coActor = movieEntry->actorHead; coActor; coActor = coActor->next) {
            if (coActor->actorID != actorID) {
                // Check if already in the list
                KnownActorNode* temp = knownActors;
                bool exists = false;
                while (temp) {
                    if (temp->actorID == coActor->actorID) {
                        exists = true;
                        break;
                    }
                    temp = temp->next;
                }
                if (!exists) {
                    KnownActorNode* newNode = new KnownActorNode(coActor->actorID);
                    newNode->next = knownActors;
                    knownActors = newNode;
                }
            }
        }
    }

    // Collect second-level connections
    for (KnownActorNode* firstLevel = knownActors; firstLevel; firstLevel = firstLevel->next) {
        ActorMovieList* firstLevelActor = findActor(firstLevel->actorID, actorMovieHead);
        if (firstLevelActor) {
            for (MovieNode* movie = firstLevelActor->movieHead; movie; movie = movie->next) {
                MovieActorList* movieEntry = findMovie(movie->movieID, movieActorHead);
                for (ActorNode* coActor = movieEntry->actorHead; coActor; coActor = coActor->next) {
                    if (coActor->actorID != actorID && coActor->actorID != firstLevel->actorID) {
                        // Check if already in the list
                        KnownActorNode* temp = knownActors;
                        bool exists = false;
                        while (temp) {
                            if (temp->actorID == coActor->actorID) {
                                exists = true;
                                break;
                            }
                            temp = temp->next;
                        }

                        // Add only if not in the list
                        if (!exists) {
                            KnownActorNode* newNode = new KnownActorNode(coActor->actorID);
                            newNode->next = knownActors;
                            knownActors = newNode;
                        }
                    }
                }
            }
        }
    }

    // Print combined list
    for (KnownActorNode* temp = knownActors; temp; temp = temp->next) {
        Actor* actor = actorTree.search(temp->actorID);
        if (actor) cout << "- " << actor->getName() << " (ID: " << temp->actorID << ")\n";
    }

    // Free memory
    while (knownActors) {
        KnownActorNode* temp = knownActors;
        knownActors = knownActors->next;
        delete temp;
    }
}

