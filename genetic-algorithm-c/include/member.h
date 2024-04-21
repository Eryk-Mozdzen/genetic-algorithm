#ifndef MEMBER_H
#define MEMBER_H

typedef struct {
    char content[32];
} member_t;

void member_random(void *member);
void member_crossover(void *member, const void *parent1, const void *parent2);
float member_fitness(const void *member);

#endif
