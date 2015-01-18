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
    int inChoice;
    
    // loads files into memory
    loadExpense("data/expenses.csv", expenses, NUMOFEXPENSES);
    loadExpense("data/specialexpenses.csv", specialExpenses, NUMOFSPECIALEXPENSES);
    loadProfits("data/checkings.csv", checkings, NUMOFCHECKINGS);
    loadProfits("data/savings.csv", savings, NUMOFSAVINGS);
    
    
    // prints out the main menu
    drawMainMenu();
    
    do
    {
        cout << endl << "Select an option: ";
        cin >> inChoice;
        switch (inChoice)
        {
            case 1 :
            {
                drawSubMenu("Checkings");
                cin >> inChoice;
                if(inChoice == 1)
                {
                    static Profits newInput;
                    savings.push_back( inputProfit(newInput) );
                    break;
                }
                else
                {
                    cout << "Invalid Input." << endl;
                }
                break;
            }
                
            case 2 :
            {
                static Profits newInput;
                checkings.push_back( inputProfit(newInput) );
                break;
            }
                
            case 3 :
            {
                static Expenses newInput;
                expenses.push_back( inputExpense(newInput) );
                break;
            }
                
            case 4 :
            {
                static Expenses newInput;
                specialExpenses.push_back( inputExpense(newInput) );
                break;
            }
                
            case 5 :
            {
                cout << "\nCHECKINGS\n";
                for (int i = NUMOFCHECKINGS-4;i<NUMOFCHECKINGS+1; i++) {
                    checkings[i].printEntry();
                }
                
                cout << "\nSAVINGS\n";
                for (int i = NUMOFSAVINGS-4;i<NUMOFSAVINGS+1; i++) {
                    savings[i].printEntry();
                }
                cout << "\nEXPENSES\n";
                for (int i = NUMOFEXPENSES-4;i<NUMOFEXPENSES+1; i++) {
                    expenses[i].printEntry();
                }
                
                cout << "\nSPECIALEXPENSES\n";
                for (int i = NUMOFSPECIALEXPENSES-4;i<NUMOFSPECIALEXPENSES+1; i++) {
                    specialExpenses[i].printEntry();
                }
                break;
            }
            
            case 113 : {}
            case 81 : {exit(EXIT_SUCCESS);} // Quits for 'Q' or 'q' entry
            case 0 : {}
            default : {break;}// Retries for invalid or 0 entry
        }
    }
    while (inChoice != 0);
    return(EXIT_SUCCESS);
}
