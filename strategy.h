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

/**
* Constructor of Strategy_data object. Initializes all strategies
* and parameters with default values.
*/
Strategy_data* create_Strategy_data(uint_fast32_t memory_depth, uint_fast32_t iterations_count, int_fast32_t matrix[2][2]);

/**
* Function for playing iterative interaction of 2 strategies
* @param this - object of Strategy_data with needed strategies and parameters
* @param i - index of first strategy
* @param j - index of second strategy
*/
void play(Strategy_data* this, int_fast32_t i, int_fast32_t j);

/**
* Function for removing family of strategies with minimum points
* @param this - object of Strategy_data with needed strategies and parameters
*/
void remove_strategies(Strategy_data* this);

/**
* Destructor of Strategy_data object. Frees all memory
*/
void delete_Strategy_data(Strategy_data* this);

#endif // STRATEGY_H_INCLUDED
