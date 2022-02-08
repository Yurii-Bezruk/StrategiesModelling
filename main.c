#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include "print.h"
#include "binary.h"
#include "strategy.h"

int_fast32_t matrix[2][2] = {
    {1, 5},
    {0, 3}
};
uint_fast32_t MEMORY_DEPTH = 0;

const int_fast32_t ITERATIONS_COUNT = 500;

int main() {
    int_fast32_t main_digits_count = (int_fast32_t)pow(2, MEMORY_DEPTH + 1);
    int_fast32_t main_strategies_count = (int_fast32_t)pow(2, main_digits_count);
    int_fast32_t sub_digits_count = (int_fast32_t)pow(2, MEMORY_DEPTH);
    int_fast32_t sub_strategies_count = (int_fast32_t)pow(2, sub_digits_count);
    int_fast32_t all_strategies_count = main_strategies_count * sub_strategies_count;
    Strategy strategies[all_strategies_count];

    for (int_fast32_t i = 0, strat_index = 0; i < main_strategies_count; i++) {
        for (int_fast32_t j = 0; j < sub_strategies_count; j++, strat_index++) {
            strategies[strat_index].name = i;
            strategies[strat_index].prev_move = j;
            strategies[strat_index].first_move = j;
            strategies[strat_index].points = 0;
        }
    }
    for (int_fast32_t i = 0; i < all_strategies_count; i++) {
        for (int_fast32_t j = i; j < all_strategies_count; j++) {
            int_fast32_t s1_move = bit_at(strategies[i].name, strategies[j].first_move);
            int_fast32_t s2_move = bit_at(strategies[j].name, strategies[i].first_move);
            for (int_fast32_t k = 0; k < ITERATIONS_COUNT - 1; k++) {
                strategies[i].points += matrix[s1_move][s2_move];
                strategies[j].points += matrix[s2_move][s1_move];
                append_move(strategies[i].prev_move, s1_move, sub_digits_count);
                append_move(strategies[j].prev_move, s2_move, sub_digits_count);
                s1_move = bit_at(strategies[i].name, strategies[j].prev_move);
                s2_move = bit_at(strategies[j].name, strategies[i].prev_move);
            }
            strategies[i].points += matrix[s1_move][s2_move];
            strategies[j].points += matrix[s2_move][s1_move];
        }
    }
//    for (int_fast32_t i = 0; i < all_strategies_count; i++) {
//        println_strategy(strategies + i, main_digits_count);
//    }
    for (int_fast32_t i = 0; i < all_strategies_count; i += sub_strategies_count) {
        for (int_fast32_t j = i + 1; j < i + sub_strategies_count; j++) {
            strategies[i].points += strategies[j].points;
        }
        strategies[i].points /= sub_strategies_count;
        println_strategy(strategies + i, main_digits_count);
    }
}
