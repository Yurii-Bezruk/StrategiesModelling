#ifndef STRATEGY_H_INCLUDED
#define STRATEGY_H_INCLUDED
#include <stdint.h>

typedef struct {
    uint_fast8_t name;
    uint_fast8_t prev_move;
    uint_fast64_t points;
} Strategy;

#endif // STRATEGY_H_INCLUDED
