#include "print.h"

void print_binary(int x, int digits) {
    for (int i = digits - 1; i >= 0; i--) {
        print(bit_at(x, i));
    }
}

void println_binary(int x, int digits) {
    print_binary(x, digits);
    printf("\n");
}

void print_strategy(Strategy* str, int main_digits_count) {
    print("[");
    print_binary(str->prev_move, main_digits_count / 2);
    print("]");
    print_binary(str->name, main_digits_count);
}

void println_strategy(Strategy* str, int main_digits_count) {
    print_strategy(str, main_digits_count);
    printf("\n");
}
