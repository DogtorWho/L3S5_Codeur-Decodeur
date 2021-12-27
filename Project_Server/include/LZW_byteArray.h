#ifndef _LZW_BYTEARRAY_
#define _LZW_BYTEARRAY_

#include <stdlib.h>
#include "globals.h"

typedef struct {
  byte_t *array;
  size_t used;
  size_t size;
} byteArray;

/* intialize an array with an initial size */
void init_byteArray(byteArray *a, size_t initialSize);

/* insert an element in the array a */
void insert_byteArray(byteArray *a, byte_t byte);

/* free the array a and is memory allocated */
void free_byteArray(byteArray *a);

/* print the size, the size used and the variables of the array */
void print_byteArray(byteArray *a);

/* fill the binary file with the contents of the array */
void byteArray_to_binaryFile(byteArray *a, char *filename);

/* fill the byte array file with the contents of the binary file */
void binaryFile_to_byteArray(byteArray *a, char *filename);

#endif
