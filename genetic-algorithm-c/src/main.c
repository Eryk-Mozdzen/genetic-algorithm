#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "genetic.h"
#include "member.h"

int main() {
    srand(time(NULL));

    const genetic_config_t config = {
        .size = sizeof(member_t),
        .random = member_random,
        .crossover = member_crossover,
        .fitness = member_fitness
    };
    genetic_t *genetic = genetic_create(&config, 10000);

    while(1) {
        member_t result;
        genetic_fittest(genetic, &result);

        const float fitness = member_fitness(&result);

        printf("%10lu%10.3f%32s\n\r", genetic->epoch, fitness, result.content);

        if(fitness>1e+3) {
            break;
        }

        genetic_evaluate(genetic);
    }

    genetic_destroy(genetic);

    return 0;
}
