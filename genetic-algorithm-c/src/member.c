#include <string.h>
#include <stdlib.h>
#include <math.h>

#include "member.h"

static const char target[] = "I'm Skynet and I will be back!";

static char random_char() {
    return rand()%('{' - ' ') + ' ';
}

void member_random(void *member) {
    const size_t len = strlen(target);

    for(size_t i=0; i<len; i++) {
        ((member_t *)member)->content[i] = random_char();
    }
}

void member_crossover(void *member, const void *parent1, const void *parent2) {
    const size_t len = strlen(target);
    const size_t midpoint = rand()%len;

    for(size_t i=0; i<midpoint; i++) {
        ((member_t *)member)->content[i] = ((member_t *)parent1)->content[i];
    }
    for(size_t i=midpoint; i<len; i++) {
        ((member_t *)member)->content[i] = ((member_t *)parent2)->content[i];
    }

    if((rand()%100)<5) {
        const size_t index = rand()%len;
        const char character = random_char();

        ((member_t *)member)->content[index] = character;
    }
}

float member_fitness(const void *member) {
    const size_t len = strlen(target);
    size_t diff = 0;

    for(size_t i=0; i<len; i++) {
        if(((member_t *)member)->content[i]!=target[i]) {
            diff++;
        }
    }

    if(diff==0) {
        return INFINITY;
    }

    return 1.f/diff;
}
