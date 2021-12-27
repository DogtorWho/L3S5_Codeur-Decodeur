#ifndef _LZW_TWELVEBITARRAY_
#define _LZW_TWELVEBITARRAY_

#include <stdlib.h>
#include <stdbool.h>
#include "globals.h"

typedef struct {
  twelveBit_t *array;
  size_t used;
  size_t size;
} twelveBitArray;

/* intialize an array with an initial size */
void init_twelveBitArray(twelveBitArray *a, size_t initialSize);

/* insert an element in the array a */
void insert_twelveBitArray(twelveBitArray *a, twelveBit_t b12);

/* free the array a and is memory allocated */
void free_twelveBitArray(twelveBitArray *a);

/* print the size, the size used and the variables of the array */
void print_twelveBitArray(twelveBitArray *a, bool seeAsciiCodes);

/* create a byte array with the transformed 12bit values of a */
void twelveBitArray_to_binaryFile(twelveBitArray *a, char *filename);

/* search for a code in the 12bit array */
bool find_code(twelveBitArray *a, twelveBit_t code);

#endif
