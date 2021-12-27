/**
 * @file LZW_twelveBitArray.h
 * File containing the functions to use 12-bit arrays.
 */

#ifndef _LZW_TWELVEBITARRAY_
#define _LZW_TWELVEBITARRAY_

#include <stdlib.h>
#include <stdbool.h>
#include "globals.h"

/**
 * @struct twelveBitArray
 * @param array array of 12-bit
 * @param used size used in the array
 * @param size real size of the array
 */
typedef struct {
  twelveBit_t *array;
  size_t used;
  size_t size;
} twelveBitArray;

/**
 * @fn void init_twelveBitArray(twelveBitArray *a, size_t initialSize)
 * @brief intialize a 12-bit array with an initial size
 * @param a the 12-bit array to initialize
 * @param initialSize the initial size of the array
 */
void init_twelveBitArray(twelveBitArray *a, size_t initialSize);

/**
 * @fn void insert_twelveBitArray(twelveBitArray *a, twelveBit_t b12)
 * @brief insert an element in a 12-bit array
 * @param a the 12-bit array where the element will be inserted
 * @param b12 the 12-bit to insert
 */
void insert_twelveBitArray(twelveBitArray *a, twelveBit_t b12);

/**
 * @fn void free_byteArray(byteArray *a)
 * @brief free the memory allocated to the 12-bit array
 * @param a the 12-bit array to free
 */
void free_twelveBitArray(twelveBitArray *a);

/**
 * @fn void print_twelveBitArray(twelveBitArray *a, bool seeAsciiCodes)
 * @brief print a 12-bit array
 * print the size, the size used and all the 12-bit of the array
 * @param a the 12-bit array to print
 * @param seeAsciiCodes see the first 256 bytes representing the ASCII characters
 */
void print_twelveBitArray(twelveBitArray *a, bool seeAsciiCodes);

/**
 * @fn void twelveBitArray_to_binaryFile(twelveBitArray *a, char *filename)
 * @brief convert a 12-bit array to a binary file
 * fill the binary file with the contents of the array
 * @param a the 12-bit array to convert
 * @param filename the binary file name which will stock the 12-bits
 */
void twelveBitArray_to_binaryFile(twelveBitArray *a, char *filename);

/**
 * @fn bool find_code(twelveBitArray *a, twelveBit_t code)
 * @brief search for a code in the 12-bit array
 * @param a the 12-bit array to search in
 * @param code the code to search for
 * @return bool
 * @retval true if the code was found in the 12-bit array
 * @retval false if the code was not found in the 12-bit array
 */
bool find_code(twelveBitArray *a, twelveBit_t code);

#endif
