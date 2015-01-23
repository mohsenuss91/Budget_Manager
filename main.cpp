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
             Improve write Function
             Implement view function that allows manual input.
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
    
    // initialize variables needed to run menu's
    unsigned int inChoice;
    char inChar;
    
    
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
                inChoice = 0;
                    while (inChoice != 4)
                    {
                        drawSubMenu("Checkings");
                        cin.clear(); cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        cin >> inChoice;
                        if(inChoice == 1)
                        {
                            static Entry newInput;
                            checkings.push_back( inputEntry(newInput) );
                            setChanged("Checkings");
                            
                        }
                        else if (inChoice == 2)
                        {
                            cout << "Are you sure you want to remove last input? (Y/N): ";
                            cin >>inChar;
                            
                            if (inChar == 'Y' || inChar == 'y')
                            { 
                                if(checkings.size() > 0)
                                {
                                    cout << "Removing last entry..." << endl;
                                    checkings.pop_back();
                                    setChanged("Checkings", true);
                                }
                                else
                                {
                                    cout << "NO ENTRIES REMAIN..." << endl;
                                }
                            }
                            else
                            {
                                cout << "Returning to previous menu...\n";
                            }
                           
                        }
                        else if (inChoice == 3)
                        {
                            cout << "\nCHECKINGS\n";
                            for (int i = 0; i < checkings.size(); i++)
                            {
                                cout << setw(3) << i+1 << ": ";
                                checkings[i].printEntry(false);
                            }
                        }
                        
                        else if (inChoice == 4)
                        { cout << "Returning to main menu...\n\n"; }
                        
                        else
                        { cout << "Invalid Input.\n"; }
                    }
                    break;
            }
            
            // Option #2 - Brings up editing menu for Savings
            case 2 :
            {
                inChoice = 0;
                    while (inChoice != 4)
                    {
                        drawSubMenu("Savings");
                        cin.clear(); cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        cin >> inChoice;
                        if(inChoice == 1)
                        {
                            static Entry newInput;
                            savings.push_back( inputEntry(newInput) );
                            setChanged("Savings");
                        }
                        else if (inChoice == 2)
                        {
                            cout << "Are you sure you want to remove last input? (Y/N): ";
                            cin >>inChar;
                            
                            if (inChar == 'Y' || inChar == 'y')
                            {
                                if(savings.size() > 0)
                                {
                                    cout << "Removing last entry..." << endl;
                                    savings.pop_back();
                                    setChanged("Savings", true);
                                }
                                else
                                {
                                    cout << "NO ENTRIES REMAIN..." << endl;
                                }
                            }
                            else
                            {
                                cout << "Returning to previous menu...\n";
                            }
                            
                        }
                        else if (inChoice == 3)
                        {
                            cout << "\nSAVINGS\n";
                            for (int i = 0; i < savings.size(); i++)
                            {
                                cout << setw(2) << i+1 << ": ";
                                savings[i].printEntry();
                            }
                        }
                        
                        else if (inChoice == 4)
                        { cout << "Returning to main menu...\n\n"; }
                        
                        else
                        { cout << "Invalid Input.\n"; }
                    }
                break;
            }
            
            // Option #3 - Brings up editing menu for Expenses
            case 3 :
            {
                inChoice = 0;
                    while (inChoice != 4)
                    {
                        drawSubMenu("Expenses");
                        
                        cin >> inChoice;
                        cin.clear(); cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        if(inChoice == 1)
                        {
                            static Entry newExpense;
                            expenses.push_back( inputEntry(newExpense, true) );
                            setChanged("Expenses");
                        }
                        else if (inChoice == 2)
                        {
                            cout << "Are you sure you want to remove last input? (Y/N): ";
                            cin >>inChar;
                            
                            if (inChar == 'Y' || inChar == 'y')
                            {
                                if(expenses.size() > 0)
                                {
                                    cout << "Removing last entry..." << endl;
                                    expenses.pop_back();
                                    setChanged("Expenses", true);
                                }
                                else
                                {
                                    cout << "NO ENTRIES REMAIN..." << endl;
                                }
                            }
                            else
                            {
                                cout << "Returning to previous menu...\n";
                            }
                            
                        }
                        else if (inChoice == 3)
                        {
                            cout << "\nEXPENSES\n";
                            for (int i = 0; i < expenses.size(); i++)
                            {
                                cout << setw(3) << i+1 << ": ";
                                expenses[i].printEntry(true);
                            }
                        }
                        
                        else if (inChoice == 4)
                        { cout << "Returning to main menu...\n\n"; }
                        
                        else
                        { cout << "Invalid Input.\n"; }
                    }
                break;
            }
                
             // Option #4 - Brings up editing menu for Special Expenses
            case 4 :
            {
                inChoice = 0;
                    while (inChoice != 4)
                    {
                        drawSubMenu("Special Expenses");
                        cin >> inChoice;
                        cin.clear(); cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        if(inChoice == 1)
                        {
                            static Entry newExpense;
                            specialExpenses.push_back( inputEntry(newExpense, true) );
                            setChanged("Special Expenses");
                        }
                        else if (inChoice == 2)
                        {
                            cout << "Are you sure you want to remove last input? (Y/N): ";
                            cin >>inChar;
                            
                            if (inChar == 'Y' || inChar == 'y')
                            {
                                if(specialExpenses.size() > 0)
                                {
                                    cout << "Removing last entry..." << endl;
                                    specialExpenses.pop_back();
                                    setChanged("Special Expenses", true);
                                }
                                else
                                {
                                    cout << "NO ENTRIES REMAIN..." << endl;
                                }
                            }
                            else
                            {
                                cout << "Returning to previous menu...\n";
                            }
                            
                        }
                        else if (inChoice == 3)
                        {
                            cout << "\nSPECIAL EXPENSES\n";
                            for (int i = 0; i < specialExpenses.size(); i++)
                            {
                                cout << setw(2) << i+1 << ": ";
                                specialExpenses[i].printEntry(true);
                            }
                        }
                        
                        else if (inChoice == 4)
                        { cout << "Returning to main menu...\n\n"; }
                        
                        else
                        { cout << "Invalid Input.\n"; }
                    }
                break;
            }
                
             // Option #5 - Views last 20 inputs of all vectors
            case 5 :
            {
                cout << "\nCHECKINGS\n";
                for (int i = checkings.size()-20;i<checkings.size(); i++) {
                    cout << setw(3) << i+1 << ": ";
                    checkings[i].printEntry(false);
                }
                
                cout << "\nSAVINGS\n";
                for (int i = savings.size()-20;i<savings.size(); i++) {
                    cout << setw(2) << i+1 << ": ";
                    savings[i].printEntry();
                }
                cout << "\nEXPENSES\n";
                for (int i = expenses.size()-20;i<expenses.size(); i++) {
                    cout << setw(3) << i+1 << ": ";
                    expenses[i].printEntry(true);
                }
                
                cout << "\nSPECIALEXPENSES\n";
                for (int i = specialExpenses.size()-8;i<specialExpenses.size(); i++) {
                    cout << setw(2) << i+1 << ": ";
                    specialExpenses[i].printEntry(true);
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
                        saveEntry(NUMOFEXPENSES, "data/expenses.csv", expenses, true);
                    if(isChanged("Special Expenses"))
                        saveEntry(NUMOFSPECIALEXPENSES, "data/specialexpenses.csv", specialExpenses, true);
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
