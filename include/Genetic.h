#pragma once

#include <vector>
#include <random>
#include <algorithm>

template<typename T>
class Genetic {
    std::mt19937 gen;
    std::vector<T> population;
    int counter;

    const T & random(const std::vector<double> &weights);
    const T & fittest(const std::vector<double> &weights) const;

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
const T & Genetic<T>::random(const std::vector<double> &weights) {
    std::discrete_distribution<int> distrib(weights.begin(), weights.end());

    const int index = distrib(gen);

    return population.at(index);
}

template<typename T>
const T & Genetic<T>::fittest(const std::vector<double> &weights) const {
    const auto it = std::max_element(weights.begin(), weights.end());
    const int index = std::distance(weights.begin(), it);

    return population.at(index);
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
    std::vector<double> fitness(population.size());

    std::transform(population.begin(), population.end(), fitness.begin(), [](const T &member) {
        return member.fitness();
    });

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
