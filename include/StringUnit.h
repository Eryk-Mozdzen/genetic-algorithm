#pragma once

#include <iostream>
#include <string>
//#include <random>
//#include <chrono>
#include <cstdio>
#include <cmath>
#include "GeneticAlgorith.h"

class StringUnit : public Unit {
private:
    std::string data;
public:
    StringUnit();
    StringUnit(std::string);
    ~StringUnit();

    std::string getData() const;

    void mutate(double);
    double fitness() const;
    //Unit* crossover(Unit *);
    static Unit* crossover(Unit *, Unit *);
};

std::ostream & operator<<(std::ostream &, const StringUnit &);