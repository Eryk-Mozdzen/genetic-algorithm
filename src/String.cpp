#include "String.h"

const std::string String::target = "I'm Skynet and I will be back!";

String::String() {
    for(unsigned int i=0; i<target.size(); i++) {
        data +=" ";
    }
}

String::String(std::random_device &rd) {
    std::default_random_engine gen(rd());
    std::uniform_int_distribution<char> distrib(' ', '}');

    for(unsigned int i=0; i<target.size(); i++) {
        data +=distrib(gen);
    }
}

double String::fitness() const {
    double fitness = 0;

    for(unsigned int i=0; i<target.size(); i++) {
        if(data[i]==target[i]) {
            fitness++;
        }
    }

    return fitness;
}

String String::crossover(std::random_device &rd, const String &parent1, const String &parent2) {
    std::default_random_engine gen(rd());
    std::uniform_int_distribution<int> distrib(0, target.size());

    const int pivot = distrib(gen);

    String child;

    for(int i=0; i<pivot; i++) {
        child.data[i] = parent1.data[i];
    }

    for(unsigned int i=pivot; i<target.size(); i++) {
        child.data[i] = parent2.data[i];
    }

    std::uniform_real_distribution<double> distribution(0, 1);
    std::uniform_int_distribution<char> distributionCharacter(' ', '}');

    if(distribution(gen)<0.05) {
        const int index = distrib(gen);
        const char character = distributionCharacter(gen);

        child.data[index] = character;
    }

    return child;
}

std::ostream & operator<<(std::ostream &stream, const String &string) {
    stream << string.data;
    return stream;
}
