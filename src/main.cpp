#include <iostream>
#include "StringUnit.h"
#include "GeneticAlgorith.h"
#include <cstdio>
#include <ctime>

int main() {
    srand(time(NULL));

    GeneticAlgorithm<StringUnit> genetic(1000);

    while(true) {
        StringUnit result = genetic.getFittest();

        std::cout << "Generation: " << genetic.getGeneration() << "\tBest: " << result << "\tFitness: " << result.fitness() << std::endl;

        if(result.fitness()>=30)
            break;

        genetic.nextGeneration(0.05);
    }
}