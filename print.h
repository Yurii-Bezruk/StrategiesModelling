#ifndef PRINT_H_INCLUDED
#define PRINT_H_INCLUDED
#include <stdio.h>
#include "binary.h"
#include "strategy.h"

/**
* Generic printing function. Prints to stdout
* value of any type.
*/
#define print(x) printf(_Generic((x), \
                          int: "%d", \
                          double: "%f", \
                          char*: "%s" \
                          ), x)
/**
* Generic printing function with line separator.
* Prints to stdout value of any type, and then '\n' symbol.
*/
#define println(x) printf(_Generic((x), \
                          int: "%d\n", \
                          double: "%f\n", \
                          char*: "%s\n" \
                          ), x)
/**
* Function for custom printing of values in binary
* form.
* @param digits - count of bits to be printed
*/
void print_binary(int_fast32_t x, int_fast32_t digits);

/**
* Function for custom printing of values in binary
* form with line separator.
* @param digits - count of bits to be printed
*/
void println_binary(int_fast32_t x, int_fast32_t digits);

/**
* Function for printing the strategy object in readable form
* without line separator.
* @param data - pointer for Strategy_data with needed strategies and parameters
* @param index - index of strategy to be printed
*/
void print_strategy(Strategy_data* data, int_fast32_t index);

/**
* Function for printing the strategy object in readable form
* with line separator.
* @param data - pointer for Strategy_data with needed strategies and parameters
* @param index - index of strategy to be printed
*/
void println_strategy(Strategy_data* data, int_fast32_t index);

/**
* Function for printing all strategies from Strategy_data object in readable form
* @param data - pointer for Strategy_data with needed strategies and parameters
*/
void print_all_strategies(Strategy_data* data);

/**
* Function for printing main strategies of every family from Strategy_data object in readable form
* @param data - pointer for Strategy_data with needed strategies and parameters
*/
void print_main_strategies(Strategy_data* data);

/**
* Function for printing summary of strategies with different complexities count
* @param data - pointer for Strategy_data with needed strategies and parameters
*/
void print_complexities(Strategy_data* data);

#endif // PRINT_H_INCLUDED
