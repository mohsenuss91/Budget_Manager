//
//  main.cpp
//  
//  Budget Manager
//  A simple c++ implementation
//  of my finance spreadsheet.
//
//  Created by Ivan Hernandez on 1/6/15.
//  Copyright (c) 2014 Ivan Hernandez. All rights reserved.
//

            /********************************************************************************
                                                    ToDo
             Impement search for activity by specific date with binary search
             Impement search for activity by year
             Impement search for activity by reason
             Impement search for activity by amount
             Indicate wrong format and skip if file cannot be loaded
            **********************************************************************************/

#include <iostream>
#include <cstdlib> //include for exit()
#include <limits> //include for numeric_limits
#include <vector> //include for vector arrays
#include <iomanip> //include for cout formatting
#include <fstream>
#include "classes.h" //include for classes

using namespace std;

int main(void)
{
    
    // variables needed to initialize right amount of entries at startup
    const int NUMOFCHECKINGS = getAmountOfValues("/Users/Ivan/Code/Budget_Manager/data/checkings.csv");
    const int NUMOFSAVINGS = getAmountOfValues("/Users/Ivan/Code/Budget_Manager/data/savings.csv");
    const int NUMOFEXPENSES = getAmountOfValues("/Users/Ivan/Code/Budget_Manager/data/expenses.csv");
    const int NUMOFSPECIALEXPENSES = getAmountOfValues("/Users/Ivan/Code/Budget_Manager/data/specialexpenses.csv");
    
    // initialize vector's needed to store all inputs
    vector<Entry> checkings(NUMOFCHECKINGS);
    vector<Entry> savings(NUMOFSAVINGS);
    vector<Entry> expenses(NUMOFEXPENSES);
    vector<Entry> specialExpenses(NUMOFSPECIALEXPENSES);
    
    // loads files into memory
    loadEntry("/Users/Ivan/Code/Budget_Manager/data/checkings.csv", checkings);
    loadEntry("/Users/Ivan/Code/Budget_Manager/data/savings.csv", savings);
    loadEntry("/Users/Ivan/Code/Budget_Manager/data/expenses.csv", expenses, true);
    loadEntry("/Users/Ivan/Code/Budget_Manager/data/specialexpenses.csv", specialExpenses, true);
    
    /* START uncomment on none mac devices
    // variables needed to initialize right amount of entries at startup
    const int NUMOFCHECKINGS = getAmountOfValues("data/checkings.csv");
    const int NUMOFSAVINGS = getAmountOfValues("data/savings.csv");
    const int NUMOFEXPENSES = getAmountOfValues("data/expenses.csv");
    const int NUMOFSPECIALEXPENSES = getAmountOfValues("data/specialexpenses.csv");
    
    // initialize vector's needed to store all inputs
    vector<Entry> checkings(NUMOFCHECKINGS);
    vector<Entry> savings(NUMOFSAVINGS);
    vector<Entry> expenses(NUMOFEXPENSES);
    vector<Entry> specialExpenses(NUMOFSPECIALEXPENSES);
    
    // loads files into memory
    loadEntry("data/checkings.csv", checkings);
    loadEntry("data/savings.csv", savings);
    loadEntry("data/expenses.csv", expenses, true);
    loadEntry("data/specialexpenses.csv", specialExpenses, true);
     END */
    
    // initialize variables needed to run menu's
    unsigned int inChoice;

    
    //Prints out memory needed
    /*cout << sizeof("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa") << "bytes per string, 400 emptry string would be " << sizeof("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa")*400/8 << " bytes" << endl;
    cout << sizeof(string*) << "bytes per string pointer, 400 emptry string pointers would be " <<  sizeof(string*)*400/8 << " kb" << endl; */
     
    
    do
    {
        // prints out the main menu
        drawMainMenu();
        cout << endl << "Select an option: ";
        cin >> inChoice;
        switch (inChoice)
        {
            // Option #1 - Brings up editing menu for Checkings
            case 1 :
            {
                subMenuController("Checkings", checkings);
                break;
            }
            
            // Option #2 - Brings up editing menu for Savings
            case 2 :
            {
                subMenuController("Savings", savings);
                break;
            }
            
            // Option #3 - Brings up editing menu for Expenses
            case 3 :
            {
                subMenuController("Expenses", expenses, true);
                break;
            }
                
             // Option #4 - Brings up editing menu for Special Expenses
            case 4 :
            {
                subMenuController("Special Expenses", specialExpenses, true);
                break;
            }
                
             // Option #5 - Views last 20 inputs of all vectors
            case 5 :
            {
                printVector("CHECKINGS", checkings);
                printVector("SAVINGS", savings);
                printVector("EXPENSES", expenses);
                printVector("SPECIAL EXPENSES", specialExpenses, 8);
                
                cin.ignore();
                cout << endl << "Press [ENTER] to continue...";
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                break;
            }
            
            // Quit Option - Saves and Quits
            case 0 :
            {
                cout << endl;
                
                if(!isChanged("Checkings") && !isChanged("Savings")
                 && !isChanged("Expenses") && !isChanged("Special Expenses"))
                {
                    cout << "No changes to save...\n";
                }
                else
                {
                    // Checks where isChanged flag is true and saves that vector to file
                    if(isChanged("Checkings"))
                        saveEntry(NUMOFCHECKINGS, "data/checkings.csv", checkings);
                    if(isChanged("Savings"))
                        saveEntry(NUMOFSAVINGS, "data/savings.csv", savings);
                    if(isChanged("Expenses"))
                        saveEntry(NUMOFEXPENSES, "data/expenses.csv", expenses);
                    if(isChanged("Special Expenses"))
                        saveEntry(NUMOFSPECIALEXPENSES, "data/specialexpenses.csv", specialExpenses);
                }
                
                cout << "Quitting...\n\n";
                break;
            }
                
            // Default option - Retries for invalid int input
            default : {cout << "Incorrect option...\n"; break;}
        }
    }
    while (inChoice != 0);
    return(EXIT_SUCCESS);
}
