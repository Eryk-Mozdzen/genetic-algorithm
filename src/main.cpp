#include <iostream>
#include <iomanip>

#include "Genetic.h"
#include "String.h"

int main() {
    std::cout << std::setprecision(3) << std::fixed;

    Genetic<String> genetic(100);

    while(true) {
        const String &result = genetic.fittest();

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
