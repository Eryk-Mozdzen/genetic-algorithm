#include <iostream>
#include <random>

#include "Genetic.h"
#include "String.h"

int main() {
    std::random_device rd;

    Genetic<String> genetic(rd, 1000);

    while(true) {
        const String &result = genetic.fittest();

        std::cout << " epoch:   " << genetic.epoch();
        std::cout << " fitness: " << result.fitness();
        std::cout << " result:  " << result;
        std::cout << std::endl;

        if(result.fitness()>=30) {
            break;
        }

        genetic.evaluate();
    }
}
