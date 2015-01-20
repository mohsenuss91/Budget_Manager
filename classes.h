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

class Entry{
protected:
    float amount;
    std::string date;
    bool isChanged;
public:
    void setDate(std::string);
    void setAmount(float amnt);
    void loadDate(std::string);
    void loadAmount(float amnt);
};

class Profits : public Entry{
public:
    Profits(void);
    ~Profits(void);
    void printEntry(void);
};

class Expenses : public Entry{
    std::string reason;
public:
    Expenses(void);
    ~Expenses(void);
    void setReason(std::string);
    void printEntry(void);
};

void drawMainMenu(void);
void drawSubMenu(std::string);

Expenses inputExpense(Expenses);
Profits inputProfit(Profits);

void loadExpense(std::string, std::vector<Expenses>&, int);
void loadProfits(std::string, std::vector<Profits>&, int);
#endif
