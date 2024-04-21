#pragma once

#include <vector>
#include <random>
#include <algorithm>

template<typename T>
class Genetic {
    std::mt19937 gen;
    std::vector<T> population;
    int counter;

public:
    Genetic(const int size);

    const T & fittest() const;
    int epoch() const;
    void evaluate();
};

template<typename T>
Genetic<T>::Genetic(const int size) : counter{0} {
    std::random_device rd;
    gen = std::mt19937(rd());

    population.reserve(size);

    for(int i=0; i<size; i++) {
        population.emplace_back(gen);
    }
}

template<typename T>
const T & Genetic<T>::fittest() const {
    return population.front();
}

template<typename T>
int Genetic<T>::epoch() const {
    return counter;
}

template<typename T>
void Genetic<T>::evaluate() {
    std::vector<double> weights;
    weights.reserve(population.size());

    for(const T &member : population) {
        weights.push_back(member.fitness());
    }

    const auto bestIterator = std::max_element(weights.begin(), weights.end());
    const int bestIndex = std::distance(weights.begin(), bestIterator);

    std::vector<T> next;
    next.reserve(population.size());

    next.push_back(population[bestIndex]);

    std::discrete_distribution<int> distribution(weights.begin(), weights.end());

    for(unsigned int i=1; i<population.size(); i++) {
        const T &parent1 = population[distribution(gen)];
        const T &parent2 = population[distribution(gen)];

        next.emplace_back(gen, parent1, parent2);
    }

    population = next;
    counter++;
}
