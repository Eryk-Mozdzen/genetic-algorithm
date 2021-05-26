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
        this->data +=rand()%('}' - ' ') + ' ';
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
    int index = rand()%(int)this->data.size();
    char character = rand()%('}' - ' ') + ' ';

    if(chance<mutationRate*0.333) {
        // change random index to random character
        this->data[index] = character;
    } else if(chance<mutationRate*0.666) {
        // delete random character
        this->data.erase(this->data.begin() + index);
    } else {
        // add random character in random place
        this->data.insert(this->data.begin() + index, character);
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

/*Unit* StringUnit::crossover(Unit *str2unit) {
    StringUnit *str2 = dynamic_cast<StringUnit*>(str2unit);

    /*std::default_random_engine engine(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_real_distribution<double> distribution01(0, 1);

    double fraq = distribution01(engine);*/

    /*double fraq = (double)(rand()%1000)/1000.;
    
    std::string str;

    for(std::size_t i=0; i<this->data.size()*fraq; i++)                      str +=this->data[i];
    for(std::size_t i=str2->data.size()*fraq+1; i<str2->data.size(); i++)     str +=str2->data[i];

    return static_cast<Unit*>(new StringUnit(str));
}*/

Unit* StringUnit::crossover(Unit *str1unit, Unit *str2unit) {
    StringUnit *str1 = dynamic_cast<StringUnit*>(str1unit);
    StringUnit *str2 = dynamic_cast<StringUnit*>(str2unit);

    /*std::default_random_engine engine(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_real_distribution<double> distribution01(0, 1);

    double fraq = distribution01(engine);*/

    double fraq = (double)(rand()%1000)/1000.;
    
    std::string str;

    for(std::size_t i=0; i<str1->data.size()*fraq; i++)                      str +=str1->data[i];
    for(std::size_t i=str2->data.size()*fraq+1; i<str2->data.size(); i++)     str +=str2->data[i];

    return static_cast<Unit*>(new StringUnit(str));
}

std::ostream & operator<<(std::ostream &lhs, const StringUnit &rhs) {
    lhs << rhs.getData();
    return lhs;
}