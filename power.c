#include "power.h"

const int_fast32_t powers[12] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048};

int_fast32_t power(int_fast8_t n){
    return powers[n];
}