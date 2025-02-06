#include <iostream>
#include <fstream>   // For ifstream (file handling)
#include <sstream>   // For stringstream (parsing)
#include "cast.h"
#include "ActorBST.h"

using namespace std;
Cast castTable;

// Function to read cast.csv and store relationships
void readCast(string filename, Cast& castTable) {
    ifstream file(filename);
    if (!file) {
        cerr << "Error: Unable to open file " << filename << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        int actorID, movieID;

        if (!(ss >> actorID)) continue; // Read actor ID
        ss.ignore();  // Ignore separator
        if (!(ss >> movieID)) continue; // Read movie ID

        castTable.addActorToMovie(actorID, movieID); // Store in adjacency list
    }

    file.close();
    cout << "Cast relationships loaded successfully!\n";
}

// Function to read actors from a CSV file and insert them into the BST
void readActors(string filename, ActorBST& actorTree) {
    ifstream file(filename);
    if (!file) {
        cerr << "Error: Unable to open file " << filename << endl;
        return;
    }
    int actorCount = 0;  // Counter to track how many actors are added
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        int id, birth;
        string name;

        if (!(ss >> id)) continue; // Read actor ID
        ss.ignore(); // Ignore the whitespace or comma separator
        getline(ss, name, ','); // Read actor name
        if (!(ss >> birth)) continue; // Read birth year

        actorTree.insert(id, name, birth); // Insert into BST

        actorCount++;
        cout << "Inserted Actor: " << id << " - " << name << " (" << birth << ")\n"; // Debugging output
    }

    file.close();
    cout << "Total Actors Inserted: " << actorCount << endl;  // Final count
}

#include "Movie.h"
#include "Actor.h"
#include "List.h"
#include "Dictionary.h"

int displayMenu() {
    int choice;

    cout << "\n------------------- Menu ---------------------------------------";
    cout << "\n[1]  Add a new actor";
    cout << "\n[2]  Add new movie";
    cout << "\n[3]  Add an actor to a movie";
    cout << "\n[4]  Update actor details";
    cout << "\n[5]  Update movie details";
    cout << "\n[6]  Display actors according to age";
    cout << "\n[7]  Display movies made within the past 3 years";
    cout << "\n[8]  Display all movies an actor starred in";
    cout << "\n[9]  Display all actors in a movie";
    cout << "\n[10] Display a list of all actors that a particular actor knows";
    cout << "\n[0]  Exit";
    cout << "\n----------------------------------------------------------------";
    cout << "\nChoose an option: ";

    cin >> choice;
    cin.ignore(); // To clear newline from input buffer

    return choice;
}


int main()
{
    ActorBST actorTree;
    readActors("actors.csv", actorTree);
    readCast("cast.csv", castTable);
    int choice;
    
    do {
        choice = displayMenu();  // Show menu and get the user's choice

        if (choice == 1) 
        {
            int id, birth;
            string name;
            cout << "Enter Actor ID: ";
            cin >> id;
            cin.ignore();
            cout << "Enter Actor Name: ";
            getline(cin, name);
            cout << "Enter Actor Birth Year: ";
            cin >> birth;
            actorTree.insert(id, name, birth);
            cout << "Actor added successfully!\n";
        }

        else if (choice == 2) 
        {
            
        }

        else if (choice == 3) 
        {
            
        }

        else if (choice == 4) 
        {
            int id, birth;
            string name;
            cout << "Enter Actor ID to update: ";
            cin >> id;
            cin.ignore();

            cout << "Enter new name (press Enter to keep current name): ";
            getline(cin, name);

            cout << "Enter new birth year (enter -1 to keep current year): ";
            cin >> birth;

            actorTree.updateActor(id, name, birth);
        }

        else if (choice == 5) 
        {
            
        }

        else if (choice == 6) 
        {
            int minAge, maxAge;
            cout << "Enter minimum age: ";
            cin >> minAge;
            cout << "Enter maximum age: ";
            cin >> maxAge;

            actorTree.displayActorsByAgeRange(minAge, maxAge);

        }

        else if (choice == 7)
        {

        }

        else if (choice == 8)
        {
            int actorID;
            cout << "Enter Actor ID: ";
            cin >> actorID;
            castTable.displayMoviesByActor(actorID);
        }

        else if (choice == 9)
        {

        }

        else if (choice == 10)
        {
            int actorID;
            cout << "Enter Actor ID: ";
            cin >> actorID;
            castTable.displayKnownActors(actorID);
        }

        else 
        {
            cout << "Invalid choice." << endl;
        }

    } while (choice != 0);  // Continue until the user chooses to exit
    
    cout << "\nExiting ..." << endl;

    return 0;
}


