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
             Fix appending write
             Clean load & save functions
             Indicate wrong format and skip if file cannot be loaded
             Implement modify function
             Impement search for activity by specific date
             Impement search for activity by year
             Impement search for activity by reason
             Impement search for activity by amount
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
    const unsigned int NUMOFCHECKINGS = getAmountOfValues("data/checkings.csv");
    const unsigned int NUMOFSAVINGS = getAmountOfValues("data/savings.csv");
    const unsigned int NUMOFEXPENSES = getAmountOfValues("data/expenses.csv");
    const unsigned int NUMOFSPECIALEXPENSES = getAmountOfValues("data/specialexpenses.csv");
    
    /*const unsigned int NUMOFCHECKINGS = 323;
    const unsigned int NUMOFSAVINGS = 81;
    const unsigned int NUMOFEXPENSES = 437;
    const unsigned int NUMOFSPECIALEXPENSES = 11;*/
    
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
    
    // initialize variables needed to run menu's
    unsigned int inChoice;

    /*
    //Prints out memory needed
    cout << sizeof("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa") << "bytes per string, 400 emptry string would be " << sizeof("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa")*400/8 << " bytes" << endl;
    cout << sizeof(string*) << "bytes per string pointer, 400 emptry string pointers would be " <<  sizeof(string*)*400/8 << " kb" << endl; 
     */
    
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
                cout << "\nCHECKINGS\n";
                for (unsigned int i = checkings.size()-20;i<checkings.size(); i++) {
                    cout << setw(3) << i+1 << ": ";
                    checkings[i].printEntry();
                }
                
                cout << "\nSAVINGS\n";
                for (unsigned int i = savings.size()-20;i<savings.size(); i++) {
                    cout << setw(2) << i+1 << ": ";
                    savings[i].printEntry();
                }
                cout << "\nEXPENSES\n";
                for (unsigned int i = expenses.size()-20;i<expenses.size(); i++) {
                    cout << setw(3) << i+1 << ": ";
                    expenses[i].printEntry();
                }
                
                cout << "\nSPECIALEXPENSES\n";
                for (unsigned int i = specialExpenses.size()-8;i<specialExpenses.size(); i++) {
                    cout << setw(2) << i+1 << ": ";
                    specialExpenses[i].printEntry();
                }
                
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
                    cout << "Nothing to save...\n";
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
