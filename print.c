#include "print.h"

void print_binary(int_fast32_t x, int_fast32_t digits) {
    for (int_fast32_t i = digits - 1; i >= 0; i--) {
        print(bit_at(x, i));
    }
}

void println_binary(int_fast32_t x, int_fast32_t digits) {
    print_binary(x, digits);
    printf("\n");
}

void print_strategy(Strategy_data* data, int_fast32_t index) {
    for (int i = 0; i < data->memory_depth + 1; i++) {
        print("[");
        print_binary(data->strategies[index].sub_strategies / power(i), power(i));
        print("]");
    }
    print_binary(data->strategies[index].name, data->main_digits_count);
    printf(" (%u)\t%lu", data->strategies[index].complexity, data->strategies[index].points);
}

void println_strategy(Strategy_data* data, int_fast32_t index) {
    print_strategy(data, index);
    printf("\n");
}

void print_all_strategies(Strategy_data* data) {
    for (int_fast32_t i = 0; i < data->all_strategies_count; i++) {
        println_strategy(data, i);
    }
    println("\n");
}

void print_main_strategies(Strategy_data* data) {
    for (int_fast32_t i = 0; i < data->all_strategies_count; i += data->sub_strategies_count) {
        print_binary(data->strategies[i].name, data->main_digits_count);
        printf(" (%u)\t%lu\n", data->strategies[i].complexity, data->strategies[i].points);
    }
    println("\n");
}

