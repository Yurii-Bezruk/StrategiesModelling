#include <stdlib.h>
#include <stdint.h>
#include <limits.h>
#include "print.h"
#include "binary.h"
#include "strategy.h"

uint_fast32_t MEMORY_DEPTH = 2;
const uint_fast32_t ITERATIONS_COUNT = 100;
int_fast32_t MATRIX[2][2] = {
    {1, 5},
    {0, 3}
};

int main() {
    Strategy_data data = *create_Strategy_data(MEMORY_DEPTH, ITERATIONS_COUNT, MATRIX);
    //play(&data, 26636, 23771);

    while(data.all_strategies_count >= 2 * data.sub_strategies_count) {
        for (int_fast32_t i = 0; i < data.all_strategies_count; i++) {
            for (int_fast32_t j = i; j < data.all_strategies_count; j++) {
                play(&data, i, j);
            }
        }

        print_all_strategies(&data);
        average_strategies(&data);
        print_main_strategies(&data);
        remove_strategies(&data);
        printf("%d/%d\n", data.all_strategies_count, 2 * data.sub_strategies_count);
        println("----------------------------------");
    }

    delete_Strategy_data(&data);
}
