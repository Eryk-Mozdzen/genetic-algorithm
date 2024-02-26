#pragma once

#include <string>
#include <random>
#include <iostream>

class String {
    static const std::string target;

    std::string data;

public:
    String();
    String(std::random_device &rd);

    double fitness() const;
    static String crossover(std::random_device &rd, const String &parent1, const String &parent2);

    friend std::ostream & operator<<(std::ostream &stream, const String &string);
};
