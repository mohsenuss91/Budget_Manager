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
             Change cases to push.back() new value onto vector.
             signal change has occured to write changes when closing.
             ?? Increase number of entries value ??
             Implement view function to show only 10 lines per viewing but allow manual input.
             implement view all function.
             Implement save function.
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
    const int NUMOFTIPS = 313;
    const int NUMOFCHECKS = 80;
    vector<Profits> tips(NUMOFTIPS);
    vector<Profits> checks(NUMOFCHECKS);
    vector<Expenses> expenses(NUMOFEXPENSES);
    vector<Expenses> specialExpenses(NUMOFSPECIALEXPENSES);
    int inChoice;
    
    
    
    float inAmount;
    string inDate(9, '\0');
    string inReason(41, '\0');
    
    // loads files into memory
    loadExpense("data/expenses.csv", expenses, NUMOFEXPENSES);
    loadExpense("data/specialexpenses.csv", specialExpenses, NUMOFSPECIALEXPENSES);
    loadProfits("data/tips.csv", tips, NUMOFTIPS);
    loadProfits("data/checks.csv", checks, NUMOFCHECKS);
    
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
                cout << "Under construction!\n\n"; break;
            }
                
            case 2 :
            {
                cout << "Under construction!\n\n"; break;
            }
                
            case 3 :
            {
                cout << "Give me the date: " ;
                cin >> inDate;
                inDate = checkDate(inDate);
                expenses[0].setDate(inDate);
                cout << "Give me the amount: $";
                cin >> inAmount;
                inAmount = checkAmount(inAmount);
                expenses[0].setAmount(inAmount);
                cout << "Give me the reason (40 character limit): ";
                cin.ignore();
                getline (cin,inReason);
                while (inReason.length() > 40)
                {
                    cin.clear();
                    //cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    cout << "Try Again: ";
                    getline (cin,inReason);
                }
                expenses[0].setReason(inReason);
                break;
            }
                
            case 4 :
            {
                cout << "Under construction!\n\n"; break;
            }
                
            case 5 :
            {
                cout << "\nEXPENSES\n";
                for (int i = NUMOFEXPENSES-10;i<NUMOFEXPENSES; i++) {
                    expenses[i].printEntry();
                }
                
                cout << "\nSPECIALEXPENSES\n";
                for (int i = NUMOFSPECIALEXPENSES-10;i<NUMOFSPECIALEXPENSES; i++) {
                    specialExpenses[i].printEntry();
                }
                
                cout << "\nTIPS";
                for (int i = NUMOFTIPS-10;i<NUMOFTIPS; i++) {
                    tips[i].printEntry();
                }
                
                cout << "\n\nCHECKS";
                for (int i = NUMOFCHECKS-10;i<NUMOFCHECKS; i++) {
                    checks[i].printEntry();
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
