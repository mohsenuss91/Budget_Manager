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
#include <string> //include for string, stod
#include <cstdlib> //include for exit()
#include <cctype> //include for isdigit
#include <cstdio>
#include "classes.h" //include for classes

using namespace std;


static bool checkingsChanged = false;
static bool savingsChanged = false;
static bool expensesChanged = false;
static bool specialExpensesChanged = false;
static bool deleteWasDone = false;

// 'Entry' functions
Entry::Entry(bool isExpense)
{
    amount = 0.0;
    date = "00/00/00";
    if(isExpense)
    {
        reason = new string;
        *reason = "NaNaNa";
    }
}
void Entry::loadDate(std::string d){ //move inline
    date = d;
}
void Entry::loadAmount(float amnt){ //move inline
    amount = amnt;
}
std::string Entry::getDate(void){ //move inline
    return date;
}
float Entry::getAmount(void){ //move inline
    return amount;
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
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "Try Again: $";
        cin >> amnt;
    }
    buf = amnt * 100;
    amnt = buf / 100.0;
    amount = amnt;
}

void Entry::printEntry(bool isExpense){
    cout << left; // align left
    cout << date;
    cout << "   . .   $";
    cout << fixed << setprecision(2)  << amount;
    if(isExpense)
    {
    cout << " . .   ";
    cout << *reason << endl;
    }
    cout << resetiosflags(std::ios::adjustfield); //realign right
}






// 'Profits' functions
Profits::Profits(void){
    amount = 0.0;
    date = "00/00/00";
}
Profits::~Profits(){
    //destructor;
}
void Profits::printEntry(bool showDecimals){
    cout << setw(8) << date;
    cout << " . . . $";
    
    if (showDecimals)
    { cout << fixed << setprecision(2) << setw(5) << amount << endl; }
    else
    { cout << setw(2) << amount << endl; }
    
}



// 'Expenses' Functions
Expenses::Expenses(void){
    amount = 0.0;
    date = "00/00/00";
    reason = new string;
    *reason = "NaNaNa";
}
Expenses::~Expenses(){
    delete reason;
    //destructor;
}
void Entry::setReason(std::string rsn){
    *reason = rsn;
}
std::string Entry::getReason(void){
    return *reason;
}
void Expenses::printEntry(void){
    cout << left; // align left
    cout << setw(8) << date;
    cout << "   . .   $";
    cout << fixed << setprecision(2) << setw(7) << amount;
    cout << " . .   ";
    cout << *reason << endl;
    cout << resetiosflags(std::ios::adjustfield); //realign right
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



// 'loadProfits' will read inputted file and load values on to profits vector
void loadProfits(std::string filename, std::vector<Profits> &inVector)
{
    std::string buffer(9, '\0');
    std::ifstream inFile(filename);
    if(!inFile)
    {
        cout << "Error opening file named \"" << filename << "\". Check if it exists.\n";
        exit(2);
    }
    for (int i = 0; std::getline(inFile,buffer,'$'); i++)
    // will read until getline fails and also reads in $ sign and skips it
    {
        
        std::getline(inFile,buffer,',');
        inVector[i].loadAmount(std::stod(buffer));
        
        std::getline(inFile,buffer,'\r');
        inVector[i].loadDate(buffer);
    }
    inFile.close();
}

// 'loadExpense' will read inputted file and load values on to expenses vector
void loadExpense(std::string filename, std::vector<Entry> &inVector)
{
    std::string buffer(41, '\0');
    std::ifstream inFile(filename);
    if(!inFile)
    {
        cout << "Error opening file named \"" << filename << "\". Nothing will be loaded from it.\n";
    }
    for (int i = 0; std::getline(inFile,buffer,'$'); i++)
        // will read until getline fails and also reads in $ sign and skips it
    {
        
        std::getline(inFile,buffer,',');
        inVector[i].loadAmount(std::stod(buffer));
        std::getline(inFile,buffer,',');
        inVector[i].setReason(buffer);
        std::getline(inFile,buffer,'\r');
        inVector[i].loadDate(buffer);
    }
    inFile.close();
}

// 'saveProfits' will write any changes in appropiate vector to the file
void saveProfits(int initialValues, std::string filename, std::vector<Profits> &inVector)
{
    //opens the file and does error checking
    std::ofstream inFile(filename, ios::app);
    if (!inFile)
    {
        cout << "Error opening file named \"" << filename << "\". New file will be made.\n";
    }
    
    
    //checks if values were added or subtracted and either appends or writes new file as a result
    if(deleteWasDone)
    {
        //create a new file to rewrite file without the deleted entries
        std::string newFilename = filename + ".new";
        std::fstream newFile(newFilename, std::ios::out);
        
        cout << "Deleting changes to " << filename << "...\n";
        
        //write the first entry without a newline and with a newline inside the for loop
        newFile << '$' << inVector[0].getAmount() << ',' << inVector[0].getDate();
        for (int i = 1; i < inVector.size(); i++)
        {
            newFile << '\r' << '$' << inVector[i].getAmount() << ',' << inVector[i].getDate();
        }
        
        //close all files
        inFile.close();
        newFile.close();
        
        //erase original file and rename new file to original file
        remove( filename.c_str() );
        rename( newFilename.c_str(), filename.c_str() );
    }
    else
    {
        cout << "Writing changes to " << filename << "...\n";
        for (int i = initialValues; i < inVector.size(); i++)
            inFile << '\r' << '$' << inVector[i].getAmount() << ',' << inVector[i].getDate();
        inFile.close();

    }
}

// 'saveExpense' will write any changes in appropiate vector to the file
void saveExpense(int initialValues, std::string filename, std::vector<Entry> &inVector)
{
    std::ofstream inFile(filename, ios::app);
    
    if (!inFile)
    {cout << "Error opening file named \"" << filename << "\". New file will be made.\n";}
    
    
    //checks if values were added or subtracted and either appends or writes new file as a result
    if(deleteWasDone)
    {
        //create a new file to rewrite file without the deleted entries
        std::string newFilename = filename + ".new";
        std::fstream newFile(newFilename, std::ios::out);
        
        cout << "Deleting changes to " << filename << "...\n";
        
        //write the first entry without a newline and with a newline inside the for loop
        newFile << '$' << inVector[0].getAmount() << ',' << inVector[0].getReason() << ',' << inVector[0].getDate();
        for (int i = 1; i < inVector.size(); i++)
        {
            newFile << '\r' << '$' << inVector[i].getAmount() << ',' << inVector[i].getReason() << ',' << inVector[i].getDate();
        }
        
        //close all files
        inFile.close();
        newFile.close();
        
        //erase original file and rename new file to original file
        remove( filename.c_str() );
        rename( newFilename.c_str(), filename.c_str() );

    }
    else
    {
        cout << "Writing changes to " << filename << "...\n";
        for (int i = initialValues; i < inVector.size(); i++)
        { inFile << '\r' << '$' << inVector[i].getAmount() << ',' << inVector[0].getReason() << ',' << inVector[i].getDate(); }
        inFile.close();
    }
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



// 'getAmountOfValues' returns the number of lines in a file
int getAmountOfValues(std::string filename)
{
    std::ifstream inFile(filename);
    std::string buffer;
    int i;
    for (i = 0; std::getline(inFile, buffer, '\r'); i++)
        /* do nothing */;
    return i;
}




// 'setChanged' will flag passed in vector name as changed
void setChanged(std::string vector, bool deleteDone)
{
    if(deleteDone)
        deleteWasDone = true;
    
    if (vector == "Checkings")
        checkingsChanged = true;
    
    else if (vector == "Savings")
        savingsChanged = true;
    
    else if (vector == "Expenses")
        expensesChanged = true;
    
    else if (vector == "Special Expenses")
        specialExpensesChanged = true;
    
    else
        cout << "Unable to set " << vector << " to changed!\n\n";
}

// 'isChanged' will return true if the passed in vector name has been flagged
bool isChanged(std::string vector)
{
    if (vector == "Checkings")
        return checkingsChanged;
    
    else if (vector == "Savings")
        return savingsChanged;
    
    else if (vector == "Expenses")
        return expensesChanged;
    
    else if (vector == "Special Expenses")
        return specialExpensesChanged;
    
    else
    {
        cout << "Unable to find " << vector << "!\n\n";
        return false;
    }
}



