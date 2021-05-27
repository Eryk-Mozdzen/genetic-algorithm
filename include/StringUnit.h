#pragma once

#include <iostream>
#include <string>
//#include <random>
//#include <chrono>
#include <cstdio>
#include <cmath>

class StringUnit {
private:
    std::string data;
public:
    StringUnit();
    StringUnit(std::string);
    ~StringUnit();

    std::string getData() const;

    void mutate(double);
    double fitness() const;
    static StringUnit crossover(const StringUnit &, const StringUnit &);
};

std::ostream & operator<<(std::ostream &, const StringUnit &);