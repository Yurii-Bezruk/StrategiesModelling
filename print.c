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
    printf(" (%u)<%.2f> \t%lu ", data->strategies[index].complexity, data->strategies[index].aggresiveness, data->strategies[index].points);
    print((data->strategies[index].group == GROUP_BIG) ? "BIG" : "SMALL");
}

void println_strategy(Strategy_data* data, int_fast32_t index) {
    print_strategy(data, index);
    printf("\n");
}

void print_all_strategies(Strategy_data* data) {
    for (int_fast32_t i = 0; i < data->all_strategies_count; i++) {
        println_strategy(data, i);
    }
    print("\n");
}

void print_main_strategies(Strategy_data* data) {
    for (int_fast32_t i = 0; i < data->all_strategies_count; i += data->sub_strategies_count) {
        print_binary(data->strategies[i].name, data->main_digits_count);
        printf(" (%u)<%.2f> \t%lu ", data->strategies[i].complexity, data->strategies[i].aggresiveness, data->strategies[i].points);
        println((data->strategies[i].group == GROUP_BIG) ? "BIG" : "SMALL");
    }
    print("\n");
}

void print_complexities(Strategy_data* data){
    double average_complexity = 0.0;
    int_fast32_t summary_complexity = 0;
    double small_average_complexity = 0.0;
    int_fast32_t small_summary_complexity = 0;
    double big_average_complexity = 0.0;
    int_fast32_t big_summary_complexity = 0;
    int_fast32_t big_complexity_counter = 0;
    printf("All: \tSmall: \tBig:\n");
    for (int_fast32_t i = 0; i < data->complexity_count; i++){
        big_complexity_counter = data->complexity_counters[i] - data->small_complexity_counters[i];
        average_complexity += i * data->complexity_counters[i];
        summary_complexity += data->complexity_counters[i];
        small_average_complexity += i * data->small_complexity_counters[i];
        small_summary_complexity += data->small_complexity_counters[i];
        big_average_complexity += i * big_complexity_counter;
        big_summary_complexity += big_complexity_counter;
        printf("(%d) - %d   %d   %d\n", i, data->complexity_counters[i], data->small_complexity_counters[i], big_complexity_counter);
    }
    printf("Average complexity: %f\n", average_complexity / summary_complexity);
    if(data->group_count != 0){
        printf("Average small group complexity: %f\n", small_average_complexity / small_summary_complexity);
    }
    printf("Average big group complexity: %f\n", big_average_complexity / big_summary_complexity);
}

void print_aggressiveness(Strategy_data* data){
    double average_aggressiveness = 0.0;
    double small_average_aggressiveness = 0.0;
    double big_average_aggressiveness = 0.0;
    for (int_fast32_t i = 0; i < data->all_strategies_count; i += data->sub_strategies_count){
        if(data->strategies[i].group == GROUP_SMALL){
            small_average_aggressiveness += data->strategies[i].aggresiveness;
        } else {
            big_average_aggressiveness += data->strategies[i].aggresiveness;
        }
        average_aggressiveness += data->strategies[i].aggresiveness;
    }
    printf("Average aggressiveness: %f\n", average_aggressiveness / (data->all_strategies_count / data->sub_strategies_count));
    if(data->group_count != 0){
        printf("Average small group aggressiveness: %f\n", (data->group_count == 0)? 0 : small_average_aggressiveness / data->group_count);
    }
    printf("Average big group aggressiveness: %f\n", big_average_aggressiveness / ((data->all_strategies_count / data->sub_strategies_count) - data->group_count));
}

void print_points(Strategy_data* data){
    double average_points = 0.0;
    double small_average_points = 0.0;
    double big_average_points = 0.0;
    for (int_fast32_t i = 0; i < data->all_strategies_count; i++){
        if(data->strategies[i].group == GROUP_SMALL){
            small_average_points += data->strategies[i].points;
        } else {
            big_average_points += data->strategies[i].points;
        }
        average_points += data->strategies[i].points;
    }
    int_fast32_t main_str_count = (data->all_strategies_count / data->sub_strategies_count);
    printf("Average points per turn: %f\n", average_points / data->all_strategies_count / data->iterations_count / (data->all_strategies_count - 1));
    if(data->group_count != 0){
        printf("Average small group points per turn: %f\n", (data->group_count == 0)? 0 : small_average_points / (data->group_count * data->sub_strategies_count) / data->iterations_count / (data->all_strategies_count - 1));
    }
    printf("Average big group points per turn: %f\n\n", big_average_points / (data->all_strategies_count - (data->group_count * data->sub_strategies_count) ) / data->iterations_count / (data->all_strategies_count - 1));
}
