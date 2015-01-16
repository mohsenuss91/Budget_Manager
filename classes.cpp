//
//  classes.cpp
//
//  Holds all the implementations of the
//  functions and classes for main.cpp
//
//  Created by Ivan Hernandez on 1/7/15.
//  Copyright (c) 2014 Ivan Hernandez. All rights reserved.
//

#include <iostream>
#include <fstream> //include for fopen and fclose
#include <limits> //include for numeric_limits
#include <string> //include for string
#include <cstdlib> //include for exit()
#include <cctype> //include for isdigit
#include "classes.h" //include for classes

using namespace std;

// 'Profits' functions

void Profits::setDate(std::string d){
    date = d;
}
void Profits::setAmount(float amnt){
    amount = amnt;
}
void Profits::printEntry(void){
        cout << date;
        cout << " . . . $";
        cout << amount ;
}

// 'Expenses' Functions

void Expenses::setDate(std::string d){
    date = d;
}
void Expenses::setAmount(float amnt){
    amount = amnt;
}
void Expenses::setReason(std::string rsn){
    reason = rsn;
}
void Expenses::printEntry(void){
    cout << date;
    cout << " . . . $";
    cout << fixed << setprecision(2) << amount;
    cout << " . . . ";
    cout << reason << endl;
}

// 'drawMainMenu' prints the main menu

void drawMainMenu(void)
{
    cout << "\n\t\t***********************************\n"
    "\t\t*                                 *\n"
    "\t\t*   (Q) Quit                      *\n"
    "\t\t*   (1) Add/View Checkings        *\n"
    "\t\t*   (2) Add/View Savings          *\n"
    "\t\t*   (3) Add/View Expenses         *\n"
    "\t\t*   (4) Add/View Special Expenses *\n"
    "\t\t*   (5) View Total Balances       *\n"
    "\t\t*                                 *\n"
    "\t\t***********************************\n";
}

 //'checkAmount' will verify if entered number is valid and will truncate the excess decimals

float checkAmount(float val)
{
    int buf;
    while(val == 0)
    {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // check note
        cout << "Try Again: $";
        cin >> val;
    }
    buf = val * 100;
    val = buf / 100.0;
    return val;
}
/* 
 NOTE:
 numeric_limits<variable_type> returns limit that the variable can hold.
 adding ::max at the end ^ will return maximum limit.
 streamsize counts characters in a stream.
 effectivley ignoring every single character in the stream.
 cin.ignore takes a second parameter that mean stop if this character is
 found even if first parameter isnt met, so basically empties cin stream.
*/

// 'checkDate' will verify date is valid by checking for 2 slashes and atleast 4 but not more then 6 integers

std::string checkDate(std::string d)
{
    int size = d.length();
    int slashCount = 0;
    int digitCount = 0;
    /*DELETE
    if (size > 8)
    {
        cout << "Try Again: ";
        cin >> d;
        d = checkDate(d);
        return d;
    }
     */
    
    for (int i = 0; i < size; i++)
    {
        if (d[i] == '/')
            slashCount++;
        else if (isdigit(d[i]))
            digitCount++;
        else
            digitCount = 0;
    }
    
    if (slashCount == 2 && digitCount >= 4 && digitCount <= 6) // correct date format 1/1/15 or 12/12/15
        { return d; }
    else
    {
        cout << "Try Again: ";
        cin >> d;
        d = checkDate(d);
        return d;
    }
}

// 'loadExpense' will read inputted file and load values on to expenses vector

void loadExpense(std::string filename, std::vector<Expenses> &inVector,int size)
{
    std::string buffer(41, '\0');
    std::ifstream inFile(filename);
    if(!inFile)
    {
        cout << "Error opening file named \"" << filename << "\". Check if it exists.\n";
        exit(2);
    }
    for (int i = 0; i < size; i++)
    {
        std::getline(inFile,buffer,'$'); //skip dollar sign
        
        std::getline(inFile,buffer,',');
        inVector[i].setAmount(std::stod(buffer));
        std::getline(inFile,buffer,',');
        inVector[i].setReason(buffer);
        std::getline(inFile,buffer,'\r');
        inVector[i].setDate(buffer);
    }
    inFile.close();
}

// 'loadExpense' will read inputted file and load values on to profits vector

void loadProfits(std::string filename, std::vector<Profits> &inVector,int size)
{
    std::string buffer(9, '\0');
    std::ifstream inFile(filename);
    if(!inFile)
    {
        cout << "Error opening file named \"" << filename << "\". Check if it exists.\n";
        exit(2);
    }
    for (int i = 0; i < size; i++)
    {
        std::getline(inFile,buffer,',');
        inVector[i].setDate(buffer);
        
        std::getline(inFile,buffer,'$');//skip dollar sign
        
        std::getline(inFile,buffer,'\r');
        inVector[i].setAmount(std::stod(buffer));
    }
    inFile.close();
}


// 'getExpense' will get values from user and then append the entries to the vector.

Expenses getSingleExpense(Expenses temp)
{
    float inAmount;
    string inDate(9, '\0');
    string inReason(41, '\0');
    
    cout << "Give me the date: " ;
    cin >> inDate;
    inDate = checkDate(inDate);
    temp.setDate(inDate);
    cout << "Give me the amount: $";
    cin >> inAmount;
    inAmount = checkAmount(inAmount);
    temp.setAmount(inAmount);
    cout << "Give me the reason (40 character limit): ";
    cin.ignore();
    getline (cin,inReason);
    while (inReason.length() > 40)
    {
        cin.clear();
        cout << "Try Again: ";
        getline (cin,inReason);
    }
    temp.setReason(inReason);
    return temp;
}

Profits getSingleProfit(Profits temp)
{
    float inAmount;
    string inDate(9, '\0');
    
    cout << "Give me the date: " ;
    cin >> inDate;
    inDate = checkDate(inDate);
    temp.setDate(inDate);
    cout << "Give me the amount: $";
    cin >> inAmount;
    inAmount = checkAmount(inAmount);
    temp.setAmount(inAmount);
    return temp;
}








