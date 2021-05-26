#pragma once

#include <vector>
#include <utility>
#include <type_traits>

class Unit {
public:
    virtual ~Unit() {};
    virtual void mutate(double) = 0;
    virtual double fitness() const = 0;
    //virtual Unit* crossover(Unit *) = 0;
    static Unit* crossover(Unit *, Unit *);
};

template<class T>
class GeneticAlgorithm {
private:
    std::vector<std::pair<Unit*, double>> population;
    std::size_t generation;

    std::size_t propableParentIndex() const;
public:
    GeneticAlgorithm(std::size_t);

    T getFittest() const;
    std::size_t getGeneration() const;

    void nextGeneration(double);
};

/*-----------------------------------------------------------------------------------*/

template<class T>
GeneticAlgorithm<T>::GeneticAlgorithm(std::size_t populationSize) {
    static_assert(std::is_base_of<Unit, T>::value, "T must derive from Unit");

    this->generation = 0;

    //this->population.resize(populationSize);

    for(std::size_t i=0; i<populationSize; i++)
        this->population.push_back(std::make_pair(static_cast<Unit*>(new T()), 0));
}

template<class T>
T GeneticAlgorithm<T>::getFittest() const {
    double fitness = this->population[0].second, f = 0;

    for(std::size_t i=0; i<this->population.size(); i++) {
        if(this->population[i].second>fitness) {
            fitness = this->population[i].second;
            f = i;
        }
    }
    return *dynamic_cast<T*>(this->population[f].first);
}

template<class T>
std::size_t GeneticAlgorithm<T>::getGeneration() const {
    return this->generation;
}

template<class T>
std::size_t GeneticAlgorithm<T>::propableParentIndex() const {
    vector<double> probArray;
    double sum = 0;
    double beginPartition = 0;
    double endPartition;
    double randomNumber = random(0, 999, "double")/1000;
    for(int i=0; i<population.size(); i++)
        sum+=(1.0/population[i].error);
    for(int i=0; i<population.size(); i++)
        probArray.push_back((1.0/population[i].error)/sum);
    for(int i=0; i<population.size(); i++) {
        endPartition = probArray[i]+beginPartition;
        if(randomNumber>=beginPartition && randomNumber<=endPartition) return population[i];
        beginPartition = endPartition;
    }
    return 0;
}

template<class T>
void GeneticAlgorithm<T>::nextGeneration(double mutationRate) {
    //for(std::size_t i=0; i<this->population.size(); i++)
    //    std::cout << this->population[i].first << std::endl;

    for(std::pair<Unit*, double> &member : this->population)
        member.second = member.first->fitness();

    double fitness = this->population[0].second, f = 0;

    for(std::size_t i=0; i<this->population.size(); i++) {
        if(this->population[i].second>fitness) {
            fitness = this->population[i].second;
            f = i;
        }
    }

    this->population[0].first = this->population[f].first;
    for(std::size_t i=1; i<this->population.size(); i++) {
        std::size_t parent1 = this->propableParentIndex();
        std::size_t parent2 = this->propableParentIndex();

        //this->population[i].first = population[parent1].first->crossover(population[parent2].first);
        this->population[i].first = T::crossover(population[parent2].first, population[parent1].first);
        this->population[i].first->mutate(mutationRate);
    }

    this->generation++;
}