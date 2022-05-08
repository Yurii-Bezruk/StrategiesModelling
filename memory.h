#ifndef MEMORY_H_INCLUDED
#define MEMORY_H_INCLUDED

/**
* Macro that allocates memory for given count of elements of needed type.
* Example of usage:
* int var = *new(int, 1);
* int* ptr = new(int, 1);
* int* array = new(int, size);
* @param type - type of object(s) to be allocated
* @param count - count of elements to be allocated
* @return pointer to allocated memory. For example, if needed type was
*         int, return type will be int*
*/
#define new(type, count) ((type*) malloc(sizeof(type) * count))

#endif // MEMORY_H_INCLUDED
