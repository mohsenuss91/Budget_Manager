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

void drawMainMenu(void);
float checkAmount(float);
std::string checkDate(std::string);


class Profits{
    float amount;
    std::string date;
public:
    void setDate(std::string);
    void setAmount(float amnt);
    void printEntry(void);
};

class Expenses{
    std::string reason;
    std::string date;
    float amount;
public:
    void setDate(std::string);
    void setAmount(float);
    void setReason(std::string);
    void printEntry(void);
};

void loadExpense(std::string, std::vector<Expenses>&, int);
void loadProfits(std::string, std::vector<Profits>&, int);
#endif
