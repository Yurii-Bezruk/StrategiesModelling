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
void print_binary(int x, int digits);

/**
* Function for custom printing of values in binary
* form with line separator.
* @param digits - count of bits to be printed
*/
void println_binary(int x, int digits);

/**
* Function for printing the strategy object in readable form
* form without line separator.
* @param str - pointer for strategy object
* @param main_digits_count - count of digits of the main
*   strategy name to be presented.
*/
void print_strategy(Strategy* str, int main_digits_count);

/**
* Function for printing the strategy object in readable form
* form with line separator.
* @param str - pointer for strategy object
* @param main_digits_count - count of digits of the main
*   strategy name to be presented.
*/
void println_strategy(Strategy* str, int main_digits_count);

#endif // PRINT_H_INCLUDED