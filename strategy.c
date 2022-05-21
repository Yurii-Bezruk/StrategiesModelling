#include "strategy.h"
#include "power.h"
#include "binary.h"
#include "memory.h"
#include <stdlib.h>
#include <limits.h>

Strategy_data* create_Strategy_data(uint_fast32_t memory_depth, uint_fast32_t group_size, uint_fast32_t iterations_count, int_fast32_t** matrix, int_fast32_t** own_matrix, int_fast32_t** foreign_matrix){
    Strategy_data* this = new(Strategy_data, 1);

    this->memory_depth          = memory_depth;
    this->group_size            = group_size;
    this->group_count           = 0;
    this->iterations_count      = iterations_count;
    this->main_digits_count     = power(memory_depth + 1);
    this->main_strategies_count = power(this->main_digits_count);
    this->sub_digits_count      = 0;
    for (int_fast32_t i = 0; i < this->memory_depth + 1; i++) {
        this->sub_digits_count += power(i);
    }
    this->sub_strategies_count  = power(this->sub_digits_count);
    this->all_strategies_count  = this->main_strategies_count * this->sub_strategies_count;
    this->complexity_count      = power(this->memory_depth + 1) + 1;
    this->complexity_counters   = new(int_fast32_t, this->complexity_count);
    this->small_complexity_counters   = new(int_fast32_t, this->complexity_count);
    for (int i = 0; i < this->complexity_count; i++){
        this->complexity_counters[i] = 0;
        this->small_complexity_counters[i] = 0;
    }

    this->strategies            = new(Strategy, this->all_strategies_count);

    uint_fast32_t* complexities = init_complexity_array(this->all_strategies_count);

    for (int_fast32_t i = 0, strat_index = 0; i < this->main_strategies_count; i++) {
        this->strategies[i * this->sub_strategies_count].complexity = get_complexity(i, complexities, this->main_digits_count);
        this->strategies[i * this->sub_strategies_count].aggresiveness = get_aggresiveness(i, this->main_digits_count);
        this->complexity_counters[this->strategies[strat_index].complexity]++;
        if(i % this->group_size == 0) {
            this->small_complexity_counters[this->strategies[strat_index].complexity]++;
            this->group_count++;
        }
        for (int_fast32_t j = 0; j < this->sub_strategies_count; j++, strat_index++) {
            this->strategies[strat_index].name = i;
            this->strategies[strat_index].sub_strategies = j;
            this->strategies[strat_index].prev_move = 0;
            this->strategies[strat_index].complexity = this->strategies[i * this->sub_strategies_count].complexity;
            this->strategies[strat_index].aggresiveness = this->strategies[i * this->sub_strategies_count].aggresiveness;
            this->strategies[strat_index].points = 0;
            if(i % this->group_size == 0) {
                this->strategies[strat_index].group = GROUP_SMALL;
                this->strategies[strat_index].own_matrix = own_matrix;
                this->strategies[strat_index].foreign_matrix = foreign_matrix;
            } else {
                this->strategies[strat_index].group = GROUP_BIG;
                this->strategies[strat_index].own_matrix = matrix;
            }
        }
    }
    free(complexities);
    return this;
}

static void calculate_points(Strategy_data* this, int_fast32_t i, int_fast32_t j, int_fast32_t s1_move, int_fast32_t s2_move) {
    if(this->strategies[i].group == this->strategies[j].group) {
        this->strategies[i].points += this->strategies[i].own_matrix[s1_move][s2_move];
        if(i != j) {
            this->strategies[j].points += this->strategies[j].own_matrix[s2_move][s1_move];
        }
    } else if(this->strategies[i].group == GROUP_SMALL && this->strategies[j].group == GROUP_BIG) {
        this->strategies[i].points += this->strategies[i].foreign_matrix[s1_move][s2_move];
        this->strategies[j].points += this->strategies[j].own_matrix[s2_move][s1_move];
    } else {
        this->strategies[i].points += this->strategies[i].own_matrix[s1_move][s2_move];
        this->strategies[j].points += this->strategies[j].foreign_matrix[s2_move][s1_move];
    }
}

void play(Strategy_data* this, int_fast32_t i, int_fast32_t j) {
    int_fast32_t s1_move;
    int_fast32_t s2_move;

    int_fast32_t prev_move_size = 1;
    int_fast32_t sub_iteration;
    for (sub_iteration = 0; sub_iteration < this->memory_depth + 1; sub_iteration++) {
        s1_move = bit_at(this->strategies[i].sub_strategies / power(sub_iteration), this->strategies[j].prev_move);
        s2_move = bit_at(this->strategies[j].sub_strategies / power(sub_iteration), this->strategies[i].prev_move);

        calculate_points(this, i, j, s1_move, s2_move);

        append_move(this->strategies[i].prev_move, s1_move, prev_move_size);
        append_move(this->strategies[j].prev_move, s2_move, prev_move_size);

//        print_strategy(this, i); printf(" --> %d moves: ", s1_move); println_binary(this->strategies[i].prev_move, prev_move_size);
//        print_strategy(this, j); printf(" --> %d moves: ", s2_move); println_binary(this->strategies[j].prev_move, prev_move_size);
//        printf("--------------------------prev_move_size: %d\n\n", prev_move_size);

        prev_move_size = sub_iteration + 2;
    }
    prev_move_size--;

    for (int_fast32_t k = 0; k < this->iterations_count - sub_iteration; k++) {
        s1_move = bit_at(this->strategies[i].name, this->strategies[j].prev_move);
        s2_move = bit_at(this->strategies[j].name, this->strategies[i].prev_move);

        calculate_points(this, i, j, s1_move, s2_move);

        append_move(this->strategies[i].prev_move, s1_move, prev_move_size);
        append_move(this->strategies[j].prev_move, s2_move, prev_move_size);

//        print_strategy(this, i); printf(" --> %d moves: ", s1_move); println_binary(this->strategies[i].prev_move, prev_move_size);
//        print_strategy(this, j); printf(" --> %d moves: ", s2_move); println_binary(this->strategies[j].prev_move, prev_move_size);
//        printf("--------------------------\n\n");

    }
}

void average_strategies(Strategy_data* this) {
    for (int_fast32_t i = 0; i < this->all_strategies_count; i += this->sub_strategies_count) {
        for (int_fast32_t j = i + 1; j < i + this->sub_strategies_count; j++) {
            this->strategies[i].points += this->strategies[j].points;
            this->strategies[j].points = 0;
        }
        this->strategies[i].points /= this->sub_strategies_count;
    }
}

static int_fast32_t find_min_strategy(Strategy_data* this) {
    uint_fast32_t min = INT_MAX;
    uint_fast32_t min_index;
    for (int_fast32_t i = 0; i < this->all_strategies_count; i += this->sub_strategies_count) {
        if(this->strategies[i].points < min) {
            min = this->strategies[i].points;
            min_index = i;
        }
        this->strategies[i].points = 0;
    }
    return min_index;
}

void remove_strategies(Strategy_data* this) {
    int_fast32_t index = find_min_strategy(this);
    this->complexity_counters[this->strategies[index].complexity]--;
    if(this->strategies[index].group == GROUP_SMALL){
        this->small_complexity_counters[this->strategies[index].complexity]--;
        this->group_count--;
    }
    for (int_fast32_t i = index + this->sub_strategies_count - 1; i >= index; i--) {
        this->strategies[i] = this->strategies[this->all_strategies_count - 1];
        this->all_strategies_count--;
    }
}

void delete_Strategy_data(Strategy_data* this) {
    free(this->complexity_counters);
    free(this->small_complexity_counters);
    free(this->strategies);
    //free(this);
}

uint_fast32_t* init_complexity_array(int_fast32_t strategy_count) {
    uint_fast32_t* arr = new(uint_fast32_t, strategy_count);
    for (int_fast32_t i = 0; i < strategy_count; i++) {
        arr[i] = -1;
    }
    arr[0] = 0;
    return arr;
}

uint_fast8_t get_complexity(uint_fast8_t name, uint_fast32_t* complexity_arr, int_fast32_t size) {
    if(complexity_arr[name] == -1) {
        uint_fast8_t reflection = 0;
        append_move(reflection, abs(bit_at(name, 0) - bit_at(name, size - 1)), size);
        for (int_fast32_t i = size - 1; i > 0; i--) {
            append_move(reflection, abs(bit_at(name, i) - bit_at(name, i - 1)), size);
        }
        complexity_arr[name] = 1 + get_complexity(reflection, complexity_arr, size);
    }
    return complexity_arr[name];
}

double get_aggresiveness(uint_fast8_t name, int_fast32_t size){
    double counter = 0;
    for (int i = 0; i < size; i++){
        if(bit_at(name, i) == 0){
            counter++;
        }
    }
    return counter / size;
}
