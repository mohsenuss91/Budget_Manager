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

#include <iostream>
#include <fstream> //include for fopen and fclose
#include <vector>
#include "classes.h" //include for classes

using namespace std;

int main(void)
{
    /************************************
            Pseudocode ToDo
     Open files(checks.csv, tips.csv, expenses.csv, specialexepenses.csv).
     ?? Read and check first line for numbers of entries ??
     Initialize vectors to number of entries size per file.
     Load all the values from the csv files onto the vectors.
     Add submenu to 4 main options.
     Change cases to push.back() new value onto vector.
     signal change has occured to write changes when closing.
     ?? Increase number of entries value ??
     Implement view function to show only 10 lines per viewing but allow manual input.
     implement view all function.
     Implement save function.
     ***********************************/
    // initialize variables needed for program
    vector<Profits> tips(10);
    vector<Expenses> expenses(10);
    int inChoice;
    float inAmount;
    std::string inDate(9, '\0');
    std::string inReason(41, '\0');
    
    ifstream expensesFile;
    expensesFile.open("data/expenses.csv");
    
    // prints out the main menu
    drawMainMenu();
    
    // start of temp
    tips[0].setAmount(250.50);
    tips[0].setDate("12/25/14");
    // end of temp
    
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
                std::getline (std::cin,inReason);
                while (inReason.length() > 40)
                {
                    cin.clear();
                    //cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    cout << "Try Again: ";
                    std::getline (std::cin,inReason);
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
                tips[0].printEntry();
                expenses[0].printEntry();
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