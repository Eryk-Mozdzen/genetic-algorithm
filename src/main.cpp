#include <iostream>
#include <iomanip>
#include <random>

#include "Genetic.h"
#include "String.h"

int main() {
    std::random_device rd;
    std::mt19937 gen(rd());

    Genetic<String> genetic(gen, 100);

    while(true) {
        const String &result = genetic.fittest();

        std::cout << std::setprecision(3) << std::fixed;
        std::cout << " epoch   " << genetic.epoch();
        std::cout << " fitness " << result.fitness();
        std::cout << " result  " << result;
        std::cout << std::endl;

        if(result.fitness()>1e+3) {
            break;
        }

        genetic.evaluate();
    }
}
