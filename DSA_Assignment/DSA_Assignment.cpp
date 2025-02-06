#include <iostream>
#include <fstream>   // For ifstream (file handling)
#include <sstream>   // For stringstream (parsing)
#include "cast.h"
#include "ActorBST.h"
#include "Movie.h"
#include "Actor.h"
#include "List.h"
#include "Dictionary.h"

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
        //cout << "Inserted Actor: " << id << " - " << name << " (" << birth << ")\n"; // Debugging output
    }

    file.close();
    cout << "Total Actors Inserted: " << actorCount << endl;  // Final count
}

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

void readMovies(string filename, List<Movie>& movieList) {
    ifstream file(filename);

    if (!file) {
        cerr << "Error: Unable to open file " << filename << endl;
        return;
    }

    string line;
    getline(file, line);

    while (getline(file, line)) {
        stringstream ss(line);
        int id, year;
        string title, plot;

        // Read integer ID directly
        ss >> id;
        ss.ignore(); // Ignore the tab separator

        // Read Title
        getline(ss, title, ',');

        // Read Plot
        getline(ss, plot, ',');

        // Read integer Year directly
        ss >> year;

        Movie movie(id, title, plot, year);
        movieList.add(movie);
    }

    file.close();
}

// -------------- Function for option 2: adding new Movie
void addMovie(List<Movie>& movieList) {
    string title, plot;
    int year;
    cout << "Enter the title of Movie: ";
    getline(cin, title);

    cout << "Enter plot of the movie: ";
    getline(cin, plot);

    // Validate year input
    while (true) {
        cout << "Enter the movie's year of release: ";
        cin >> year;

        if (cin.fail() || year < 1888 || year > 2025) {
            cout << "Invalid input! Please enter a valid year (1888 - 2025)." << endl;
            cin.clear();  // Clear error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Discard invalid input
        }
        else {
            break;  // Valid input, exit loop
        }
    }

    // searching for largest Movie id in the list
    int id = 1;
    for (int i = 0; i < movieList.getLength(); i++) {
        Movie m = movieList.get(i);
        if (m.getId() > id) {
            id = m.getId();
        }
    }
    id += 1; //id for the new movie

    //adding new movie to the list
    Movie newMovie(id, title, plot, year);
    movieList.add(newMovie);

    cout << "Movie added successfully with ID: " << id << endl;
}

// -------------- Function for option 5: update movie details
void updateMovie(List<Movie>& movieList) {
    int id;
    int index = -1;
    while (true) {
        cout << "Enter the ID of the movie that you want to update: ";
        cin >> id;

        if (cin.fail()) {
            cout << "Invalid input! Please enter a valid numeric ID." << endl;
            cin.clear();  // Clear error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Discard invalid input
            continue;  // Restart loop
        }

        // Check if the ID exists in the list
        for (int i = 0; i < movieList.getLength(); i++) {
            if (movieList.get(i).getId() == id) {
                index = i;
                break;
            }
        }

        if (index != -1) {
            break;  // Valid ID, exit loop
        }
        else {
            cout << "Movie with ID " << id << " not found. Please enter a valid ID." << endl;
        }
    }

    cout << "Current Movie details" << endl;
    cout << "---------------------" << endl;
    cout << "ID: " << movieList.get(index).getId() << endl;
    cout << "Title: " << movieList.get(index).getTitle() << endl;
    cout << "Plot: " << movieList.get(index).getPlot() << endl;
    cout << "Year: " << movieList.get(index).getYear() << endl;
    cout << endl;

    string newTitle, newPlot;
    int newYear;

    cin.ignore();  // Clear input buffer before using getline()
    cout << "Enter new title (leave blank to keep current): ";
    getline(cin, newTitle);

    cout << "Enter new plot (leave blank to keep current): ";
    getline(cin, newPlot);

    // Validate new year input
    while (true) {
        cout << "Enter new year (1888 - 2025) or 0 to keep current: ";
        cin >> newYear;

        if (cin.fail() || (newYear != 0 && (newYear < 1888 || newYear > 2025))) {
            cout << "Invalid year! Please enter a valid year between 1888 and 2025, or 0 to keep current." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else {
            break;
        }
    }

    Movie updatedMovie = movieList.get(index);  // Get a copy of the movie

    if (!newTitle.empty()) updatedMovie.setTitle(newTitle);
    if (!newPlot.empty()) updatedMovie.setPlot(newPlot);
    if (newYear != 0) updatedMovie.setYear(newYear);

    movieList.replace(index, updatedMovie);  // Replace the movie in the list

    cout << "Movie updated successfully! This is the new Movie details" << endl;
    cout << "---------------------" << endl;
    cout << "ID: " << movieList.get(index).getId() << endl;
    cout << "Title: " << movieList.get(index).getTitle() << endl;
    cout << "Plot: " << movieList.get(index).getPlot() << endl;
    cout << "Year: " << movieList.get(index).getYear() << endl;

}

int main()
{
    ActorBST actorTree;
    readActors("actors.csv", actorTree);
    readCast("cast.csv", castTable);

    List<Movie> movieList; //creating movie list
    readMovies("movies.csv", movieList); //reading movies.csv and adding to movieList
    
    ////---------------------------- testing movies data
    //int l = movieList.getLength();
    //cout << l << endl;
    //Movie m = movieList.get(0);
    //Movie m17214 = movieList.get(17213);
    //cout << m.getId() << m.getTitle() << m.getPlot() << m.getYear() << endl;
    //cout << m17214.getId() << m17214.getTitle() << m17214.getPlot() << m17214.getYear() << endl;
    ////----------------------------------


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
            cout << "Adding a new Movie" << endl;
            cout << "------------------" << endl;
            cout << endl;

            addMovie(movieList);

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
            cout << "Updating Movie Details" << endl;
            cout << "----------------------" << endl;
            cout << endl;

            updateMovie(movieList);
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
            castTable.displayKnownActors(actorID, actorTree);
        }

        else 
        {
            cout << "Invalid choice." << endl;
        }

    } while (choice != 0);  // Continue until the user chooses to exit
    
    cout << "\nExiting ..." << endl;

    return 0;
}


