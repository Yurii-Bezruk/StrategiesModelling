#ifndef STRATEGY_H_INCLUDED
#define STRATEGY_H_INCLUDED
#include <stdint.h>

typedef struct {
    uint_fast8_t name;
    uint_fast8_t prev_move;
    uint_fast8_t first_move;
    uint_fast64_t points;
} Strategy;

typedef struct {
    int_fast32_t matrix[2][2];
    int_fast32_t iterations_count;
    int_fast32_t main_digits_count;
    int_fast32_t main_strategies_count;
    int_fast32_t sub_digits_count;
    int_fast32_t sub_strategies_count;
    int_fast32_t all_strategies_count;
    Strategy* strategies;
} Strategy_data;

Strategy_data* create_Strategy_data(uint_fast32_t memory_depth, uint_fast32_t iterations_count, int_fast32_t matrix[2][2]);

void play(Strategy_data* this, int_fast32_t i, int_fast32_t j);

void remove_strategies(Strategy_data* this);

void delete_Strategy_data(Strategy_data* this);

#endif // STRATEGY_H_INCLUDED
