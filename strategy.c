#include "strategy.h"
#include "power.h"
#include "binary.h"
#include <stdlib.h>
#include <limits.h>

Strategy_data* create_Strategy_data(uint_fast32_t memory_depth, uint_fast32_t iterations_count, int_fast32_t matrix[2][2]) {
    Strategy_data* this = (Strategy_data*) malloc(sizeof(Strategy_data));

    this->matrix[0][0] = matrix[0][0];
    this->matrix[0][1] = matrix[0][1];
    this->matrix[1][0] = matrix[1][0];
    this->matrix[1][1] = matrix[1][1];

    this->iterations_count      = iterations_count;
    this->main_digits_count     = power(memory_depth + 1);
    this->main_strategies_count = power(this->main_digits_count);
    this->sub_digits_count      = power(memory_depth);
    this->sub_strategies_count  = power(this->sub_digits_count);
    this->all_strategies_count  = this->main_strategies_count * this->sub_strategies_count;
    this->strategies            = (Strategy*) malloc(sizeof(Strategy) * this->all_strategies_count);

    for (int_fast32_t i = 0, strat_index = 0; i < this->main_strategies_count; i++) {
        for (int_fast32_t j = 0; j < this->sub_strategies_count; j++, strat_index++) {
            this->strategies[strat_index].name = i;
            this->strategies[strat_index].prev_move = j;
            this->strategies[strat_index].first_move = j;
            this->strategies[strat_index].points = 0;
        }
    }
    return this;
}

void play(Strategy_data* this, int_fast32_t i, int_fast32_t j) {
    int_fast32_t s1_move = bit_at(this->strategies[i].first_move, 0);
    int_fast32_t s2_move = bit_at(this->strategies[j].first_move, 0);

    for (int_fast32_t k = 0; k < this->iterations_count - 1; k++) {
        this->strategies[i].points += this->matrix[s1_move][s2_move];
        if(i != j) {
            this->strategies[j].points += this->matrix[s2_move][s1_move];
        }
        append_move(this->strategies[i].prev_move, s1_move, this->sub_digits_count);
        append_move(this->strategies[j].prev_move, s2_move, this->sub_digits_count);
        s1_move = bit_at(this->strategies[i].name, this->strategies[j].prev_move);
        s2_move = bit_at(this->strategies[j].name, this->strategies[i].prev_move);
    }
    this->strategies[i].points += this->matrix[s1_move][s2_move];
    if(i != j) {
        this->strategies[j].points += this->matrix[s2_move][s1_move];
    }
}

static int_fast32_t find_min_strategy(Strategy_data* this) {
    uint_fast32_t min = INT_MAX;
    uint_fast32_t min_index;
    for (int_fast32_t i = 0; i < this->all_strategies_count; i += this->sub_strategies_count) {
        uint_fast32_t points = this->strategies[i].points;
        this->strategies[i].points = 0;

        for (int_fast32_t j = i + 1; j < i + this->sub_strategies_count; j++) {
            points += this->strategies[j].points;
            this->strategies[j].points = 0;
        }

        points /= this->sub_strategies_count;
        if(points < min) {
            min = points;
            min_index = i;
        }

        print_binary(this->strategies[i].name, this->main_digits_count);
        printf("\t%d\n", points);
    }
    return min_index;
}

void remove_strategies(Strategy_data* this) {
    int_fast32_t index = find_min_strategy(this);
    for (int_fast32_t i = index + this->sub_strategies_count - 1; i >= index; i--) {
        this->strategies[i] = this->strategies[this->all_strategies_count - 1];
        this->all_strategies_count--;
    }
}

void delete_Strategy_data(Strategy_data* this) {
    free(this->strategies);
    free(this);
}
