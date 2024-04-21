#include <iostream>
#include <iomanip>

#include "Genetic.h"
#include "Member.h"

int main() {
    std::cout << std::setprecision(3) << std::fixed;

    Genetic<Member> genetic(10000);

    while(true) {
        const Member &result = genetic.fittest();

        std::cout << std::setw(10) << genetic.epoch();
        std::cout << std::setw(10) << result.fitness();
        std::cout << std::setw(32) << result;
        std::cout << std::endl;

        if(result.fitness()>1e+3) {
            break;
        }

        genetic.evaluate();
    }
}
