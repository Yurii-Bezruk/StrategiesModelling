#include <stdlib.h>
#include <stdint.h>
#include <limits.h>
#include "print.h"
#include "binary.h"
#include "strategy.h"

uint_fast32_t MEMORY_DEPTH = 0;
const uint_fast32_t ITERATIONS_COUNT = 100;
int_fast32_t MATRIX[2][2] = {
    {1, 5},
    {0, 3}
};

int main() {
    Strategy_data data = *create_Strategy_data(MEMORY_DEPTH, ITERATIONS_COUNT, MATRIX);

    while(data.all_strategies_count > 2) {
        for (int_fast32_t i = 0; i < data.all_strategies_count; i++) {
            for (int_fast32_t j = i; j < data.all_strategies_count; j++) {
//            int i = 2, j = 4;
                play(&data, i, j);
            }
        }

        for (int_fast32_t i = 0; i < data.all_strategies_count; i++) {
            println_strategy(data.strategies + i, data.main_digits_count);
        }
        println("\n");

        remove_strategies(&data);

        println("----------------------------------");
    }

    delete_Strategy_data(&data);
}
