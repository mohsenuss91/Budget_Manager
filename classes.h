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

// Entry - Parent Class
class Entry{
protected:
    float amount;
    std::string date;
    std::string* reason;
public:
    Entry();
    void setDate(std::string);
    void setAmount(float amnt);
    void setReason(std::string);
    std::string getDate(void);
    std::string getReason(void);
    float getAmount(void);
    void loadDate(std::string);
    void loadAmount(float amnt);
    void printEntry(bool isExpense = false);
};



//Functions
void drawMainMenu(void);
void drawSubMenu(std::string);

Entry inputEntry(Entry, bool isExpense = false);

int getAmountOfValues(std::string);
void setChanged(std::string, bool deleteDone = false);
bool isChanged(std::string);

void loadEntry(std::string, std::vector<Entry>&, bool isExpense = false);
void saveEntry(int, std::string, std::vector<Entry>&,bool isExpense = false);
#endif
