#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "genetic.h"

#define ELEMENT(genetic, index) (((char *)(genetic)->population) + ((index)*(genetic)->config.size))

static void * random_member(genetic_t *genetic, const float *cumulative, const float sum) {
    const float random = isinf(sum) ? rand() : (rand()%((size_t)(sum*1000000.f)))/1000000.f;

    size_t low = 0;
    size_t high = genetic->population_size - 1;
    while(low<high) {
        const size_t mid = low + (high - low)/2;

        if(random<cumulative[mid]) {
            high = mid;
        } else {
            low = mid + 1;
        }
    }

    return ELEMENT(genetic, low);
}

genetic_t * genetic_create(const genetic_config_t *config, const size_t population_size) {
    genetic_t *genetic = malloc(sizeof(genetic_t));
    genetic->population = malloc(population_size*config->size);
    genetic->population_size = population_size;
    genetic->epoch = 0;

    memcpy(&genetic->config, config, sizeof(*config));

    for(size_t i=0; i<genetic->population_size; i++) {
        genetic->config.random(ELEMENT(genetic, i));
    }

    return genetic;
}

void genetic_fittest(const genetic_t *genetic, void *member) {
    memcpy(member, genetic->population, genetic->config.size);
}

void genetic_evaluate(genetic_t *genetic) {
    float *weights = malloc(genetic->population_size*sizeof(float));

    size_t best_index = 0;
    float best_fitness = -INFINITY;
    float sum_fitness = 0;
    for(size_t i=0; i<genetic->population_size; i++) {
        weights[i] = genetic->config.fitness(ELEMENT(genetic, i));

        if(weights[i]>best_fitness) {
            best_index = i;
            best_fitness = weights[i];
        }

        sum_fitness +=weights[i];
        if(i>0) {
            weights[i] +=weights[i-1];
        }
    }

    void *next = malloc(genetic->population_size*genetic->config.size);
    void *next_iter = next;

    memcpy(next_iter, ELEMENT(genetic, best_index), genetic->config.size);
    next_iter = (char *)next_iter + genetic->config.size;

    for(size_t i=1; i<genetic->population_size; i++) {
        const void *parent1 = random_member(genetic, weights, sum_fitness);
        const void *parent2 = random_member(genetic, weights, sum_fitness);

        genetic->config.crossover(next_iter, parent1, parent2);
        next_iter = (char *)next_iter + genetic->config.size;
    }

    free(genetic->population);
    free(weights);

    genetic->population = next;
    genetic->epoch++;
}

void genetic_destroy(genetic_t *genetic) {
    free(genetic->population);
    free(genetic);
}
