#include <stdlib.h>
#include <stdint.h>
#include <limits.h>
#include <string.h>
#include "print.h"
#include "binary.h"
#include "strategy.h"

uint_fast32_t MEMORY_DEPTH = 1;
uint_fast32_t ITERATIONS_COUNT = 100;
int_fast32_t MATRIX[2][2] = {
    {1, 5},
    {0, 3}
};

void init_global_params(int argc, char** argv){
    for (int i = 0; i < argc; i++){
        if(strcmp(argv[i], "-h") == 0){
            println("Options:");
            println("\t-h                                      Print help (this message)");
            println("\t-i <number>                             Set iterations count for every two strategies");
            println("\t-d <number>                             Set strategy memory depth");
            println("\t-m <number> <number> <number> <number>  Set reward matrix for strategies");
            exit(0);
        } else if(strcmp(argv[i], "-i") == 0 && (i + 1) < argc){
            ITERATIONS_COUNT = atoi(argv[++i]);
        } else if(strcmp(argv[i], "-d") == 0 && (i + 1) < argc){
            MEMORY_DEPTH = atoi(argv[++i]);
        } else if(strcmp(argv[i], "-m") == 0 && (i + 4) < argc){
            MATRIX[0][0] = atoi(argv[++i]);
            MATRIX[0][1] = atoi(argv[++i]);
            MATRIX[1][0] = atoi(argv[++i]);
            MATRIX[1][1] = atoi(argv[++i]);
        }
    }
}

int main(int argc, char** argv) {
    init_global_params(argc, argv);

    Strategy_data data = *create_Strategy_data(MEMORY_DEPTH, ITERATIONS_COUNT, MATRIX);

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
