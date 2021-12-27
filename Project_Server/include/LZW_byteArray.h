/**
 * @file LZW_byteArray.h
 * File containing functions to control an array of bytes.
 */

#ifndef _LZW_BYTEARRAY_
#define _LZW_BYTEARRAY_

#include <stdlib.h>

#include "globals.h"

/**
 * @struct byteArray
 * @param array array of bytes
 * @param used size used in the array
 * @param size real size of the array
 */
typedef struct {
  byte_t *array;
  size_t used;
  size_t size;
} byteArray;

/**
 * @fn void init_byteArray(byteArray *a, size_t initialSize)
 * @brief intialize a byte array with an initial size
 * @param a the byte array to initialize
 * @param initialSize the initial size of the array
 */
void init_byteArray(byteArray *a, size_t initialSize);

/**
 * @fn void insert_byteArray(byteArray *a, byte_t byte)
 * @brief insert an element in a byte array
 * @param a the byte array where the element will be inserted
 * @param byte the byte to insert
 */
void insert_byteArray(byteArray *a, byte_t byte);

/**
 * @fn void free_byteArray(byteArray *a)
 * @brief free the memory allocated to the byte array
 * @param a the byte array to free
 */
void free_byteArray(byteArray *a);

/**
 * @fn void print_byteArray(byteArray *a)
 * @brief print a byte array
 * print the size, the size used and all the bytes of the array
 * @param a the byte array to print
 */
void print_byteArray(byteArray *a);

/**
 * @fn void byteArray_to_binaryFile(byteArray *a, char *filename)
 * @brief convert a byte array to a binary file
 * fill the binary file with the contents of the array
 * @param a the byte array to convert
 * @param filename the binary file name which will stock the bytes
 */
void byteArray_to_binaryFile(byteArray *a, char *filename);

/**
 * @fn void binaryFile_to_byteArray(byteArray *a, char *filename)
 * @brief convert a binary file into a byte array
 * fill the byte array file with the contents of the binary file
 * @param a the byte array to be converted
 * @param filename the binary file name which contain the bytes
 */
void binaryFile_to_byteArray(byteArray *a, char *filename);

#endif
