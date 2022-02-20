#ifndef POWER_H_INCLUDED
#define POWER_H_INCLUDED

const int_fast32_t powers[12] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048};

#define power(n) ((int_fast32_t)powers[n])

#endif // POWER_H_INCLUDED
