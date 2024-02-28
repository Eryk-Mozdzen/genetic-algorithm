#pragma once

#include <string>
#include <random>
#include <ostream>

class String {
    std::string data;

public:
    String(std::mt19937 &gen);
    String(std::mt19937 &gen, const String &parent1, const String &parent2);

    double fitness() const;

    friend std::ostream & operator<<(std::ostream &stream, const String &string);
};
