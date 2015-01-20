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

// 'Entry' functions

void Entry::loadDate(std::string d){ //move inline
    date = d;
}
void Entry::loadAmount(float amnt){ //move inline
    amount = amnt;
}
void Entry::setDate(std::string d){
    unsigned int size = (int)d.length();
    unsigned int slashCount = 0;
    unsigned int digitCount = 0;
    
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
    { date = d; }
    else
    {
        cout << "Try Again: ";
        cin >> d;
        setDate(d);
    }
}
void Entry::setAmount(float amnt){
    unsigned int buf;
    while(amnt == 0)
    {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // check note
        cout << "Try Again: $";
        cin >> amnt;
    }
    buf = amnt * 100;
    amnt = buf / 100.0;
    amount = amnt;
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


// 'Profits' functions
Profits::Profits(void){
    amount = 0.0;
    date = "00/00/00";
}
Profits::~Profits(){
    //destructor;
}
void Profits::printEntry(void){
        cout << date;
        cout << " . . . $";
        cout << fixed << setprecision(2) << amount << endl;
}


// 'Expenses' Functions
Expenses::Expenses(void){
    amount = 0.0;
    date = "00/00/00";
    reason = "NaNaNa";
}
Expenses::~Expenses(){
    //destructor;
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

void drawSubMenu(std::string category)
{
    cout << "\n\t\t*******************************\n"
    "\t\t*                             *\n"\
    "\t\t*   (1) Add Input             *\n"
    "\t\t*   (2) Remove Input          *\n"
    "\t\t*   (3) View All              *\n"
    "\t\t*   (4) Return to main menu   *\n"
    "\t\t*                             *\n"
    "\t\t*******************************\n";
    
    cout << endl << "How will you modify " << category << ": ";
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
        inVector[i].loadAmount(std::stod(buffer));
        std::getline(inFile,buffer,',');
        inVector[i].setReason(buffer);
        std::getline(inFile,buffer,'\r');
        inVector[i].loadDate(buffer);
    }
    inFile.close();
}


// 'loadProfits' will read inputted file and load values on to profits vector
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
        inVector[i].loadDate(buffer);
        
        std::getline(inFile,buffer,'$');//skip dollar sign
        
        std::getline(inFile,buffer,'\n');
        inVector[i].loadAmount(std::stod(buffer));
    }
    inFile.close();
}


// 'inputExpense' will get values from user and then append the entries to the vector.
Expenses inputExpense(Expenses newInput)
{
    float inAmount;
    string inDate(9, '\0');
    string inReason(41, '\0');
    
    cout << "Give me the date: " ;
    cin >> inDate;
    newInput.setDate(inDate);
    cout << "Give me the amount: $";
    cin >> inAmount;
    newInput.setAmount(inAmount);
    cout << "Give me the reason (40 character limit): ";
    cin.ignore();
    getline (cin,inReason);
    while (inReason.length() > 40)
    {
        cin.clear();
        cout << "Try Again: ";
        getline (cin,inReason);
    }
    newInput.setReason(inReason);
    return newInput;
}


// 'inputProfit' will get values from user and then append the entries to the vector.
Profits inputProfit(Profits newInput)
{
    float inAmount;
    string inDate(9, '\0');
    
    cout << "Give me the date: " ;
    cin >> inDate;
    newInput.setDate(inDate);
    cout << "Give me the amount: $";
    cin >> inAmount;
    newInput.setAmount(inAmount);
    return newInput;
}








