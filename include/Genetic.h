#pragma once

#include <vector>
#include <random>

template<typename T>
class Genetic {
    std::random_device &rd;
    std::vector<T> population;
    int counter;

    const T & random(const std::vector<double> &weights);
    const T & fittest(const std::vector<double> &weights) const;

public:
    Genetic(std::random_device &rd, const unsigned int size);

    const T & fittest() const;
    int epoch() const;
    void evaluate();
};

template<typename T>
Genetic<T>::Genetic(std::random_device &rd, const unsigned int size) : rd{rd}, population{size, T(rd)}, counter{0} {

}

template<typename T>
const T & Genetic<T>::random(const std::vector<double> &weights) {
    std::default_random_engine gen(rd());
    std::uniform_real_distribution<> distrib(0, 1);

    const double number = distrib(gen);
    double endPartition = 0;

    for(unsigned int i=0; i<weights.size(); i++) {
        endPartition +=weights[i];

        if(number<endPartition) {
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
    double sum = 0;

    for(unsigned int i=0; i<population.size(); i++) {
        fitness[i] = population[i].fitness();
        sum +=fitness[i];
    }

    for(double &f : fitness) {
        f /=sum;
    }

    std::vector<T> next(population.size());

    next[0] = fittest(fitness);

    for(unsigned int i=1; i<population.size(); i++) {
        const T &parent1 = random(fitness);
        const T &parent2 = random(fitness);

        next[i] = T::crossover(rd, parent1, parent2);
    }

    population = next;
    counter++;
}
