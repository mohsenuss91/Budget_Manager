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
             ?? Read and check first line for numbers of entries ??
             Add submenu to 4 main options.
             signal change has occured to write changes when closing.
             ?? Increase number of entries value ??
             Implement view function to show only 10 lines per viewing but allow manual input.
             implement view all function.
             Implement save function.
             Fix output screen.
            **********************************************************************************/

#include <iostream>
#include <cstdlib> //include for exit()
#include <limits> //include for numeric_limits
#include <vector> //include for vector arrays
#include "classes.h" //include for classes

using namespace std;

int main(void)
{
    // initialize variables needed for program
    const int NUMOFEXPENSES = 432;
    const int NUMOFSPECIALEXPENSES = 11;
    const int NUMOFCHECKINGS = 313;
    const int NUMOFSAVINGS = 80;
    vector<Profits> checkings(NUMOFCHECKINGS);
    vector<Profits> savings(NUMOFSAVINGS);
    vector<Expenses> expenses(NUMOFEXPENSES);
    vector<Expenses> specialExpenses(NUMOFSPECIALEXPENSES);
    unsigned int inChoice;
    char inChar;
    
    // loads files into memory
    loadExpense("data/expenses.csv", expenses);
    loadExpense("data/specialexpenses.csv", specialExpenses);
    loadProfits("data/checkings.csv", checkings);
    loadProfits("data/savings.csv", savings);
    
    
    
    
    do
    {
        // prints out the main menu
        drawMainMenu();
        cout << endl << "Select an option: ";
        cin >> inChoice;
        switch (inChoice)
        {
            // Option #1
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
                            static Profits newInput;
                            checkings.push_back( inputProfit(newInput) );
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
                            for (int i = 0; i < checkings.size(); i++) {
                                cout << i+1 << ": ";
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
            
            // Option #2
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
                            static Profits newInput;
                            savings.push_back( inputProfit(newInput) );
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
                            for (int i = 0; i < savings.size(); i++) {
                                cout << i+1 << ": ";
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
            
            // Option #3
            case 3 :
            {
                inChoice = 0;
                    while (inChoice != 4)
                    {
                        drawSubMenu("Expenses");
                        cin.clear(); cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        cin >> inChoice;
                        if(inChoice == 1)
                        {
                            static Expenses newExpense;
                            expenses.push_back( inputExpense(newExpense) );
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
                            for (int i = 0; i < expenses.size(); i++) {
                                cout << i+1 << ": ";
                                expenses[i].printEntry();
                            }
                        }
                        
                        else if (inChoice == 4)
                        { cout << "Returning to main menu...\n\n"; }
                        
                        else
                        { cout << "Invalid Input.\n"; }
                    }
                break;
            }
                
             // Option #4
            case 4 :
            {
                inChoice = 0;
                    while (inChoice != 4)
                    {
                        drawSubMenu("Special Expenses");
                        cin.clear(); cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        //FIX: ignores input after entering new data for expense and special epxense
                        cin >> inChoice;
                        if(inChoice == 1)
                        {
                            static Expenses newExpense;
                            specialExpenses.push_back( inputExpense(newExpense) );
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
                            for (int i = 0; i < specialExpenses.size(); i++) {
                                cout << i+1 << ": ";
                                specialExpenses[i].printEntry();
                            }
                        }
                        
                        else if (inChoice == 4)
                        { cout << "Returning to main menu...\n\n"; }
                        
                        else
                        { cout << "Invalid Input.\n"; }
                    }
                break;
            }
                
             // Option #5
            case 5 :
            {
                cout << "\nCHECKINGS\n";
                for (int i = checkings.size()-19;i<checkings.size(); i++) {
                    checkings[i].printEntry(false);
                }
                
                cout << "\nSAVINGS\n";
                for (int i = savings.size()-19;i<savings.size(); i++) {
                    savings[i].printEntry();
                }
                cout << "\nEXPENSES\n";
                for (int i = expenses.size()-19;i<expenses.size(); i++) {
                    expenses[i].printEntry();
                }
                
                cout << "\nSPECIALEXPENSES\n";
                for (int i = specialExpenses.size()-9;i<specialExpenses.size(); i++) {
                    specialExpenses[i].printEntry();
                }
                
                cin.ignore();
                cout << endl << "Press [ENTER] to continue...";
                cin.get();
                break;
            }
            
            // Other Options
            case 113 : {}
            case 81 : {exit(EXIT_SUCCESS);} // Quits for 'Q' or 'q' entry
            case 0 : {}
            default : {break;}// Retries for invalid or 0 entry
        }
    }
    while (inChoice != 0);
    return(EXIT_SUCCESS);
}
