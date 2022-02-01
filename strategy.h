#ifndef STRATEGY_H_INCLUDED
#define STRATEGY_H_INCLUDED
#include <stdint.h>

typedef struct {
    uint8_t name;
    uint8_t prev_move;
    int points;
} Strategy;

#endif // STRATEGY_H_INCLUDED
