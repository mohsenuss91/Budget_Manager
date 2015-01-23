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
public:
    void setDate(std::string);
    void setAmount(float amnt);
    std::string getDate(void);
    float getAmount(void);
    void loadDate(std::string);
    void loadAmount(float amnt);
};

// Profits - Child Class
class Profits : public Entry{
public:
    Profits(void);
    ~Profits(void);
    void printEntry(bool showDecimals = true);
};

// Expenses - Child Class
class Expenses : public Entry{
private:
    std::string reason;
public:
    Expenses(void);
    ~Expenses(void);
    std::string getReason(void);
    void setReason(std::string);
    void printEntry(void);
};

//Functions
void drawMainMenu(void);
void drawSubMenu(std::string);

Expenses inputExpense(Expenses);
Profits inputProfit(Profits);

int getAmountOfValues(std::string);
void setChanged(std::string, bool deleteDone = false);
bool isChanged(std::string);

void loadExpense(std::string, std::vector<Expenses>&);
void loadProfits(std::string, std::vector<Profits>&);
void saveProfits(int, std::string, std::vector<Profits>&);
void saveExpense(int, std::string, std::vector<Expenses>&);
#endif
