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

/* Class Methods */

// 'Entry' Constructor
Entry::Entry()
{
    amount = 0.0;
    date = "00/00/00";
    reason = NULL;
    isExpense = false;
}

// 'Entry' Destructor
Entry::~Entry()
{
    if(reason)
    {
        delete reason;
        reason = NULL;
    }
}

// 'setDate' will check string for valid date input
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

// 'setAmount' will error check for valid amount input
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

// 'printEntry' will output to screen an entries values formatted
void Entry::printEntry(){
    cout << right; // align left
    cout << setw(8) << date;
    cout << "  . . .  $";
    
    if(isExpense)
    {
        cout << resetiosflags(std::ios::adjustfield); //reset alignment
        cout << fixed << setprecision(2)  << setw(7) << left << amount;
        cout << " . . .  ";
        cout << *reason << endl;
    }
    else
    {
        cout << fixed << setprecision(2)  << amount;
        cout << endl;
        cout << resetiosflags(std::ios::adjustfield); //reset alignment
    }
}

// 'setReason' will dynamically allocate memory for reason string if Entry is an expense
void Entry::setReason(std::string rsn){
    if(!reason)
    {
        reason = new string;
        *reason = "NaNaNa";
        isExpense = true;
    }
    *reason = rsn;
}





/* Functions */

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

// 'drawSubMenu' prints the sub menu
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

void subMenuController(std::string vectorName, std::vector<Entry> &inVector, bool isExpense)
{
    unsigned int inChoice = 0;
    char inChar;
    while (inChoice != 4)
    {
        drawSubMenu(vectorName);
        cin >> inChoice;
        cin.clear(); cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if(inChoice == 1)
        {
            inVector.push_back( inputEntry() );
            setChanged(vectorName);
            
        }
        else if (inChoice == 2)
        {
            cout << "Are you sure you want to remove last input? (Y/N): ";
            cin >>inChar;
            
            if (inChar == 'Y' || inChar == 'y')
            {
                if(inVector.size() > 0)
                {
                    cout << "Removing last entry..." << endl;
                    inVector.pop_back();
                    setChanged(vectorName, true);
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
            cout << "\n" << vectorName << "\n";
            for (unsigned int i = 0; i < inVector.size(); i++)
            {
                cout << setw(3) << i+1 << ": ";
                inVector[i].printEntry();
            }
        }
        
        else if (inChoice == 4)
        { cout << "Returning to main menu...\n\n"; }
        
        else
        { cout << "Invalid Input.\n"; }
    }
}



// 'inputEntry' will get values from user and then append the entries to the vector.
Entry inputEntry(bool isExpense)
{
    float inAmount;
    string inDate(9, '\0');
    static Entry newInput;
    
    cout << "Give me the date: " ;
    cin >> inDate;
    newInput.setDate(inDate);
    cout << "Give me the amount: $";
    cin >> inAmount;
    newInput.setAmount(inAmount);
    if (isExpense)
    {
        static string inReason(41, '\0');
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
    }
    return newInput;
}

// 'loadEntry' will read inputted file and load values appropiate vector
void loadEntry(std::string filename, std::vector<Entry> &inVector, bool isExpense)
{
    std::string buffer(41, '\0');
    std::ifstream inFile(filename);
    if(!inFile)
    {
        cout << "Error opening file named \"" << filename << "\". Nothing will be loaded from it.\n";
    }
    for (unsigned int i = 0; std::getline(inFile,buffer,'$'); i++)
        // will read until getline fails and also reads in $ sign and skips it
    {
        
        std::getline(inFile,buffer,',');
        inVector[i].loadAmount(std::stod(buffer));
        if(isExpense)
        {
            std::getline(inFile,buffer,',');
            inVector[i].setReason(buffer);
        }
        std::getline(inFile,buffer,'\r');
        inVector[i].loadDate(buffer);
    }
    inFile.close();
}

// 'saveEntry' will write any changes in appropiate vector to the file
void saveEntry(int initialValues, std::string filename, std::vector<Entry> &inVector)
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
        
        //Writes the headers
        for (unsigned int i = 0, j = (inVector.size() / 100) + 1; i<j;i++)
        {
            newFile << "Date,Amount,,";
        }
        for (unsigned int i = 0; i < 100; i++)
        {
            newFile << '\r';
            for (unsigned int j = inVector.size() / 100, k = 0, l; k <= j; k++)
            {
                l = k*100;
                if (i+l > inVector.size())
                {
                    newFile << ",,";
                }
                else
                {
                    newFile << inVector[i+l].getDate() << ',';
                    if(inVector[0].getIsExpense())
                    { newFile << inVector[i+l].getReason() << ','; }
                    newFile << '$' << inVector[i+l].getAmount() << ',';
                }
                newFile << ",";
            }
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
        for (unsigned int i = initialValues; i < inVector.size(); i++)
        {
            inFile << '\r' << '$' << inVector[i].getAmount() << ',' << inVector[0].getReason() << ',' << inVector[i].getDate();
        }
        inFile.close();
    }
}





// 'getAmountOfValues' returns the number of lines in a file
int getAmountOfValues(std::string filename)
{
    std::ifstream inFile(filename);
    std::string buffer;
    unsigned int i;
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



