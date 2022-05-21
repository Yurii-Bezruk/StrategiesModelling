#ifndef STRATEGY_H_INCLUDED
#define STRATEGY_H_INCLUDED
#include <stdint.h>
#define GROUP_SMALL 0
#define GROUP_BIG 1

typedef struct {
    uint_fast8_t name;
    uint_fast8_t sub_strategies;
    uint_fast8_t prev_move;
    uint_fast8_t complexity;
    int_fast32_t** own_matrix;
    int_fast32_t** foreign_matrix;
    uint_fast64_t points;
    uint8_t group;
} Strategy;

typedef struct {
    int_fast32_t memory_depth;
    int_fast32_t group_size;
    int_fast32_t iterations_count;
    int_fast32_t main_digits_count;
    int_fast32_t main_strategies_count;
    int_fast32_t sub_digits_count;
    int_fast32_t sub_strategies_count;
    int_fast32_t all_strategies_count;
    int_fast32_t complexity_count;
    int_fast32_t* complexity_counters;
    Strategy* strategies;
} Strategy_data;

/**
* Constructor of Strategy_data object. Initializes all strategies
* and parameters with default values.
*/
Strategy_data* create_Strategy_data(uint_fast32_t memory_depth, uint_fast32_t group_size, uint_fast32_t iterations_count, int_fast32_t** matrix, int_fast32_t** own_matrix, int_fast32_t** foreign_matrix);

/**
* Function for playing iterative interaction of 2 strategies
* @param this - object of Strategy_data with needed strategies and parameters
* @param i - index of first strategy
* @param j - index of second strategy
*/
void play(Strategy_data* this, int_fast32_t i, int_fast32_t j);

/**
* Function for averaging points of family of strategies with the same name
* but different sub-strategies. Should be called before removing
* @param this - object of Strategy_data with needed strategies and parameters
*/
void average_strategies(Strategy_data* this);

/**
* NOTE! call average_strategies() function first!!!
*
* Function for removing family of strategies with minimum points
* @param this - object of Strategy_data with needed strategies and parameters
*/
void remove_strategies(Strategy_data* this);

/**
* Destructor of Strategy_data object. Frees all memory
* @param this - object of Strategy_data to be freed
*/
void delete_Strategy_data(Strategy_data* this);

uint_fast32_t* init_complexity_array(int_fast32_t strategy_count);
uint_fast8_t get_complexity(uint_fast8_t name, uint_fast32_t* complexity_arr, int_fast32_t size);
#endif // STRATEGY_H_INCLUDED
