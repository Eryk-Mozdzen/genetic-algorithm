#pragma once

#include <vector>
#include <random>
#include <iostream>

template<typename T>
class Genetic {
    std::mt19937 &gen;
    std::vector<T> population;
    int counter;

    const T & random(const std::vector<double> &weights);
    const T & fittest(const std::vector<double> &weights) const;

public:
    Genetic(std::mt19937 &gen, const int size);

    const T & fittest() const;
    int epoch() const;
    void evaluate();
};

template<typename T>
Genetic<T>::Genetic(std::mt19937 &gen, const int size) : gen{gen}, counter{0} {
    population.reserve(size);

    for(int i=0; i<size; i++) {
        population.emplace_back(gen);
    }
}

template<typename T>
const T & Genetic<T>::random(const std::vector<double> &weights) {
    double sum = 0;

    for(const double &w : weights) {
        sum +=w;
    }

    std::uniform_real_distribution<> distrib(0, sum);

    const double number = distrib(gen);
    double cumulative = 0;

    for(unsigned int i=0; i<weights.size(); i++) {
        cumulative +=weights[i];

        if(number<cumulative) {
            return population[i];
        }
    }

    return population[0];
}

template<typename T>
const T & Genetic<T>::fittest(const std::vector<double> &weights) const {
    int index = 0;

    for(unsigned int i=0; i<weights.size(); i++) {
        if(weights[i]>weights[index]) {
            index = i;
        }
    }

    return population[index];
}

template<typename T>
const T & Genetic<T>::fittest() const {
    return population[0];
}

template<typename T>
int Genetic<T>::epoch() const {
    return counter;
}

template<typename T>
void Genetic<T>::evaluate() {
    std::vector<double> fitness(population.size());

    for(unsigned int i=0; i<population.size(); i++) {
        fitness[i] = population[i].fitness();
    }

    std::vector<T> next;
    next.reserve(population.size());

    next.push_back(fittest(fitness));

    for(unsigned int i=1; i<population.size(); i++) {
        const T &parent1 = random(fitness);
        const T &parent2 = random(fitness);

        next.emplace_back(gen, parent1, parent2);
    }

    population = next;
    counter++;
}
