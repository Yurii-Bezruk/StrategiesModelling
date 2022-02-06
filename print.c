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

void print_strategy(Strategy* str, int_fast32_t main_digits_count) {
    print("[");
    print_binary(str->first_move, main_digits_count / 2);
    print("]");
    print_binary(str->name, main_digits_count);
    printf("\t%d", str->points);
}

void println_strategy(Strategy* str, int_fast32_t main_digits_count) {
    print_strategy(str, main_digits_count);
    printf("\n");
}
