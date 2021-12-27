/**
 * @file LZW_twelveBitArray.h
 * File containing the functions to use 12-bit arrays.
 */

#include "LZW_twelveBitArray.h"

#include <stdio.h>
#include <assert.h>

#include "tools.h"

void init_twelveBitArray(twelveBitArray *a, size_t initialSize) {
  assert(a != NULL);
  assert(initialSize > 0);

  a->array = malloc(initialSize * sizeof(twelveBit_t));
  a->used = 0;
  a->size = initialSize;
}

void insert_twelveBitArray(twelveBitArray *a, twelveBit_t b12) {
  assert(a != NULL);
  assert(a->array != NULL);

  // a->used is the number of used entries, because a->array[a->used++] updates a->used only *after* the array has been accessed.
  // Therefore a->used can go up to a->size
  if (a->used == a->size) {
    a->size *= 2;
    a->array = realloc(a->array, a->size * sizeof(twelveBit_t));
    assert(a->array != NULL);
  }
  a->array[a->used++] = b12;
}

void free_twelveBitArray(twelveBitArray *a) {
  assert(a != NULL);

  free(a->array);
  a->array = NULL;
  a->used = a->size = 0;
}

void print_twelveBitArray(twelveBitArray *a, bool seeAsciiCodes) {
  assert(a != NULL);
  assert(a->array != NULL);

  int i = 0;
  if(!seeAsciiCodes){
    i = 256;
    printf(" Skipping the ascii table\n");
  }

  printf(" - Size : %ld\n", a->size);
  printf(" - Size used : %ld\n", a->used);
  printf(" - Variables : \n");
  for(int j = i; j < a->used; j++)
    b12_printf(a->array[j], "   ", 1);
  printf("\n");
}

void twelveBitArray_to_binaryFile(twelveBitArray *a, char *filename){
  FILE *fd = fopen(filename, "wb");
  assert(fd != NULL);

  byteArray byArr;
  init_byteArray(&byArr, 1);

  b12Array_to_byteArray(a, &byArr);

  byte_t buffer[byArr.used];

  fwrite(buffer, 1, byArr.used, fd);

  free_byteArray(&byArr);

  fclose(fd);
}

bool find_code(twelveBitArray *a, twelveBit_t code){
  assert(a != NULL);

  for(int i=0; i < a->used; i++){
    if(code == a->array[i]){
      return true;
    }
  }
  return false;
}
