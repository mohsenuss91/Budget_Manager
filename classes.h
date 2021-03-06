//
//  classes.h
//
//  Holds all function and class
//  declarations for main.cpp
//
//  Created by Ivan Hernandez on 1/7/15.
//  Copyright (c) 2014 Ivan Hernandez. All rights reserved.
//

#ifndef _classes_h
#define _classes_h
#include <string> //include front strings
#include <iomanip> //include for setting decimal precision
#include <vector>

// Entry - Main Class
class Entry{
protected:
    float amount;
    unsigned int searchID;
    std::string date;
    std::string* reason;
    bool isExpense;
public:
    Entry();
    ~Entry();
    void setDate(std::string);
    void setAmount(float amnt);
    void setReason(std::string);
    void calculateSearchID(void);
    void printEntry(void);
    
    //inline methods
    std::string getReason(void)
        { return *reason; }
    std::string getDate(void)
        { return date; }
    float getAmount(void)
        { return amount; }
    unsigned int getSearchID(void)
        { return searchID; }
    bool getIsExpense(void)
        { return isExpense; }
    void loadDate(std::string d)
        { date = d; }
    void loadAmount(float amnt)
        { amount = amnt; }
    
};

//Functions
void drawMainMenu(void);
void drawSubMenu(std::string);
void subMenuController(std::string, std::vector<Entry>&, bool isExpense = false);

void setChanged(std::string, bool deleteDone = false);
bool isChanged(std::string);

void searchVector(std::vector<Entry>&, int, int, int min = 0); //by date
void printVector(std::string, std::vector<Entry>&, int amountToPrint = 20);
int getAmountOfValues(std::string);

Entry inputEntry(bool isExpense = false);
void loadEntry(std::string, std::vector<Entry>&, bool isExpense = false);
void saveEntry(int, std::string, std::vector<Entry>&);

void waitForEnter(void);
#endif
