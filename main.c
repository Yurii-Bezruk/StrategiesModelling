#include <stdlib.h>
#include "print.h"
#include "binary.h"
#include "strategy.h"

int matrix[2][2] = {
    {1, 5},
    {0, 3}
};
int MEMORY_DEPTH = 0;

const int ITERATIONS_COUNT = 500;

int main() {
    int main_digits_count = (int)pow(2, MEMORY_DEPTH + 1);
    int main_strategies_count = (int)pow(2, main_digits_count);
    int sub_digits_count = (int)pow(2, MEMORY_DEPTH);
    int sub_strategies_count = (int)pow(2, sub_digits_count);
    int all_strategies_count = main_strategies_count * sub_strategies_count;
    Strategy strategies[all_strategies_count];

    for (int i = 0, strat_index = 0; i < main_strategies_count; i++) {
        for (int j = 0; j < sub_strategies_count; j++, strat_index++){
            strategies[strat_index].name = i;
            strategies[strat_index].prev_move = j;
            strategies[strat_index].points = 0;
        }
    }
    for (int i = 0; i < all_strategies_count; i++){
        println_strategy(strategies + i, main_digits_count);
    }
}
