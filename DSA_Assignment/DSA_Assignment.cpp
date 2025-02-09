#include <iostream>
#include <fstream>   // For ifstream (file handling)
#include <sstream>   // For stringstream (parsing)
#include "cast.h"
#include "BST.h"
#include "Movie.h"
#include "Actor.h"
#include "List.h"
#include "Dictionary.h"
#include <iomanip>

using namespace std;
Cast castTable;

// Function to read cast.csv and store relationships
void readCast(string filename, Cast& castTable, BST& actorTree) {
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

        // Search for the actor in the BST
        BinaryNode* actorNode = actorTree.search(actorID);
        if (actorNode) {
            castTable.addActorToMovie(actorNode, movieID); // Add using BinaryNode*
        }
        else {
            cout << "Warning: Actor ID " << actorID << " not found in BST. Skipping entry.\n";
        }
    }

    file.close();
    /*cout << "Cast relationships loaded successfully!\n";*/
}


// Function to read actors from a CSV file and insert them into the BST
void readActors(string filename, BST& actorTree) {
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
        ss.ignore(); // Ignore whitespace or comma separator
        getline(ss, name, ','); // Read actor name
        if (!(ss >> birth)) continue; // Read birth year

        // Create an Actor object and insert it into BST
        Actor newActor(id, name, birth);
        actorTree.insert(newActor);

        actorCount++;
        //cout << "Inserted Actor: " << id << " - " << name << " (" << birth << ")\n"; // Debugging output
    }

    file.close();
    //cout << "Total Actors Inserted: " << actorCount << endl;  // Final count
}


void displayMenu() {

    cout << "\n------------------- Menu ---------------------------------------";
    cout << "\nAdministrator Options" << endl;
    cout << "\n[1]  Add a new actor";
    cout << "\n[2]  Add new movie";
    cout << "\n[3]  Add an actor to a movie";
    cout << "\n[4]  Update actor details";
    cout << "\n[5]  Update movie details" << endl;
    cout << "\nUser Options" << endl;
    cout << "\n[6]  Display actors according to age";
    cout << "\n[7]  Display movies made within the past 3 years";
    cout << "\n[8]  Display all movies an actor starred in";
    cout << "\n[9]  Display all actors in a movie";
    cout << "\n[10] Display a list of all actors that a particular actor knows";
    cout << "\n[11] Rate an actor";
    cout << "\n[12] Rate a movie";
    cout << "\n[13] Recommend based on actor ratings";
    cout << "\n[14] Recommend based on movie ratings";
    cout << "\n[0]  Exit";
    cout << "\n----------------------------------------------------------------";
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
void readMovies(string filename, Dictionary& movieDict) {
    ifstream file(filename);

    if (!file) {
        cerr << "Error: Unable to open file " << filename << endl;
        return;
    }

    string line;
    getline(file, line); // Skip the header if present

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

        // Create a new Movie object
        Movie movie(id, title, plot, year);

        // Add the movie to the Dictionary using its ID as the key
        bool success = movieDict.add(id, movie);
        if (!success) {
            cerr << "Error: Movie with ID " << id << " could not be added to the Dictionary." << endl;
        }
    }

    file.close();
}

void insertActorsToMovies(string filename, BST& actorTree, List<Movie>& movieList) {
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

        // Search for the Actor in BST
        BinaryNode* actorNode = actorTree.search(actorID);
        if (!actorNode) {
            cout << "Warning: Actor ID " << actorID << " not found in BST. Skipping entry.\n";
            continue;
        }

        // Search for the Movie in the Linked List
        for (int i = 0; i < movieList.getLength(); i++) {
            Movie& movie = movieList.getReference(i);  //  Get reference
            if (movie.getId() == movieID) {
                movie.getActors().insert(actorNode->item); //  Modify the movie in the list
                break;  
            }
        }
    }

    file.close();
    cout << "Cast relationships added to movies successfully!\n";
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

// -------------- Function for option 3: Add an actor to a movie
void addActorToMovie(BST& actorTree, List<Movie>& movieList, Cast& castTable) {
    int movieId, actorId;
    cout << "Enter the Movie ID: ";
    cin >> movieId;

    cout << "Enter the Actor ID: ";
    cin >> actorId;

    int movieIndex = movieList.search(movieId);
    if (movieIndex == -1) {
        cout << "Movie with ID " << movieId << " not found." << endl;
        return;  // Exit if movie is not found
    }

    // Search for the actor in the actorTree
    BinaryNode* actorNode = actorTree.search(actorId); 
    if (actorNode == nullptr) {
        cout << "Actor with ID " << actorId << " not found." << endl;
        return;  // Exit if actor is not found
    }

    Movie& movie = movieList.getReference(movieIndex);
    // Check if the actor is already in the movie
    if (movie.getActors().search(actorId) != nullptr) {  // If search is not null, actor already exists
        cout << "Actor " << actorNode->item.getName() << " is already in the movie " << movie.getTitle() << "." << endl;
        return;  // Stop here to prevent duplicate entry
    }
    movie.getActors().insert(actorNode->item);
    castTable.addActorToMovie(actorNode, movieId);

    cout << "Actor " << actorNode->item.getName() << " added to the movie " << movie.getTitle() << " successfully." << endl;
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

//----------------Function for option 7: display Movies made within the past 3 years
void displayRecentMovies(List<Movie>& movieList) {

    // Create a temporary list to store movies made within the last 3 years
    List<Movie> recentMovies;

    // Loop through all movies and filter out those made in the last 3 years
    for (int i = 0; i < movieList.getLength(); i++) {
        Movie m = movieList.get(i);
        if (2025 - m.getYear() <= 3) {
            recentMovies.add(m);
        }
    }

    // sort the temp list
    recentMovies.mergeSort();

    if (recentMovies.getLength() == 0) {
        cout << "No movies found from the last 3 years." << endl;
        
    }
    else {
        cout << endl;
        cout << "Movies made within the past 3 years (in ascending order of year):" << endl;
        cout << "-----------------------------------------------------------------" << endl;
        for (int i = 0; i < recentMovies.getLength(); i++) {
            Movie m = recentMovies.get(i);
            cout << "ID: " << m.getId() << ", Title: " << m.getTitle() << ", Year: " << m.getYear() << endl;
        }
    }
}

//----------------Function for option 9: display all Actors in a Movie
void displayActorsInMovie(List<Movie>& movieList) {

    int movieId;
    int movieIndex;

    while (true) {
        cout << "Enter Movie ID: ";
        cin >> movieId;

        // Check if cin failed (non-integer input or other invalid input)
        if (cin.fail()) {
            cin.clear();  // Clear the error state
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Ignore the rest of the input
            cout << "Invalid input. Please enter a valid Movie ID." << endl;
        }
        else {
            // Search for the movieId in the movieList
            movieIndex = movieList.search(movieId);

            // Check if the movie was found (movieIndex != -1)
            if (movieIndex == -1) {
                cout << "Movie ID not found. Please enter a valid Movie ID." << endl;
            }
            else {
                break;  // Valid input and valid movie ID found, exit loop
            }
        }
    }

    Movie m = movieList.get(movieIndex);

    //creating temporary arraylist for actors
    ArrayList<Actor> temp;
    m.getActors().getActorsInList(temp); // put all actors in the movie into temp
    if (temp.getLength() == 0) {
        cout << "No actors found for this movie." << endl;
        return;
    }
    temp.sortByActorName(); //sorting according to actor's name

    cout << "Displaying all Actors in " << m.getTitle() << " (in alphabetical order)" << endl;
    cout << "------------------------------------------" << endl;
    temp.print();
}

//----------------Function for option 11: rating an actor---------------
void rateActor(BST& actorTree) {
    int actorId;
    float rating;

    cout << "Enter Actor ID: ";
    cin >> actorId;

    BinaryNode* actorNode = actorTree.search(actorId);
    if (actorNode == nullptr) {
        cout << "Actor not found!" << endl;
        return;
    }

    // Validate rating input
    while (true) {
        cout << "Enter new rating (0-10): ";
        cin >> rating;

        // Check if input is a number and within range
        if (cin.fail() || rating < 0 || rating > 10) {
            cout << "Invalid rating. Must be a number between 0 and 10." << endl;
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
        }
        else {
            break; // Valid input, exit loop
        }
    }

    actorNode->item.addRating(rating);
    cout << fixed << setprecision(1);
    cout << "Actor " << actorNode->item.getName() << " has been updated with a rating of " << actorNode->item.getRating() << endl;
}

//----------------Function for option 12: rating an movie---------------
void rateMovie(List<Movie>& movieList) {
    int movieId;
    float rating;

    cout << "Enter Movie ID: ";
    cin >> movieId;

    int movieIndex = movieList.search(movieId);
    if (movieIndex == -1) {
        cout << "Movie not found!" << endl;
        return;
    }
    Movie& m = movieList.getReference(movieIndex); 

    // Validate rating input
    while (true) {
        cout << "Enter new rating (0-10): ";
        cin >> rating;

        // Check if input is a number and within range
        if (cin.fail() || rating < 0 || rating > 10) {
            cout << "Invalid rating. Must be a number between 0 and 10." << endl;
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
        }
        else {
            break; // Valid input, exit loop
        }
    }

    m.addRating(rating);
    cout << fixed << setprecision(1);
    cout << "Movie " << m.getTitle() << " has been updated with a rating of " << m.getRating() << endl;
}

//----------------Function for option 13: Recommend Actors base on rating---------------
void recommendActors(BST& actorTree) 
{
    actorTree.displayActorsByRating();
}

//----------------Function for option 14: Recommend Movies base on rating---------------
void recommendMovies(List<Movie>& movieList){

    List<Movie> temp;
    for (int i = 0; i < movieList.getLength(); i++) {
        Movie m = movieList.get(i);
        if (m.getRating() > 0) {
            temp.add(m);
        }
    }

    temp.mergeSortByRating(); // sorting by rating

    cout << "Top 5 Recommended Movies base on Rating" << endl;
    for (int i = 0; i < temp.getLength() && i < 5; i++) {
        cout << i + 1 << "." << endl;
        cout << "----------" << endl;
        Movie m = temp.get(i);

        cout << "Movie ID: " << m.getId() << endl;
        cout << "Title: " << m.getTitle() << endl;
        cout << "Year: " << m.getYear() << endl;
        cout << "Rating: " << m.getRating() << " / 10" << endl;
        cout << endl;
    }

    if (temp.getLength() == 0) {
        cout << "No Movies has been rated yet." << endl;
    }
}

int main()
{
    BST actorTree;
    readActors("actors.csv", actorTree);
    readCast("cast.csv", castTable, actorTree);

    List<Movie> movieList; //creating movie list
    readMovies("movies.csv", movieList); //reading movies.csv and adding to movieList
    
    //adding movies to movie dictionary
    /*Dictionary movieDict;
    readMovies("movies.csv", movieDict);*/

    ////---------------------------- testing movies data
    //int l = movieDict.getLength();
    //cout << l << endl;
    //Movie m = movieDict.get(260368);
    //Movie m17214 = movieDict.get(6405058);
    //cout << m.getId() << m.getTitle() << m.getPlot() << m.getYear() << endl;
    //cout << m17214.getId() << m17214.getTitle() << m17214.getPlot() << m17214.getYear() << endl;
    ////----------------------------------



    ////---------------------------- testing movies data
    //int l = movieList.getLength();
    //cout << l << endl;
    //Movie m = movieList.get(0);
    //Movie m17214 = movieList.get(17213);
    //cout << m.getId() << m.getTitle() << m.getPlot() << m.getYear() << endl;
    //cout << m17214.getId() << m17214.getTitle() << m17214.getPlot() << m17214.getYear() << endl;
    ////----------------------------------


    //Adding actors to movies----------------
    insertActorsToMovies("cast.csv", actorTree, movieList);

    ////-----------------------testing inserted actors in movies---------------
    //int idtest = 117600;
    //for (int i = 0; i < movieList.getLength(); i++) {
    //    if (movieList.get(i).getId() == idtest) {
    //        Movie m117600 = movieList.get(i);
    //        m117600.getActors().displaySorted();
    //    }
    //}
    ////------------------------------------------------------------------------

    int choice;
    bool exit = false;
    while(exit==false) {

        displayMenu();  // Show menu and get the user's choice
        // Input validation loop
        while (true) {
            cout << "\nChoose an option: ";
            cin >> choice;

            if (cin.fail()) {  // If input is not a valid integer
                cin.clear();  // Clear error state
                cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Ignore invalid input
                cout << "Invalid input. Please enter a valid number for the menu choice." << endl;
            }
            else if (choice < 0 || choice > 14) {  // Ensure input is within valid range
                cout << "Invalid choice. Please enter a number between 0 and 14." << endl;
            }
            else {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Clear buffer in case of extra input
                break;  // Exit loop if input is valid
            }
        }

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

            // Insert new actor object
            Actor newActor(id, name, birth);
            actorTree.insert(newActor);

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
            addActorToMovie(actorTree, movieList, castTable);

            //testing data
            /*for (int i = 0; i < movieList.getLength(); i++) {
                if (movieList.get(i).getId() == idtest) {
                    Movie m117600 = movieList.get(i);
                    m117600.getActors().displaySorted();
                }
            }*/
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
            displayRecentMovies(movieList);
        }

        else if (choice == 8)
        {
            int actorID;
            cout << "Enter Actor ID: ";
            cin >> actorID;
            BinaryNode* actor = actorTree.search(actorID);
            castTable.displayMoviesByActor(actor, movieList);
        }

        else if (choice == 9)
        {
            displayActorsInMovie(movieList);
        }

        else if (choice == 10)
        {
            int actorID;
            cout << "Enter Actor ID: ";
            cin >> actorID;
            BinaryNode* actor = actorTree.search(actorID);
            castTable.displayKnownActors(actor, actorTree);
        }

        else if (choice == 11) 
        {
            rateActor(actorTree);
        }

        else if (choice == 12) 
        {
            rateMovie(movieList);
        }

        else if (choice == 13) 
        {
            recommendActors(actorTree);
        }

        else if (choice == 14) 
        {
            recommendMovies(movieList);
        }

        else if (choice == 0) {
            cout << "\nExiting ..." << endl;
            exit = true;
        }

        /*else 
        {
            cout << "Invalid choice." << endl;
        }*/

    }  // Continue until the user chooses to exit

    return 0;
}


