#include "StringUnit.h"

StringUnit::StringUnit() {
    this->data = "";

    /*std::default_random_engine engine(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> distributionLength(0, 50);
    std::uniform_int_distribution<char> distributionChar(' ', '}');

    int length = distributionLength(engine);
    for(int i=0; i<length; i++)
        this->data +=distributionChar(engine);*/

    int length = rand()%50 + 1;
    for(int i=0; i<length; i++)
        this->data +=rand()%('}' - ' ' + 1) + ' ';
}

StringUnit::StringUnit(std::string data) {
    this->data = data;
}

StringUnit::~StringUnit() {

}

std::string StringUnit::getData() const {
    return this->data;
}

void StringUnit::mutate(double mutationRate) {
    /*std::default_random_engine engine(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_real_distribution<double> distribution01(0, 1);
    std::uniform_int_distribution<int> distributionChar(' ', '}');
    std::uniform_int_distribution<char> distributionLength(0, (int)this->data.size());

    double chance = distribution01(engine);
    int index = distributionLength(engine);*/

    double chance = (double)(rand()%1000)/1000.;

    if(chance>mutationRate)
        return;

    std::size_t index = rand()%this->data.size();
    char character = rand()%('}' - ' ' + 1) + ' ';

    switch(rand()%3) {
        case 0: {
            // change character at random index to random character
            this->data[index] = character;
        } break;
        case 1: {
            // delete random character
            this->data.erase(this->data.begin() + index);
        } break;
        case 2: {
            // add random character in random place
            this->data.insert(this->data.begin() + index, character);
        } break;
    }
}

double StringUnit::fitness() const {
    const std::string target = "I'm Skynet and I will be back!";

    double fitness = 0;
    for(std::size_t i=0; i<std::min(this->data.size(), target.size()); i++) {
        if(this->data[i]==target[i])
            fitness++;
    }

    fitness /=(0.1*std::abs((float)target.size() - (float)this->data.size()) + 1);

    return fitness;
}

StringUnit StringUnit::crossover(const StringUnit &str1, const StringUnit &str2) {
    /*std::default_random_engine engine(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_real_distribution<double> distribution01(0, 1);

    double fraq = distribution01(engine);*/

    std::size_t pivot = rand()%std::min(str1.data.size(), str2.data.size());
    
    std::string str = "";

    for(std::size_t i=0; i<pivot; i++)                      str +=str1.data[i];
    for(std::size_t i=pivot+1; i<str2.data.size(); i++)     str +=str2.data[i];

    return StringUnit(str);
}

std::ostream & operator<<(std::ostream &lhs, const StringUnit &rhs) {
    lhs << rhs.getData();
    return lhs;
}