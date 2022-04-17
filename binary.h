#ifndef BINARY_H_INCLUDED
#define BINARY_H_INCLUDED
#include "power.h"

/**
* Returns value of @position bit of @number
*/
#define bit_at(number, position) ((number & ((int)power(position))) != 0 ? 1 : 0)

/**
* Returns new value after appending agent move to moves history using binary operators.
* Example of usage:
* prev_move = 5 (..00101)
* apeend_move(prev_move, 1, 3) -> 3 (..00011)
*
* @param number - storage of moves
* @param move - new move to be appended (0 or 1)
* @param digits_count - count of active digits
*/
#define append_move(number, move, digits_count) (number = (((number << 1) + move) & ~(1 << digits_count)))

#endif // BINARY_H_INCLUDED
