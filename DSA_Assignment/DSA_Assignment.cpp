#include <iostream>
using namespace std;

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
    int choice;
    do {
        choice = displayMenu();  // Show menu and get the user's choice

        if (choice == 1) 
        {
            
        }

        else if (choice == 2) 
        {
            
        }

        else if (choice == 3) 
        {
            
        }

        else if (choice == 4) 
        {
            
        }

        else if (choice == 5) 
        {
            
        }

        else if (choice == 6) 
        {

        }

        else if (choice == 7)
        {

        }

        else if (choice == 8)
        {

        }

        else if (choice == 9)
        {

        }

        else if (choice == 10)
        {

        }

        else 
        {
            cout << "Invalid choice." << endl;
        }

    } while (choice != 0);  // Continue until the user chooses to exit
    
    cout << "\nExiting ..." << endl;

    return 0;
}


