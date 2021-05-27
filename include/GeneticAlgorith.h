/*
    Simple Genetic Algorithm for general purpose
    by Eryk Możdżeń May 2021
*/

#pragma once

#include <vector>
#include <utility>
#include <cstdlib>

template<class T>
class GeneticAlgorithm {
private:
    std::vector<std::pair<T, double>> population;
    std::size_t generation;

    void evaluateFitness();
    std::size_t randomMember() const;
    std::size_t fittestMember() const;
public:
    GeneticAlgorithm(std::size_t);

    const T & getFittest() const;
    std::size_t getGeneration() const;

    void evaluateGeneration(double);
};

/*-----------------------------------------------------------------------------------*/

template<class T>
GeneticAlgorithm<T>::GeneticAlgorithm(std::size_t populationSize) {
    this->generation = 0;
    this->population.resize(populationSize);
}

template<class T>
const T & GeneticAlgorithm<T>::getFittest() const {
    return this->population[this->fittestMember()].first;
}

template<class T>
std::size_t GeneticAlgorithm<T>::getGeneration() const {
    return this->generation;
}

template<class T>
void GeneticAlgorithm<T>::evaluateFitness() {
    double sum = 0;

    for(std::size_t i=0; i<this->population.size(); i++) {
        this->population[i].second = this->population[i].first.fitness();
        sum +=this->population[i].second;
    }

    // probability normalization
    for(std::size_t i=0; i<this->population.size(); i++)
        this->population[i].second /=sum;
}

template<class T>
std::size_t GeneticAlgorithm<T>::randomMember() const {
    double endPartition = 0;
    double randomNumber = (double)(rand()%1000)/1000.;

    for(std::size_t i=0; i<this->population.size(); i++) {
        endPartition +=this->population[i].second;
        
        if(randomNumber<endPartition)
            return i;
    }

    return 0;
}

template<class T>
std::size_t GeneticAlgorithm<T>::fittestMember() const {
    std::size_t f = 0;

    for(std::size_t i=0; i<this->population.size(); i++) {
        if(this->population[i].second>this->population[f].second) {
            f = i;
        }
    }

    return f;
}

template<class T>
void GeneticAlgorithm<T>::evaluateGeneration(double mutationRate) {
    std::vector<std::pair<T, double>> next(this->population.size());
    
    this->evaluateFitness();

    // best in current generation has 100% chance to be in next generation
    // fitness will only grow or stay in the same level
    next[0].first = this->getFittest();

    // rest of the next population will be created from current members
    // probability of reproduction for every member is normalized fitness
    for(std::size_t i=1; i<this->population.size(); i++) {
        std::size_t parent1 = this->randomMember();
        std::size_t parent2 = this->randomMember();

        // mix two random members form current generation
        next[i].first = T::crossover(this->population[parent1].first, this->population[parent2].first);

        // mutate by some small value
        // to prevernt against equal population members (stopped development)
        next[i].first.mutate(mutationRate);
    }

    this->population = next;
    this->generation++;
}