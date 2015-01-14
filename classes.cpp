//
//  classes.cpp
//
//  Holds all the implementations of the
//  functions and classes for main.cpp
//
//  Created by Ivan Hernandez on 1/7/15.
//  Copyright (c) 2014 Ivan Hernandez. All rights reserved.
//

#include "classes.h"
#include <iostream>
using namespace std;

// 'Profits' functions

void Profits::setDate(std::string d){
    date = d;
}
void Profits::setAmount(float amnt){
    amount = amnt;
}
void Profits::printEntry(void){
        cout << date; // print date
        cout << " . . . $"; // print spacer
        cout << fixed << setprecision(2) << (float)amount / 100 << endl; // print amount
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
        cout << date; // print date
        cout << " . . . $"; // print spacer
    cout << fixed << setprecision(2) << amount << endl;//(float)amount / 100 << endl; // print amount
        cout << "Reason: " << reason << endl; // print reason
}

// 'drawMainMenu' Function to print the main menu

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


float checkAmount(float val)
{
    int buf; // buf will be used to truncate float
    while(val == 0) // loop to prevent inputs that are not integers.
    {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // check note
        cout << "Try Again: $";
        cin >> val;
    }
    // does truncation and final assignment
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


std::string checkDate(std::string d)
{
    int size = d.length();
    int slashCount = 0;
    int digitCount = 0;
    const int SLASH = 47;
    const int NINE = 57;
    
    if (size > 8)
    {
        cout << "Try Again: ";
        cin >> d;
        d = checkDate(d);
        return d;
    }
    
    for (int i = 0; i < size; i++)
    {
        if (d[i] == '/')
            slashCount++;
        else if (d[i] >= SLASH && d[i] <= NINE) //replace with isDigit()
            digitCount++;
    }
    
    if (slashCount == 2 && digitCount >= 4) // correct date format 1/1/15
        { return d; }
    else
    {
        cout << "Try Again: ";
        cin >> d;
        d = checkDate(d);
        return d;
    }
}