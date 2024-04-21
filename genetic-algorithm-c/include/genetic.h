#ifndef GENETIC_H
#define GENETIC_H

#include <stddef.h>

typedef struct {
    size_t size;
    void (*random)(void *);
    void (*crossover)(void *, const void *, const void *);
    float (*fitness)(const void *);
} genetic_config_t;

typedef struct {
    void *population;
    size_t population_size;
    size_t epoch;
    genetic_config_t config;
} genetic_t;

genetic_t * genetic_create(const genetic_config_t *config, const size_t population_size);
void genetic_fittest(const genetic_t *genetic, void *member);
void genetic_evaluate(genetic_t *genetic);
void genetic_destroy(genetic_t *genetic);

#endif
