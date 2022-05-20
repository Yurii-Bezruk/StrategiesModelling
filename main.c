#include <stdlib.h>
#include <stdint.h>
#include <limits.h>
#include <string.h>
#include "print.h"
#include "binary.h"
#include "strategy.h"
#include "memory.h"

uint_fast32_t MEMORY_DEPTH;
uint_fast32_t GROUP_SIZE;
uint_fast32_t ITERATIONS_COUNT;
int_fast32_t** MATRIX;
int_fast32_t** OWN_MATRIX;
int_fast32_t** FOREIGN_MATRIX;

void init_global_params(int argc, char** argv){
    MEMORY_DEPTH = 1;
    GROUP_SIZE = 4;
    ITERATIONS_COUNT = 100;

    MATRIX = new(int_fast32_t*, 2);
    MATRIX[0] = new(int_fast32_t, 2);
    MATRIX[1] = new(int_fast32_t, 2);
    MATRIX[0][0] = 1;
    MATRIX[0][1] = 5;
    MATRIX[1][0] = 0;
    MATRIX[1][1] = 3;

    OWN_MATRIX = new(int_fast32_t*, 2);
    OWN_MATRIX[0] = new(int_fast32_t, 2);
    OWN_MATRIX[1] = new(int_fast32_t, 2);
    OWN_MATRIX[0][0] = 0;
    OWN_MATRIX[0][1] = 1;
    OWN_MATRIX[1][0] = 3;
    OWN_MATRIX[1][1] = 5;

    FOREIGN_MATRIX = new(int_fast32_t*, 2);
    FOREIGN_MATRIX[0] = new(int_fast32_t, 2);
    FOREIGN_MATRIX[1] = new(int_fast32_t, 2);
    FOREIGN_MATRIX[0][0] = 2;
    FOREIGN_MATRIX[0][1] = 6;
    FOREIGN_MATRIX[1][0] = 0;
    FOREIGN_MATRIX[1][1] = 2;

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

void delete_matrixes(){
    free(MATRIX[0]);
    free(MATRIX[1]);
    free(MATRIX);
    free(OWN_MATRIX[0]);
    free(OWN_MATRIX[1]);
    free(OWN_MATRIX);
    free(FOREIGN_MATRIX[0]);
    free(FOREIGN_MATRIX[1]);
    free(FOREIGN_MATRIX);
}

int main(int argc, char** argv) {
    init_global_params(argc, argv);
    Strategy_data data = *create_Strategy_data(MEMORY_DEPTH, GROUP_SIZE, ITERATIONS_COUNT, MATRIX, OWN_MATRIX, FOREIGN_MATRIX);

//    int arr[9];
//    for (int i = 0; i < 9; i++){
//        arr[i] = 0;
//    }
//    for (int i = 0; i < data.all_strategies_count; i += data.sub_strategies_count){
//        if(data.strategies[i].group == GROUP_SMALL){
//            arr[data.strategies[i].complexity]++;
//        }
//    }
//    for (int i = 0; i < 9; i++){
//        printf("(%d) - %d\n", i, arr[i]);
//    }
//    print_main_strategies(&data);

    while(data.all_strategies_count >= 2 * data.sub_strategies_count) {
        for (int_fast32_t i = 0; i < data.all_strategies_count; i++) {
            for (int_fast32_t j = i; j < data.all_strategies_count; j++) {
                play(&data, i, j);
            }
        }

        print_all_strategies(&data);
        printf("%d/2\n", data.all_strategies_count / data.sub_strategies_count);

        average_strategies(&data);
        print_main_strategies(&data);
        remove_strategies(&data);
        println("----------------------------------");
    }

    delete_Strategy_data(&data);
    delete_matrixes();
}
