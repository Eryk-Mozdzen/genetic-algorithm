#pragma once

#include <string>
#include <random>
#include <ostream>

class Member {
    std::string data;

public:
    Member(std::mt19937 &gen);
    Member(std::mt19937 &gen, const Member &parent1, const Member &parent2);

    double fitness() const;

    friend std::ostream & operator<<(std::ostream &stream, const Member &string);
};
