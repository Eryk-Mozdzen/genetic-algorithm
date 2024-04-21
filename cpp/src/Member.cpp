#include <cstring>

#include "Member.h"

constexpr char target[] = "I'm Skynet and I will be back!";

Member::Member(std::mt19937 &gen) {
    std::uniform_int_distribution<char> distrib(' ', '}');

    for(unsigned int i=0; i<strlen(target); i++) {
        data +=distrib(gen);
    }
}

Member::Member(std::mt19937 &gen, const Member &parent1, const Member &parent2) {
    std::bernoulli_distribution distributionBool;

    for(unsigned int i=0; i<strlen(target); i++) {
        if(distributionBool(gen)) {
            data +=parent1.data[i];
        } else {
            data +=parent2.data[i];
        }
    }

    std::uniform_int_distribution<int> distrib(0, strlen(target));
    std::uniform_real_distribution<double> distribution(0, 1);
    std::uniform_int_distribution<char> distributionCharacter(' ', '}');

    while(distribution(gen)<0.05) {
        const int index = distrib(gen);
        const char character = distributionCharacter(gen);

        data[index] = character;
    }
}

double Member::fitness() const {
    int diff = 0;

    for(unsigned int i=0; i<strlen(target); i++) {
        if(data[i]!=target[i]) {
            diff++;
        }
    }

    if(diff==0) {
        return std::numeric_limits<double>::infinity();
    }

    return 1./diff;
}

std::ostream & operator<<(std::ostream &stream, const Member &string) {
    stream << string.data;
    return stream;
}
